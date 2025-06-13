#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 100
#define MAX_NAME_LEN 50

// Exercise categories
const char *exercise_types[5][3] = {
    {"Running", "Cycling", "Fast Walking"},        // Cardio
    {"Push-ups", "Squats", NULL},                  // Full-body Strength
    {"Leg Press", "Leg Curl", NULL},               // Lower-body Strength
    {"Pull-ups", "Chin-ups", NULL},                // Upper-body Strength
    {"Plank", "Crunches", NULL}                    // Core Strength (only once a week)
};

const char *days[6] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Member structure
typedef struct {
    char real_name[MAX_NAME_LEN];
    char nickname[MAX_NAME_LEN];
} Member;

typedef struct {
    const char *cardio;
    const char *strength;
} Routine;

typedef struct {
    char member_name[MAX_NAME_LEN];
    Routine daily[6]; // Monday to Saturday
    int core_used;
} MemberRoutine;

// Global members and routines
Member milliways_members[MAX_MEMBERS];
MemberRoutine member_routines[MAX_MEMBERS];
int member_count = 0;

// Sample function to add a member (for testing/demo)
void addSampleMembers() {
    strcpy(milliways_members[0].real_name, "John Doe");
    strcpy(milliways_members[0].nickname, "StarRunner");
    strcpy(member_routines[0].member_name, "John Doe");
    member_routines[0].core_used = 0;

    strcpy(milliways_members[1].real_name, "Alice Moon");
    strcpy(milliways_members[1].nickname, "LunarQueen");
    strcpy(member_routines[1].member_name, "Alice Moon");
    member_routines[1].core_used = 0;

    member_count = 2;
}

void displayMembers() {
    printf("==== Milliways Members ====\n");
    for (int i = 0; i < member_count; i++) {
        printf("%s (%s)\n", milliways_members[i].real_name, milliways_members[i].nickname);
    }
}

int findMemberIndex(const char *name) {
    for (int i = 0; i < member_count; i++) {
        if (strcmp(milliways_members[i].real_name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void setExerciseRoutine() {
    char name[MAX_NAME_LEN];
    printf("Enter member name: ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;

    int idx = findMemberIndex(name);
    if (idx == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("Setting routine for %s\n", milliways_members[idx].real_name);

    for (int i = 0; i < 6; i++) {
        printf("Day: %s\n", days[i]);

        printf("Select Cardio Exercise [0: Running, 1: Cycling, 2: Fast Walking]: ");
        int cardio_choice;
        scanf("%d", &cardio_choice);
        getchar();
        member_routines[idx].daily[i].cardio = exercise_types[0][cardio_choice];

        int strength_category;
        printf("Select Strength/Core Category [1: Full-body, 2: Lower-body, 3: Upper-body, 4: Core]: ");
        scanf("%d", &strength_category);
        getchar();

        if (strength_category == 4) {
            if (member_routines[idx].core_used) {
                printf("Core exercise already used this week. Choose another category.\n");
                i--;
                continue;
            } else {
                member_routines[idx].core_used = 1;
            }
        }

        int strength_choice;
        printf("Select Exercise [0 or 1]: ");
        scanf("%d", &strength_choice);
        getchar();
        member_routines[idx].daily[i].strength = exercise_types[strength_category][strength_choice];
    }
    printf("Routine set successfully for %s.\n", name);
}

void getExerciseRoutine() {
    char name[MAX_NAME_LEN];
    printf("Enter member name to view routine: ");
    fgets(name, MAX_NAME_LEN, stdin);
    name[strcspn(name, "\n")] = 0;

    int idx = findMemberIndex(name);
    if (idx == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("\nMember: %s\nNickname: %s\n", milliways_members[idx].real_name, milliways_members[idx].nickname);
    for (int i = 0; i < 6; i++) {
        printf("%s:\n", days[i]);
        printf("  - Cardio: %s\n", member_routines[idx].daily[i].cardio);
        printf("  - Strength/Core: %s\n", member_routines[idx].daily[i].strength);
    }
}

void showMenu() {
    printf("\n==== Magrathea Training Menu ====\n");
    printf("1. List Members\n");
    printf("2. Set Basic Workout Routine\n");
    printf("3. View Basic Workout Routine\n");
    printf("0. Exit\n");
}

int main() {
    addSampleMembers();

    int choice;
    do {
        showMenu();
        printf("Select an option: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) {
            case 1:
                displayMembers();
                break;
            case 2:
                setExerciseRoutine();
                break;
            case 3:
                getExerciseRoutine();
                break;
            case 0:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}
