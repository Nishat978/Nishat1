#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRAINING_STAGES 8

// One-dimensional arrays used for constraints
char *main_menu[] = {
    "I. Audition Management",
    "II. Training",
    "III. Debut"
};

char *training_menu[] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

char training_results[MAX_TRAINING_STAGES] = {'-', '-', '-', '-', '-', '-', '-', '-'};

void display_main_menu() {
    printf("\n####################################\n");
    printf("#            MAIN MENU             #\n");
    printf("####################################\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s\n", i + 1, main_menu[i]);
    }
    printf("Enter your choice (1-3), 0 or Q to quit: ");
}

void display_training_menu() {
    printf("\n####################################\n");
    printf("#         TRAINING STAGES          #\n");
    printf("####################################\n");
    for (int i = 0; i < MAX_TRAINING_STAGES; i++) {
        printf("%d. %s [Status: %c]\n", i + 1, training_menu[i], training_results[i]);
    }
    printf("Enter stage number (1-8), or 0 to return to main menu: ");
}

void handle_training_stage(int stage) {
    char choice;
    if (training_results[stage - 1] == 'P') {
        printf("You have already passed this stage.\n");
        return;
    }

    // Rule: Stages 1 and 2 must be completed in order
    if (stage == 2 && training_results[0] != 'P') {
        printf("You must complete Stage 1 before attempting Stage 2.\n");
        return;
    }
    if (stage > 2 && (training_results[0] != 'P' || training_results[1] != 'P')) {
        printf("You must pass Stages 1 and 2 before accessing higher stages.\n");
        return;
    }

    printf("Would you like to enter the evaluation result? (Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'Y') {
        printf("Did you complete the training and pass the certification? (Y for Pass / N for Fail): ");
        scanf(" %c", &choice);
        if (choice == 'Y') {
            training_results[stage - 1] = 'P';
            printf("Stage %d marked as Passed.\n", stage);
        } else {
            training_results[stage - 1] = 'F';
            printf("Stage %d marked as Failed.\n", stage);
        }
    }
}

void training_system() {
    int stage;
    while (1) {
        display_training_menu();
        if (scanf("%d", &stage) != 1) {
            while (getchar() != '\n');
            continue;
        }
        if (stage == 0) break;
        if (stage >= 1 && stage <= MAX_TRAINING_STAGES) {
            handle_training_stage(stage);
        } else {
            printf("Invalid stage. Please select between 1-8.\n");
        }
    }
}

int main() {
    char input[10];
    int choice;

    while (1) {
        display_main_menu();
        scanf("%s", input);

        if (input[0] == '0' || input[0] == 'Q' || input[0] == 'q' || input[0] == '\0') {
            printf("Exiting program.\n");
            break;
        }

        choice = atoi(input);

        switch (choice) {
            case 1:
                printf("Audition Management system not implemented yet.\n");
                break;
            case 2:
                training_system();
                break;
            case 3:
                printf("Debut system not implemented yet.\n");
                break;
            default:
                printf("Invalid menu option. Try again.\n");
        }
    }
    return 0;
}
