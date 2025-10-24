#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct Voter {
    char name[50];
    char nic[13];
    int age;
}; 
void display();
void voter_menu();
void register_voter();  
int check_voter_age(int day, int month, int year);
void save_voter_data(struct Voter newvoter);
void vote();
   




void voter_menu() {
    int choice;
    printf("\033[1;33m\n\n\t\t\tVOTER MENU\033[0m\n\n");
    printf("\033[1;34m\t\t\t1. Register as a Voter\n");
    printf("\t\t\t2. Vote\n");
    printf("\t\t\t3. Back to Main Menu\033[0m\n");
    printf("\n\t\t\tChoose an option: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            register_voter();
            break;
        case 2:
            vote();
            break;
        case 3:
            display();
            break;
        default:
            printf("\033[1;31m\n\t\t\t\t\tInvalid option.\033[0m\n");
            voter_menu();
            break;
    }
}

void register_voter() {
    struct Voter newVoter;
    int day, month, year;

    printf("\033[1;33m\n\n\t\t\tVOTER REGISTRATION\033[0m\n\n");
    printf("\033[1;34m\t\t\tEnter your Name:\033[0m ");
    while (getchar() != '\n');
    fgets(newVoter.name, sizeof(newVoter.name), stdin);
    newVoter.name[strcspn(newVoter.name, "\n")] = 0;

    printf("\033[1;34m\t\t\t12 Digit NIC Number :\033[0m ");
    scanf("%s", newVoter.nic);

    printf("\033[1;34m\t\t\tDate Of Birth (Day Month Year):\033[0m ");
    scanf("%d %d %d", &day, &month, &year);

    if (check_voter_age(day, month, year)) {
        save_voter_data(newVoter);
    } else {
        printf("\033[1;33m\n\t\t\t\t\tYou are not eligible.\033[0m\n");
    }
    voter_menu();
}

int check_voter_age(int day, int month, int year) {
    int current_year = 2025; 
    int current_month = 10;
    int current_day = 26;
    int age = current_year - year;

    if (current_month < month || (current_month == month && current_day < day)) {
        age--;
    }
    return age >= 18;
}

void save_voter_data(struct Voter newvoter) {
    FILE *fptr;
    fptr = fopen("voters.txt", "a");

    if (fptr == NULL) {
        printf("\033[1;31m\t\t\t\t\tError\033[0m\n");
        return;
    }

    fprintf(fptr, "Name: %s, NIC: %s\n", newvoter.name, newvoter.nic);
    fclose(fptr);
    printf("\033[1;32m\n\t\t\t\t\t Registration successful!\033[0m\n");
}

void vote() {
    char nic_check[13];
    int candidate_number;
    char line[256];
    int found = 0;

    printf("\033[1;033m\n\n\t\t\tVOTING PAGE\033[0m\n\n");
   
    printf("\033[1;34m\t\t\tEnter your NIC number to validate:\033[0m");
    scanf("%s", nic_check);

    //check voter registered and not voted
    FILE *voters_file = fopen("voters.txt", "r");
    FILE *voted_file = fopen("voted.txt", "r");
    if (voters_file == NULL) {

        printf("\033[1;32m\t\t\t\t\tNo registered voters found.\033[0m\n");
        return;
    }

    // Check if NIC is available
    while (fgets(line, sizeof(line), voters_file)) {
        if (strstr(line, nic_check) != NULL) {
            found = 1;
            break;
        }
    }
    fclose(voters_file);

    if (found!= 1) {
        printf("\033[1;031m\n\t\t\t\t\tYou are not a registered voter.\033[0m\n");
        return;
    }

    // Check if NIC is already voted
    if (voted_file != NULL) {
        while (fgets(line, sizeof(line), voted_file)) {
            if (strstr(line, nic_check) != NULL) {
                printf("\033[1;33m\n\t\t\t\t\tYou have already voted.\033[0m\n");
                fclose(voted_file);
                return;
            }
        }
        fclose(voted_file);
    }

    // Display candidates to vote
    printf("\n\t\t\t\t\tCandidates available:\n");
    FILE *candidates_file = fopen("candi_data.txt", "r");
    if (candidates_file == NULL) {
        printf("\033[1;31m\t\t\t\t\tNo candidates have registered yet.\033[1;0m\n");
        return;
    }
    while (fgets(line, sizeof(line), candidates_file)) {
        printf("\t\t\t\t\t%s", line);
    }
    fclose(candidates_file);

    printf("\033[1;34m\n\t\t\tEnter the number of the candidate you want to vote for:\033[0m ");
    scanf("%d", &candidate_number);

   // save vot to the text file
    FILE *votes_file = fopen("votes.txt", "a");
    FILE *voted_record = fopen("voted.txt", "a");

    if (votes_file == NULL || voted_record == NULL) {
        printf("\033[1;31m\t\t\t\t\tError .\033[0m\n");
        return;
    }

    fprintf(votes_file, "%d\n", candidate_number);
    fprintf(voted_record, "NIC: %s\n", nic_check);
    fclose(votes_file);
    fclose(voted_record);
    printf("\n\t\t\t\t\t Succecessfully Voted!\n");
    voter_menu();
}