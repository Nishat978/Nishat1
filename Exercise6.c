#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 5
#define MAX_TESTS 7
#define MAX_STRING 50

// Fitness test names
const char *fitnessTests[MAX_TESTS] = {
    "1-Mile Running Test (min)",
    "Speed Sprint (sec)",
    "Push-ups (min for 30 reps)",
    "Squats (min for 50 reps)",
    "Arm Strength (min for 50 push-ups)",
    "Swimming (min for 400m)",
    "Weightlifting (bodyweight multiplier)"
};

// Member data
char memberNames[MAX_MEMBERS][MAX_STRING] = {
    "Goeun", "Woncheol", "Youngjin", "Hyekyung", "Arthur"
};
char memberNicknames[MAX_MEMBERS][MAX_STRING] = {
    "Eun", "Chul", "Jin", "Kyun", "Art"
};

// Health scores [nickname, test1, test2, ..., test7]
char healthScores[MAX_MEMBERS][MAX_TESTS + 1][MAX_STRING];

// Utility: Find member index by nickname
int findMemberIndex(const char *nickname) {
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(nickname, memberNicknames[i]) == 0) {
            return i;
        }
    }
    return -1;
}

// Parsing and storing health data
void setHealth() {
    printf("\n--- Enter Fitness Data ---\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        printf("Enter data for %s (%s):\n", memberNames[i], memberNicknames[i]);
        printf("Format: test1,test2,test3,test4,test5,test6,test7\n> ");

        char input[200];
        fgets(input, sizeof(input), stdin);

        // Remove newline
        input[strcspn(input, "\n")] = 0;

        // Tokenize input
        char *token = strtok(input, ",");
        int count = 0;

        strcpy(healthScores[i][0], memberNicknames[i]); // Store nickname

        while (token != NULL && count < MAX_TESTS) {
            strcpy(healthScores[i][count + 1], token);
            token = strtok(NULL, ",");
            count++;
        }

        if (count != MAX_TESTS) {
            printf("Invalid input. Please enter 7 values.\n");
            i--; // redo this member
        }
    }
    printf("Fitness data recorded successfully.\n");
}

// Viewing health data
void getHealth() {
    printf("\n--- View Fitness Data ---\n");
    printf("Enter member nickname (or 'all' to view all): ");
    
    char nickname[MAX_STRING];
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = 0;

    if (strcmp(nickname, "all") == 0) {
        for (int i = 0; i < MAX_MEMBERS; i++) {
            printf("\nName: %s\nNickname: %s\n", memberNames[i], memberNicknames[i]);
            for (int j = 0; j < MAX_TESTS; j++) {
                printf("%d. %s: %s\n", j + 1, fitnessTests[j], healthScores[i][j + 1]);
            }
        }
    } else {
        int index = findMemberIndex(nickname);
        if (index == -1) {
            printf("Member not found.\n");
            return;
        }
        printf("\nName: %s\nNickname: %s\n", memberNames[index], memberNicknames[index]);
        for (int j = 0; j < MAX_TESTS; j++) {
            printf("%d. %s: %s\n", j + 1, fitnessTests[j], healthScores[index][j + 1]);
        }
    }
}

// Training Stage 1 submenu
void trainingStage1Menu() {
    while (1) {
        printf("\n[Stage 1] Physical Strength & Knowledge\n");
        printf("A. Enter Fitness Data\n");
        printf("B. View Fitness Data\n");
        printf("Q. Back to Main Menu\n");
        printf("Select option: ");

        char option;
        scanf(" %c", &option);
        getchar(); // flush newline

        if (option == 'A' || option == 'a') {
            setHealth();
        } else if (option == 'B' || option == 'b') {
            getHealth();
        } else if (option == 'Q' || option == 'q') {
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }
    }
}

// Main menu
int main() {
    while (1) {
        printf("\n===== Main Menu =====\n");
        printf("I. Audition Management\n");
        printf("II. Training\n");
        printf("III. Debut\n");
        printf("0. Exit\n");
        printf("Select option: ");

        char input[10];
        fgets(input, sizeof(input), stdin);

        if (input[0] == '0' || input[0] == 'Q' || input[0] == 'q' || input[0] == '\n') {
            printf("Exiting program.\n");
            break;
        } else if (input[0] == 'I' || input[0] == 'i') {
            printf("Audition Management not implemented.\n");
        } else if (input[0] == 'I' && input[1] == 'I') {
            printf("Redirecting to Training...\n");
        } else if (input[0] == 'I' || input[0] == 'i') {
            printf("Training not implemented.\n");
        } else if (input[0] == 'I' && input[1] == 'I') {
            // Training menu simplified for this task
            printf("\n[II. Training]\n");
            trainingStage1Menu();
        } else {
            printf("Invalid input. Try again.\n");
        }
    }

    return 0;
}
