#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <ncurses.h>

int jumpHeight = 0;
int gameSpeed = 40000;

void pauseGame() {
    usleep(gameSpeed);
}

void displayGameInfo() {
    clear();
    mvprintw(1, 10, "SPACE = Jump | X = Exit");
    mvprintw(1, 60, "SCORE:");
}

void displayCharacter(int jumpType) {

    if (jumpType == 1)
        jumpHeight++;
    else if (jumpType == 2)
        jumpHeight--;

    mvprintw(15 - jumpHeight, 2, "  O ");
    mvprintw(16 - jumpHeight, 2, " /|\\ ");
    mvprintw(17 - jumpHeight, 2, " / \\ ");

    refresh();
    pauseGame();
}

void displayObstacle(int *pos) {

    mvprintw(17, 70 - *pos, "|");

    (*pos)++;

    if (*pos > 70)
        *pos = 0;
}

int main() {

    int obstaclePos = 0;
    int ch;

    initscr();
    noecho();
    curs_set(FALSE);

    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    displayGameInfo();

    while (1) {

        ch = getch();

        if (ch == 'x')
            break;

        if (ch == ' ') {
            for(int i=0;i<5;i++){
                displayCharacter(1);
                displayObstacle(&obstaclePos);
            }
            for(int i=0;i<5;i++){
                displayCharacter(2);
                displayObstacle(&obstaclePos);
            }
        } else {
            displayCharacter(0);
            displayObstacle(&obstaclePos);
        }

        clear();
        displayGameInfo();
    }

    endwin();
    return 0;
}