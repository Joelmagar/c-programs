#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <SDL2/SDL.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>

#include <portaudio.h>

#define SAMPLE_RATE 44100
#define CHANNELS 2
#define SAMPLE_MAX SHRT_MAX

#define BASE_NOTE 9
#define NUMBER_OF_NOTES 84

#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef short SampleType;

typedef struct {
    int sample_count;
    SampleType (*data)[CHANNELS];
} SoundData;

typedef struct {
    bool pressed;
    int sample_position;
} PlayingState;

typedef struct {
    SoundData sound_data;
    PlayingState playing_state;
} PianoString;

PianoString piano[NUMBER_OF_NOTES];
PaStream* audio_stream;
int keycode_to_note[256];


// ---------------- WAV LOADER ----------------

SoundData loadWavFileForNote(int note) {
    SoundData sound = {0};

    char path[256];
    snprintf(path, sizeof(path), "samples/%i.wav", note);

    FILE* f = fopen(path, "rb");
    if (!f) {
        sound.sample_count = 1;
        sound.data = malloc(sizeof(SampleType[CHANNELS]));
        sound.data[0][0] = 0;
        sound.data[0][1] = 0;
        return sound;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    uint8_t* buffer = malloc(size);
    fread(buffer, 1, size, f);
    fclose(f);

    int data_offset = -1;
    int data_size = 0;

    for (int i = 0; i < size - 8; i++) {
        if (memcmp(buffer + i, "data", 4) == 0) {
            data_offset = i + 8;
            data_size = *(int*)(buffer + i + 4);
            break;
        }
    }

    if (data_offset < 0) {
        free(buffer);
        sound.sample_count = 1;
        sound.data = malloc(sizeof(SampleType[CHANNELS]));
        sound.data[0][0] = 0;
        sound.data[0][1] = 0;
        return sound;
    }

    sound.sample_count = data_size / sizeof(SampleType) / CHANNELS;
    sound.data = malloc(sizeof(SampleType) * CHANNELS * sound.sample_count);
    memcpy(sound.data, buffer + data_offset, data_size);

    free(buffer);
    return sound;
}


// ---------------- PIANO ----------------

void initPiano() {
    for (int i = 0; i < NUMBER_OF_NOTES; i++)
        piano[i].sound_data = loadWavFileForNote(BASE_NOTE + i);
}

void deinitPiano() {
    for (int i = 0; i < NUMBER_OF_NOTES; i++)
        free(piano[i].sound_data.data);
}

void pressKey(int note) {
    if (note < BASE_NOTE || note >= BASE_NOTE + NUMBER_OF_NOTES) return;
    int i = note - BASE_NOTE;
    piano[i].playing_state.sample_position = 0;
    piano[i].playing_state.pressed = true;
}

void releaseKey(int note) {
    if (note < BASE_NOTE || note >= BASE_NOTE + NUMBER_OF_NOTES) return;
    piano[note - BASE_NOTE].playing_state.pressed = false;
}


// ---------------- AUDIO ----------------

int audioCallback(const void* input,
                  void* output,
                  unsigned long frames,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void* userData)
{
    float (*out)[2] = output;

    for (unsigned long i = 0; i < frames; i++) {
        out[i][0] = 0.0f;
        out[i][1] = 0.0f;
    }

    for (int p = 0; p < NUMBER_OF_NOTES; p++) {
        if (!piano[p].playing_state.pressed) continue;

        int pos = piano[p].playing_state.sample_position;
        int count = MIN(frames,
                        piano[p].sound_data.sample_count - pos);

        for (int i = 0; i < count; i++) {
            float l = piano[p].sound_data.data[pos + i][0] / (float)SAMPLE_MAX;
            float r = piano[p].sound_data.data[pos + i][1] / (float)SAMPLE_MAX;
            out[i][0] += l * 0.2f;
            out[i][1] += r * 0.2f;
        }

        if (count != frames)
            piano[p].playing_state.pressed = false;
        else
            piano[p].playing_state.sample_position += frames;
    }

    return paContinue;
}

void initAudio() {
    Pa_Initialize();

    PaStreamParameters out;
    out.device = Pa_GetDefaultOutputDevice();
    out.channelCount = 2;
    out.sampleFormat = paFloat32;
    out.suggestedLatency =
        Pa_GetDeviceInfo(out.device)->defaultLowOutputLatency;
    out.hostApiSpecificStreamInfo = NULL;

    Pa_OpenStream(&audio_stream,
                  NULL,
                  &out,
                  SAMPLE_RATE,
                  paFramesPerBufferUnspecified,
                  paNoFlag,
                  audioCallback,
                  NULL);

    Pa_StartStream(audio_stream);
}
void deinitAudio() {
    Pa_StopStream(audio_stream);
    Pa_Terminate();
}


// ---------------- KEYBOARD ----------------

const int keys[] = {
    67,68,69,70,71,72,73,74,75,76,95,96,
    10,11,12,13,14,15,16,17,18,19,20,21,
    24,25,26,27,28,29,30,31,32,33,34,35,
    38,39,40,41,42,43,44,45,46,47,48,51,
    94,52,53,54,55,56,57,58,59,60,61,62,
};

void initKeys(Display* d) {
    Window root = DefaultRootWindow(d);

    for (int i = 0; i < 256; i++)
        keycode_to_note[i] = -1;

    for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); i++)
        keycode_to_note[keys[i]] = i;

    XGrabKeyboard(d, root, false, GrabModeAsync, GrabModeAsync, CurrentTime);
    XAutoRepeatOff(d);
    XSelectInput(d, root, KeyPressMask | KeyReleaseMask);
}

void deinitKeys(Display* d) {
    Window root = DefaultRootWindow(d);
    XUngrabKeyboard(d, root);
    XAutoRepeatOn(d);
}

void runInputLoop(Display* d) {
    bool quit = false;
    int shift = 12;

    while (!quit) {
        XEvent e;
        XNextEvent(d, &e);
printf("Keycode: %d\n", e.xkey.keycode);
        if (e.type != KeyPress && e.type != KeyRelease) continue;

        KeySym sym = XkbKeycodeToKeysym(d, e.xkey.keycode, 0, 0);
        if (sym == XK_Escape) quit = true;

        int idx = keycode_to_note[e.xkey.keycode];
        if (idx < 0) continue;

        int note = idx + BASE_NOTE + shift;

        if (e.type == KeyPress) pressKey(note);
        else releaseKey(note);
    }
}


// ---------------- MAIN ----------------

int main() {
    Display* display = XOpenDisplay(NULL);
    if (!display) return 1;

    initPiano();
    initAudio();
    initKeys(display);

    printf("Ready to play (ESC to quit)\n");
    runInputLoop(display);

    deinitKeys(display);
    deinitAudio();
    deinitPiano();
    XCloseDisplay(display);
    return 0;
}