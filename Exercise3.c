#include <stdio.h>
#include <stdlib.h>

#define NUM_CANDIDATES 6
#define MAX 100

int main(void)
{
    char group_name[MAX];
    char member_info[NUM_CANDIDATES][11][MAX] = {
        {"Jiyeon Park", "2006/04/15", "F", "jiyeon@outlook.com", "South Korea", "18.5", "Dance", "Composition", "0", "ENFJ", "A passionate and creative dancer and composer ready to pursue dreams together."},
        {"Ethan Smith", "2005/08/22", "M", "ethan@outlook.com", "USA", "21.2", "Vocal", "Lyric Writing", "2", "ISTP", "A vocalist with a rich voice and songwriting skills, eager to share K-POP’s charm worldwide."},
        {"Suphanan Wong", "2004/01/05", "F", "suphanan@outlook.com", "Thailand", "19.0", "Dance", "Lyric Writing", "4", "INFJ", "Aspiring to move hearts with dynamic dance and emotional lyrics, becoming part of the Hallyu wave from Thailand."},
        {"Helena Silva", "2007/03/10", "F", "helena@outlook.com", "Brazil", "20.8", "Vocal", "Composition & Lyric Writing", "1", "ENFP", "A versatile singer from Brazil who wants to inspire through both music and lyrics."},
        {"Karolina Nowak", "2006/09/18", "F", "karolina@outlook.com", "Poland", "17.9", "Dance", "Composition", "2", "ISFP", "A composer and dancer from Poland, eager to convey emotions through music."},
        {"Liam Wilson", "2006/11/08", "M", "liam@outlook.com", "Australia", "20.1", "Dance", "Composition & Lyric Writing", "3", "ENTJ", "A passionate dancer and composer from Australia, determined to share his unique music through K-POP."}
    };

    int candidate01[11], candidate02[11], candidate03[11], candidate04[11], candidate05[11], candidate06[11];

    printf("Enter audition group name: ");
    int ch, idx = 0;
    while ((ch = getchar()) != '\n' && idx < MAX - 1)
        group_name[idx++] = ch;
    group_name[idx] = '\0';

    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Review \n", group_name);
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("Name (Age)       | DOB       | Gender | Email                 | Nationality | BMI  | Primary Skill | Secondary Skill       | TOPIK   | MBTI |\n");
    printf("=============================================================================================\n");

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        int year, age;
        sscanf(member_info[i][1], "%d", &year);
        age = 2025 - year;

        printf("%-15s (%2d) | %-10s | %-6s | %-22s | %-11s | %-4s | %-13s | %-21s | ",
               member_info[i][0], age, member_info[i][1], member_info[i][2], member_info[i][3],
               member_info[i][4], member_info[i][5], member_info[i][6], member_info[i][7]);

        if (member_info[i][8][0] == '0')
            printf("Native  ");
        else
            printf("%-7s", member_info[i][8]);

        printf(" | %-4s |\n", member_info[i][9]);
        printf("---------------------------------------------------------------------------------------------\n");
        printf("%s\n", member_info[i][10]);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
