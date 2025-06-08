#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #define CLEAR "cls"
    #define SLEEP "timeout /t 3 > nul"
#else
    #define CLEAR "clear"
    #define SLEEP "sleep 3"
#endif

int main() {
    char date[11];       // yyyy-mm-dd + '\0'
    char name[100];

    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    scanf("%10s", date);

    printf("[Please enter your name]: ");
    getchar(); // clear leftover newline
    fgets(name, sizeof(name), stdin);

    // Remove newline character from name if it exists
    for (int i = 0; name[i] != '\0'; i++) {
        if (name[i] == '\n') {
            name[i] = '\0';
            break;
        }
    }

    printf("**The input has been processed successfully.**\n");

    // Wait for 3 seconds
    system(SLEEP);

    // Clear the screen
    system(CLEAR);

    // Print the top border
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    // Print triangle lines with splash text
    for (int i = 1; i <= 5; i++) {
        // Left triangle
        for (int j = 0; j < i; j++) {
            printf("*");
        }

        // Main splash lines
        switch (i) {
            case 1:
                printf("%*s[Magrathea ver 0.1]%*s", 43, "", 35, "");
                break;
            case 2:
                printf("%*sMagrathea, where a shining planet is created in a wasteland with no grass,%*s", 14, "", 14, "");
                break;
            case 3:
                printf("%*sa place where unseen potential is discovered and gems are polished by the hands of experts,%*s", 11, "", 7, "");
                break;
            case 4:
                printf("%*sWelcome to Magrathea.%*s", 44, "", 31, "");
                break;
            case 5:
                printf("%*s", 98, "");  // Empty line padding
                break;
        }

        // Right inverted triangle
        for (int k = 0; k <= 5 - i; k++) {
            printf("*");
        }

        printf("\n");
    }

    // Print bottom border
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    // User and execution info
    printf("[User]: %s%*s[Execution Time]: %s\n", name, 43 - (int)strlen(name), "", date);
    printf("=============================================================================================================\n");

    return 0;
}
