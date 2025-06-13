#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 8
#define MAX_NAME_LEN 50

// Struct for Mentor
typedef struct {
    int id;                         // Unique ID (1–8)
    char name[MAX_NAME_LEN];       // Mentor name
    int mentee_index;              // Index of matched trainee
} Mentor;

// Trainee data (name and nickname)
char trainee_names[MAX_TRAINEES][MAX_NAME_LEN] = {
    "Elena Spark",
    "Dax Flame",
    "Nova Stone",
    "Kai Shadow",
    "Rhea Steel",
    "Zane Vortex",
    "Luna Skye",
    "Jett Blaze"
};

char trainee_nicknames[MAX_TRAINEES][MAX_NAME_LEN] = {
    "Sparkz", "Inferno", "NovaX", "Shade", "IronHeart", "Whirl", "MoonRay", "Blazer"
};

// Abilities and ID (ASCII sum of nickname)
int trainee_id[MAX_TRAINEES];
int trainee_abilities[MAX_TRAINEES];

// Mentor list
Mentor mentors[MAX_TRAINEES];
int mentor_count = 0;

// Function to convert nickname to ASCII sum
int parseIntMember(const char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i] != '\0'; i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

// Function to generate random ability score (100–1000)
int getRandomAbility() {
    return (rand() % 901) + 100; // 100 to 1000
}

// Initialize trainee data
void initializeTrainees() {
    for (int i = 0; i < MAX_TRAINEES; i++) {
        trainee_id[i] = parseIntMember(trainee_nicknames[i]);
        trainee_abilities[i] = getRandomAbility();
    }
    printf("Trainee data initialized.\n");
}

// Input up to 8 mentors
void inputMentors() {
    char name[MAX_NAME_LEN];
    mentor_count = 0;
    printf("Enter 8 mentor names:\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        printf("Mentor %d: ", i + 1);
        fgets(name, MAX_NAME_LEN, stdin);
        name[strcspn(name, "\n")] = 0;
        mentors[i].id = i + 1;
        strcpy(mentors[i].name, name);
        mentors[i].mentee_index = -1; // Initialize
        mentor_count++;
    }
    printf("Mentors registered successfully.\n");
}

// Match trainees to mentors based on ID % 8
void matchMentoring() {
    int used_mentors[MAX_TRAINEES] = {0};
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int mentor_index = i % MAX_TRAINEES;
        // Ensure 1:1 mapping (bonus)
        while (used_mentors[mentor_index]) {
            mentor_index = (mentor_index + 1) % MAX_TRAINEES;
        }
        mentors[mentor_index].mentee_index = i;
        used_mentors[mentor_index] = 1;
    }
    printf("Mentoring matches assigned (1:1).\n");
}

// Output mentoring results
void printMentorResults() {
    printf("\n==== Mentoring Matches ====\n");
    for (int i = 0; i < MAX_TRAINEES; i++) {
        int trainee_idx = mentors[i].mentee_index;
        if (trainee_idx != -1) {
            printf("Trainee [%d] %s (Nick: %s, ASCII Sum: %d, Ability: %d)\n",
                   trainee_idx + 1,
                   trainee_names[trainee_idx],
                   trainee_nicknames[trainee_idx],
                   trainee_id[trainee_idx],
                   trainee_abilities[trainee_idx]);
            printf("  -> Mentor [%d] %s\n", mentors[i].id, mentors[i].name);
        } else {
            printf("Mentor [%d] %s has no assigned mentee.\n", mentors[i].id, mentors[i].name);
        }
    }
}

// Menu
void showMenu() {
    printf("\n===== Self-Management & Teamwork > Mentoring =====\n");
    printf("1. Initialize Trainee Data\n");
    printf("2. Register Mentors\n");
    printf("3. Match Mentoring\n");
    printf("4. View Matches\n");
    printf("0. Exit\n");
}

int main() {
    srand(time(NULL)); // Seed RNG

    int choice;
    do {
        showMenu();
        printf("Choose option: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch (choice) {
            case 1:
                initializeTrainees();
                break;
            case 2:
                inputMentors();
                break;
            case 3:
                matchMentoring();
                break;
            case 4:
                printMentorResults();
                break;
            case 0:
                printf("Goodbye.\n");
                break;
            default:
                printf("Invalid selection.\n");
        }
    } while (choice != 0);

    return 0;
}
