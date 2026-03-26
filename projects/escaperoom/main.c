#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
    int hasKey;
    int hasClue;
};

void room1(struct Player *p);
void room2(struct Player *p);
void room3(struct Player *p);

int main() {
    struct Player player = {0, 0};
    int choice;

    printf("=================================\n");
    printf("      ESCAPE ROOM GAME\n");
    printf("=================================\n");
    printf("You wake up in a locked house...\n");

    while (1) {
        printf("\n--- MAIN HALL ---\n");
        printf("1. Go to Room 1\n");
        printf("2. Go to Room 2\n");
        printf("3. Go to Exit Door\n");
        printf("4. Quit Game\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                room1(&player);
                break;
            case 2:
                room2(&player);
                break;
            case 3:
                room3(&player);
                break;
            case 4:
                printf("Thanks for playing!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void room1(struct Player *p) {
    int choice;
    printf("\n--- ROOM 1 (Bedroom) ---\n");
    printf("1. Search the bed\n");
    printf("2. Search the cupboard\n");
    printf("3. Go back\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        if (p->hasKey == 0) {
            printf("You found a KEY under the bed!\n");
            p->hasKey = 1;
        } else {
            printf("Nothing else here.\n");
        }
    } else if (choice == 2) {
        printf("You found a paper with a riddle:\n");
        printf("I speak without a mouth and hear without ears. What am I?\n");
        p->hasClue = 1;
    } else if (choice == 3) {
        return;
    } else {
        printf("Invalid option.\n");
    }
}

void room2(struct Player *p) {
    int choice;
    char answer[20];

    printf("\n--- ROOM 2 (Study Room) ---\n");
    printf("1. Open drawer\n");
    printf("2. Solve riddle\n");
    printf("3. Go back\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Drawer is empty.\n");
    }
    else if (choice == 2) {
        if (p->hasClue == 1) {
            printf("Enter your answer: ");
            scanf("%s", answer);

            if (strcmp(answer, "echo") == 0 || strcmp(answer, "Echo") == 0) {
                printf("Correct! A secret door opens...\n");
            } else {
                printf("Wrong answer!\n");
            }
        } else {
            printf("You don't know the riddle yet.\n");
        }
    }
    else if (choice == 3) {
        return;
    }
    else {
        printf("Invalid choice.\n");
    }
}

void room3(struct Player *p) {
    if (p->hasKey == 1 && p->hasClue == 1) {
        printf("\n--- EXIT DOOR ---\n");
        printf("You use the key and solve the  puzzle...\n");
        printf("DOOR OPENED! YOU ESCAPED!\n");
        printf("CONGRATULATIONS!\n");
        exit(0);
    } else {
        printf("\nDoor is locked. You need:\n");
        if (p->hasKey == 0)
            printf("- A key\n");
        if (p->hasClue == 0)
            printf("- A clue\n");
    }
}