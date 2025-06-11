#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define INFO_FIELDS 7
#define MAX_LENGTH 256

int main() {
    char project_name[MAX_LENGTH];
    int total_judges, selected_members;
    char judges_array[MAX_JUDGES][MAX_LENGTH];
    int judge_count = 0;

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = '\0'; // Remove newline

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // consume newline after number input

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    while (judge_count < total_judges) {
        printf("\nJudge %d: ", judge_count + 1);
        fgets(judges_array[judge_count], sizeof(judges_array[judge_count]), stdin);

        // Count commas to validate correct field count
        int comma_count = 0;
        for (int i = 0; judges_array[judge_count][i] != '\0'; i++) {
            if (judges_array[judge_count][i] == ',')
                comma_count++;
        }

        if (comma_count != INFO_FIELDS - 1) {
            printf("The input items are incorrect. Please enter them again.\n");
            continue;
        }

        judge_count++;
    }

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    char check;
    printf("\"Should we check the judge information?\" (Y/N): ");
    scanf(" %c", &check);
    if (check != 'Y') {
        printf("Program terminated.\n");
        return 0;
    }

    printf("\n####################################\n");
    printf("#        Display Judge Data        #\n");
    printf("####################################\n");

    for (int i = 0; i < total_judges; i++) {
        char *token;
        char temp[MAX_LENGTH];
        strcpy(temp, judges_array[i]);

        printf("[Judge %d]\n", i + 1);
        token = strtok(temp, ",");
        if (token) printf("Name: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Gender: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Affiliation: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Title: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Expertise: %s\n", token);
        token = strtok(NULL, ",");
        if (token) printf("Email: %s\n", token);
        token = strtok(NULL, ",\n");
        if (token) printf("Phone: %s\n", token);
        printf("-----------------------------------\n");
    }

    return 0;
}
