#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 5

struct Player {
    int x, y;
    int health;
    int score;
};

struct Question {
    char question[100];
    char options[4][50];
    char answer;
};

char map[SIZE][SIZE] = {
    {'S', '.', 'Q', '.', '.'},
    {'.', 'T', '.', 'Q', '.'},
    {'.', '.', '.', '.', '.'},
    {'.', 'Q', '.', 'T', '.'},
    {'.', '.', '.', '.', 'E'}
};

struct Question questions[3] = {
    {"What is the capital of France?",
     {"A) Berlin", "B) Paris", "C) Rome", "D) Madrid"}, 'B'},

    {"Which language is used for system programming?",
     {"A) Python", "B) Java", "C) C", "D) HTML"}, 'C'},

    {"Who is the father of C language?",
     {"A) Bjarne", "B) James", "C) Dennis Ritchie", "D) Guido"}, 'C'}
};

void displayMap(struct Player p) {
    printf("\nMAP:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i == p.x && j == p.y)
                printf("P ");
            else
                printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int askQuestion() {
    int q = rand() % 3;
    char ans;

    printf("\nQUIZ TIME!\n");
    printf("%s\n", questions[q].question);
    for (int i = 0; i < 4; i++)
        printf("%s\n", questions[q].options[i]);

    printf("Enter answer (A/B/C/D): ");
    scanf(" %c", &ans);

    if (ans == questions[q].answer || ans == questions[q].answer + 32) {
        printf("Correct!\n");
        return 1;
    } else {
        printf("Wrong! Correct answer is %c\n", questions[q].answer);
        return 0;
    }
}

int main() {
    struct Player p;
    char move;

    srand(time(0));

    p.x = 0;
    p.y = 0;
    p.health = 3;
    p.score = 0;

    printf("=== QUIZ ADVENTURE GAME ===\n");
    printf("Reach 'E' to win. Avoid traps (T).\n");

    while (1) {
        displayMap(p);
        printf("Health: %d  Score: %d\n", p.health, p.score);
        printf("Move (W/A/S/D): ");
        scanf(" %c", &move);

        if (move == 'W' || move == 'w') p.x--;
        else if (move == 'S' || move == 's') p.x++;
        else if (move == 'A' || move == 'a') p.y--;
        else if (move == 'D' || move == 'd') p.y++;

        if (p.x < 0) p.x = 0;
        if (p.x >= SIZE) p.x = SIZE - 1;
        if (p.y < 0) p.y = 0;
        if (p.y >= SIZE) p.y = SIZE - 1;

        if (map[p.x][p.y] == 'Q') {
            if (askQuestion()) {
                p.score += 10;
                map[p.x][p.y] = '.';
            } else {
                p.health--;
            }
        }
        else if (map[p.x][p.y] == 'T') {
            printf("You stepped on a TRAP!\n");
            p.health--;
            map[p.x][p.y] = '.';
        }
        else if (map[p.x][p.y] == 'E') {
            printf("\nYOU ESCAPED THE MAP!\n");
            printf("Final Score: %d\n", p.score);
            break;
        }

        if (p.health <= 0) {
            printf("\nGAME OVER! You lost all health.\n");
            break;
        }
    }

    return 0;
}