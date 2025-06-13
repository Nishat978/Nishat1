/* Trauma Management with Arthur's Easter Egg - ANSI C Standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_MEMBERS 10
#define MAX_RESPONSES 30
#define MAX_LENGTH 100

// ---------------- Structures ------------------
typedef struct {
    char nickname[20];
    int age;
    char trauma[MAX_LENGTH];
} Trauma;

typedef struct {
    int id;
    char question[MAX_LENGTH];
} CounselingQuestion;

typedef struct {
    char nickname[20];
    char question[MAX_LENGTH];
    char response[MAX_LENGTH];
} CounselingResponse;

typedef struct {
    char keyword[10];
    char message[300];
} ArthurEasterEgg;

// ---------------- Global Variables ------------------
Trauma traumaList[MAX_MEMBERS];
CounselingResponse responseList[MAX_RESPONSES];
int traumaCount = 0;
int responseCount = 0;

CounselingQuestion questions[] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

ArthurEasterEgg arthur = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
};

// ---------------- Utility Functions ------------------
int isRightChar(char userInput[], char reversedBinary[][9]) {
    for (int i = 0; i < 7; i++) {
        char bin[9];
        unsigned char c = userInput[i];
        for (int j = 7; j >= 0; j--) {
            bin[7 - j] = ((c >> j) & 1) + '0';
        }
        bin[8] = '\0';
        if (strcmp(bin, reversedBinary[i]) != 0) return 0;
    }
    return 1;
}

int isEasterEgg(char input[]) {
    return strcmp(input, arthur.keyword) == 0;
}

void toBinary(char c, char *bin) {
    for (int i = 7; i >= 0; i--) {
        bin[7 - i] = ((c >> i) & 1) + '0';
    }
    bin[8] = '\0';
}

void reverseString(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void find_easter_egg() {
    printf("<<Arthur's Easter Egg>>\n");
    char reversed[8];
    strcpy(reversed, arthur.keyword);
    reverseString(reversed);

    char reversedBinary[7][9];
    for (int i = 0; i < 7; i++) {
        toBinary(reversed[i], reversedBinary[i]);
        printf("%s\n", reversedBinary[i]);
    }

    char inputChars[8];
    printf("Enter the characters corresponding to these binary codes (7 letters): ");
    scanf("%7s", inputChars);

    if (isRightChar(inputChars, reversedBinary)) {
        char finalInput[10];
        printf("Correct! Now combine the characters into a word: ");
        scanf("%s", finalInput);

        if (isEasterEgg(finalInput)) {
            printf("##Easter Egg Discovered!$$\n");
            printf("%s\n", arthur.message);
        } else {
            printf("Incorrect keyword. Returning to menu.\n");
        }
    } else {
        printf("Incorrect characters. Try again later.\n");
    }
}

// ---------------- Trauma Management ------------------
void inputTrauma() {
    char nickname[20], trauma[MAX_LENGTH];
    int found;

    while (1) {
        printf("Enter nickname (or 'exit' to return): ");
        scanf("%s", nickname);
        if (strcmp(nickname, "exit") == 0) break;

        found = 0;
        for (int i = 0; i < MAX_MEMBERS; i++) {
            if (strcmp(traumaList[i].nickname, nickname) == 0) {
                printf("Enter trauma description: ");
                getchar();
                fgets(trauma, MAX_LENGTH, stdin);
                trauma[strcspn(trauma, "\n")] = 0;
                strcpy(traumaList[i].trauma, trauma);
                traumaCount++;
                found = 1;
                break;
            }
        }
        (found) ? printf("Trauma saved.\n") : printf("Nickname not found. Try again.\n");
    }
}

void startCounseling() {
    if (traumaCount == 0) {
        printf("No trauma data.\n");
        return;
    }

    printf("Members with trauma:\n");
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strlen(traumaList[i].trauma) > 0)
            printf("- %s\n", traumaList[i].nickname);
    }

    char selected[20];
    printf("Select a nickname for counseling: ");
    scanf("%s", selected);

    int found = 0;
    for (int i = 0; i < MAX_MEMBERS && responseCount < MAX_RESPONSES; i++) {
        if (strcmp(traumaList[i].nickname, selected) == 0 && strlen(traumaList[i].trauma) > 0) {
            found = 1;
            printf("Counseling session for %s\n", selected);
            int asked[5] = {0};
            srand(time(NULL));

            for (int q = 0; q < 3; ) {
                int r = rand() % 5;
                if (asked[r]) continue;
                asked[r] = 1;

                printf("Q%d: %s\n", questions[r].id, questions[r].question);
                char response[MAX_LENGTH];
                getchar();
                fgets(response, MAX_LENGTH, stdin);
                response[strcspn(response, "\n")] = 0;

                if (strlen(response) == 0 || strlen(response) > 100) {
                    printf("Invalid response. Please enter again.\n");
                    continue;
                }

                strcpy(responseList[responseCount].nickname, selected);
                strcpy(responseList[responseCount].question, questions[r].question);
                strcpy(responseList[responseCount].response, response);
                responseCount++;
                q++;
            }
            break;
        }
    }

    if (!found) {
        printf("Nickname not found or no trauma data.\n");
    } else {
        printf("Counseling completed for %s\n", selected);
    }
}

void viewSessionByNickname() {
    char nickname[20];
    printf("Enter nickname to view session: ");
    scanf("%s", nickname);
    int shown = 0;
    for (int i = 0; i < MAX_MEMBERS; i++) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) {
            printf("Nickname: %s\nTrauma: %s\n", nickname, traumaList[i].trauma);
            for (int j = 0; j < responseCount; j++) {
                if (strcmp(responseList[j].nickname, nickname) == 0) {
                    printf("Q: %s\nA: %s\n", responseList[j].question, responseList[j].response);
                }
            }
            shown = 1;
            break;
        }
    }
    if (!shown) printf("No session data for this nickname.\n");
}

void overcomeTrauma() {
    while (1) {
        char input[20];
        printf("\n--- Trauma Management ---\n");
        printf("A. Input Trauma\nB. Start Counseling\nC. View Session\nD. Exit\n> ");
        scanf("%s", input);

        if (strcmp(input, "A") == 0 || strcmp(input, "a") == 0) inputTrauma();
        else if (strcmp(input, "B") == 0 || strcmp(input, "b") == 0) startCounseling();
        else if (strcmp(input, "C") == 0 || strcmp(input, "c") == 0) viewSessionByNickname();
        else if (strcmp(input, "D") == 0 || strcmp(input, "d") == 0) break;
        else if (strcmp(input, "Arthur") == 0) find_easter_egg();
        else printf("Invalid input. Try again.\n");
    }
}

// -------------- Initialize --------------
void initTraumaMembers() {
    strcpy(traumaList[0].nickname, "Luna"); traumaList[0].age = 19;
    strcpy(traumaList[1].nickname, "Kai"); traumaList[1].age = 20;
    strcpy(traumaList[2].nickname, "Sera"); traumaList[2].age = 18;
    // Add more as needed
}

int main() {
    initTraumaMembers();
    overcomeTrauma();
    return 0;
}
