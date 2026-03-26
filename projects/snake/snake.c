// Compile:
// cc snake.c -o snake -lncurses

#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SCORE 256
#define FRAME_TIME 130000

typedef struct {
    int x;
    int y;
} Vec2;

int screen_width = 25;
int screen_height = 20;

WINDOW *win;

Vec2 head = {0,0};
Vec2 segments[MAX_SCORE];
Vec2 dir = {1,0};
Vec2 berry;

int score = 0;
bool is_running = true;

char score_message[32];

bool collide(Vec2 a, Vec2 b){
    return a.x == b.x && a.y == b.y;
}

bool collide_body(Vec2 p){
    for(int i = 0; i < score; i++)
        if(collide(p, segments[i]))
            return true;
    return false;
}

Vec2 spawn_berry(){

    Vec2 b;

    do{
        b.x = rand() % screen_width;
        b.y = rand() % screen_height;
    }
    while(collide(b, head) || collide_body(b));

    return b;
}

void draw_border(){

    int width = screen_width * 2 + 1;
    int height = screen_height + 1;

    mvaddch(0,0,ACS_ULCORNER);
    mvaddch(0,width,ACS_URCORNER);

    for(int i=1;i<width;i++)
        mvaddch(0,i,ACS_HLINE);

    for(int i=1;i<=height;i++){
        mvaddch(i,0,ACS_VLINE);
        mvaddch(i,width,ACS_VLINE);
    }

    mvaddch(height+1,0,ACS_LLCORNER);
    mvaddch(height+1,width,ACS_LRCORNER);

    for(int i=1;i<width;i++)
        mvaddch(height+1,i,ACS_HLINE);
}

void quit_game(){
    endwin();
    printf("\e[1;1H\e[2J");
    printf("\e[?25h");
    exit(0);
}

void restart_game(){

    head = (Vec2){0,0};
    dir = (Vec2){1,0};

    score = 0;

    snprintf(score_message,sizeof(score_message),"[ Score: %d ]",score);

    berry = spawn_berry();

    is_running = true;
}

void init(){

    srand(time(NULL));

    win = initscr();

    keypad(win,true);
    noecho();
    nodelay(win,true);
    curs_set(0);

    if(!has_colors()){
        endwin();
        fprintf(stderr,"Terminal does not support colors\n");
        exit(1);
    }

    start_color();
    use_default_colors();

    init_pair(1,COLOR_RED,-1);
    init_pair(2,COLOR_GREEN,-1);
    init_pair(3,COLOR_YELLOW,-1);

    berry = spawn_berry();

    snprintf(score_message,sizeof(score_message),"[ Score: %d ]",score);
}

void process_input(){

    int key = wgetch(win);

    switch(key){

        case KEY_LEFT:
            if(dir.x != 1){ dir.x = -1; dir.y = 0; }
            break;

        case KEY_RIGHT:
            if(dir.x != -1){ dir.x = 1; dir.y = 0; }
            break;

        case KEY_UP:
            if(dir.y != 1){ dir.x = 0; dir.y = -1; }
            break;

        case KEY_DOWN:
            if(dir.y != -1){ dir.x = 0; dir.y = 1; }
            break;

        case ' ':
            if(!is_running) restart_game();
            break;

        case 27:
            quit_game();
            break;
    }
}

void game_over(){

    while(!is_running){

        process_input();

        mvaddstr(screen_height/2,screen_width-8,"Game Over");
        mvaddstr(screen_height/2+1,screen_width-12,"[SPACE] restart");

        attron(COLOR_PAIR(3));
        draw_border();
        attroff(COLOR_PAIR(3));

        refresh();
        usleep(FRAME_TIME);
    }
}

void update(){

    for(int i = score; i > 0; i--)
        segments[i] = segments[i-1];

    segments[0] = head;

    head.x += dir.x;
    head.y += dir.y;

    if(head.x < 0 || head.y < 0 ||
       head.x >= screen_width ||
       head.y >= screen_height ||
       collide_body(head))
    {
        is_running = false;
        game_over();
        return;
    }

    if(collide(head,berry)){

        if(score < MAX_SCORE)
            score++;

        snprintf(score_message,sizeof(score_message),"[ Score: %d ]",score);

        berry = spawn_berry();
    }

    usleep(FRAME_TIME);
}

void draw(){

    erase();

    attron(COLOR_PAIR(1));
    mvaddch(berry.y+1, berry.x*2+1, '@');
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));

    for(int i=0;i<score;i++)
        mvaddch(segments[i].y+1, segments[i].x*2+1, '$');

    mvaddch(head.y+1, head.x*2+1, '+');

    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(3));
    draw_border();
    attroff(COLOR_PAIR(3));

    mvaddstr(0, screen_width-5, score_message);

    refresh();
}

int main(int argc,char *argv[]){

    if(argc == 3 && !strcmp(argv[1],"-d")){

        if(sscanf(argv[2],"%dx%d",&screen_width,&screen_height) != 2){
            printf("Usage: snake -d WIDTHxHEIGHT\n");
            exit(1);
        }
    }

    init();

    while(is_running){

        process_input();
        update();
        draw();
    }

    quit_game();

    return 0;
}