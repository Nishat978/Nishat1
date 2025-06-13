#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MEMBERS 10
#define MAX_RESPONSES 3
#define MAX_TRAUMA_LEN 256
#define MAX_RESPONSE_LEN 100
#define MAX_NAME_LEN 50

// Member structure
struct Member {
    char nickname[MAX_NAME_LEN];
    int age;
};

// Trauma structure
struct Trauma {
    char nickname[MAX_NAME_LEN];
    int age;
    char description[MAX_TRAUMA_LEN];
    int hasTrauma;
};

// Counseling question structure
struct Question {
    int id;
    char content[150];
};

// Counseling response structure
struct Counseling {
    char nickname[MAX_NAME_LEN];
    char question[150];
    char response[MAX_RESPONSE_LEN];
};

struct Member members[MAX_MEMBERS] = {
    {"StarKid", 17},
    {"Nova", 18},
    {"Blaze", 19},
    {"Echo", 20},
    {"Zephyr", 18},
};

struct Trauma traumaData[MAX_MEMBERS];
struct Counseling counselingData[MAX_MEMBERS * MAX_RESPONSES];
int counselingCount = 0;

const struct Question questions[5] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

void inputTrauma() {
    char inputNick[MAX_NAME_LEN];
    int found = 0;
    while (1) {
        printf("\nEnter nickname (or 'exit' to stop): ");
        scanf("%s", inputNick);
        if (strcmp(inputNick, "exit") == 0) break;

        for (int i = 0; i < MAX_MEMBERS; ++i) {
            if (strcmp(members[i].nickname, inputNick) == 0) {
                printf("Enter trauma description: ");
                getchar(); // clear newline
                fgets(traumaData[i].description, MAX_TRAUMA_LEN, stdin);
                traumaData[i].description[strcspn(traumaData[i].description, "\n")] = 0;
                strcpy(traumaData[i].nickname, members[i].nickname);
                traumaData[i].age = members[i].age;
                traumaData[i].hasTrauma = 1;
                printf("Trauma recorded for %s.\n", inputNick);
                found = 1;
                break;
            }
        }
        !found ? printf("Nickname not found. Try again.\n") : (found = 0);
    }
}

void counselingSession() {
    char inputNick[MAX_NAME_LEN];
    printf("\nMembers with trauma:\n");
    for (int i = 0; i < MAX_MEMBERS; ++i) {
        if (traumaData[i].hasTrauma)
            printf("- %s\n", traumaData[i].nickname);
    }
    printf("Select a nickname: ");
    scanf("%s", inputNick);

    int memberIndex = -1;
    for (int i = 0; i < MAX_MEMBERS; ++i) {
        if (strcmp(traumaData[i].nickname, inputNick) == 0 && traumaData[i].hasTrauma) {
            memberIndex = i;
            break;
        }
    }
    if (memberIndex == -1) {
        printf("Nickname not found or no trauma data.\n");
        return;
    }

    srand(time(NULL));
    int selected[3];
    for (int i = 0; i < 3;) {
        int r = rand() % 5;
        int duplicate = 0;
        for (int j = 0; j < i; ++j) if (selected[j] == r) duplicate = 1;
        if (!duplicate) selected[i++] = r;
    }

    getchar(); // clear input
    for (int i = 0; i < 3; ++i) {
        printf("%s\n> ", questions[selected[i]].content);
        char temp[MAX_RESPONSE_LEN];
        fgets(temp, MAX_RESPONSE_LEN, stdin);
        temp[strcspn(temp, "\n")] = 0;
        while (strlen(temp) == 0 || strlen(temp) > 100) {
            printf("Invalid. Please limit to 100 characters.\n> ");
            fgets(temp, MAX_RESPONSE_LEN, stdin);
            temp[strcspn(temp, "\n")] = 0;
        }
        strcpy(counselingData[counselingCount].nickname, inputNick);
        strcpy(counselingData[counselingCount].question, questions[selected[i]].content);
        strcpy(counselingData[counselingCount].response, temp);
        counselingCount++;
    }
    printf("Counseling session completed for %s.\n", inputNick);
}

void viewSession() {
    char inputNick[MAX_NAME_LEN];
    printf("\nEnter nickname to view session: ");
    scanf("%s", inputNick);
    for (int i = 0; i < MAX_MEMBERS; ++i) {
        if (strcmp(traumaData[i].nickname, inputNick) == 0 && traumaData[i].hasTrauma) {
            printf("Nickname: %s\nTrauma: %s\n", traumaData[i].nickname, traumaData[i].description);
            for (int j = 0; j < counselingCount; ++j) {
                if (strcmp(counselingData[j].nickname, inputNick) == 0) {
                    printf("Q: %s\nA: %s\n", counselingData[j].question, counselingData[j].response);
                }
            }
            return;
        }
    }
    printf("Nickname not found or no trauma data.\n");
}

void overcomeTrauma() {
    char option;
    do {
        printf("\n[Trauma Management Menu]\nA. Input Trauma\nB. Counseling Session\nC. View Session\nX. Exit\nSelect: ");
        scanf(" %c", &option);
        switch (option) {
            case 'A': case 'a': inputTrauma(); break;
            case 'B': case 'b': counselingSession(); break;
            case 'C': case 'c': viewSession(); break;
        }
    } while (option != 'X' && option != 'x');
}

int main() {
    overcomeTrauma();
    return 0;
}
