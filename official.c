#include <stdio.h>
#include <string.h>
#define MAX_CANDIDATES 50
#define MAX_VOTERS 100
void display();
void official_login();
void count_votes();
void official_menu();
void candidates();
void voter();

void official_menu(){
        int choice;
        printf("\033[1;33m\n\t\t\tOfficials Menu\033[0m\n\n");
        printf("\033[1;34m\t\t\t1 View Candidate List\n");
        printf("\t\t\t2 View voters List\n");
        printf("\t\t\t3 Realese Election Results\n");
        printf("\t\t\t4 Exit\033[0m\n");
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                 candidates();
                break;

            case 2:
                 voter();
                break;

            case 3:
                count_votes();
                break;

            case 4:
                printf("\n\t\t\t\t\tExiting now...\n");
                display();
                

            default:
                printf("\033[1;31m\t\t\t\t\tInvalid choice, please try again.\033[0m\n");
        }

}

void official_login(){
    char D_Username[] = "official";
    char D_Password[] = "offi123";
    char T_Username[20];
    char T_Password[20];

    printf("\033[1;33m\n\n\t\t\tOFFICIAL LOGIN\n\n\033[0m");
    printf("\t\t\t\t\t\tUser name is: official\n"); 
    printf("\t\t\tEnter username: ");                                                     //user name and password is already given
    scanf("%s",T_Username);                                               //to approved officials
    printf("\t\t\t\t\t\tPassword is: offi123\n");                                     
    printf("\t\t\tEnter password: ");              
    scanf("%s", T_Password);                      
    if (strcmp(T_Username, D_Username) == 0 && strcmp(T_Password, D_Password) == 0) {
        printf("\n\t\t\t\t\tLogin successful!\n");
        official_menu();
    } else {
        printf("\033[1;31m\n\t\t\t\t\tInvalid username or password.\033[0m\n");
        display();
    }

}


void count_votes() {
    FILE *votes_file = fopen("votes.txt", "r");
    if (votes_file == NULL) {
        printf("\033[1;31m\n\t\t\t\t\tNo one has voted yet.\033[0m\n");
        official_menu();
        
    }

    int vote_count[100] = {0}; 
    int candidate_number;
    int max_votes = 0;
    int winner_number = -1;

    while (fscanf(votes_file, "%d", &candidate_number) == 1) {
        if (candidate_number >= 1 && candidate_number < 100) {
            vote_count[candidate_number]++;
        }
    }
    fclose(votes_file);

    printf("\033[1;31m\n\n\t\t\t\t\t\t\tELECTION RESULTS\033[0m\n");
    printf("\t\t\t\t\t\t--------------------------------\n");
   
    // Display results and find the winner
    FILE *results_file = fopen("results.txt", "w");
    if (results_file == NULL) {
        printf("\033[1;31m\t\t\t\t\tError\033[0m\n");
    }

    printf("\n\t\t\t\t\t\t\tCandidate Votes\n");
    fprintf(results_file, "Candidate Votes:\n");
    for (int i = 1; i < 100; i++) {
        if (vote_count[i] > 0) {
            printf("\t\t\t\t\t\t       Candidate %d: %d votes\n", i, vote_count[i]);
            fprintf(results_file, "Candidate %d: %d votes\n", i, vote_count[i]);
            if (vote_count[i] > max_votes) {
                max_votes = vote_count[i];
                winner_number = i;
            }
        }
    }
   
    if (winner_number != -1) {
        printf("\n\t\t\t\t\t\tWinner: Candidate %d with %d votes!\n", winner_number, max_votes);
        fprintf(results_file, "\nWinner: Candidate %d with %d votes!\n", winner_number, max_votes);
    } else {
        printf("\033[1;31m\n\t\t\t\t\tNo votes were recorded.\033[0m\n");
        fprintf(results_file, "\nNo votes were recorded.\n");
    }

    if (results_file != NULL) {
        fclose(results_file);
    }
       display();
}
    void candidates(){

     FILE *candi;
     candi=fopen("candi_data.txt","r");

     if (candi==NULL)
     {
        printf("\t\t\t\t\tNO Candidates Registered Yet");
        official_menu();
     }
     else{
        
        char line[100];
        printf("\033[1;33m\n\n\t\t\t\t\t\t\tCANDIDATE LIST\033[1;0m\n\n");
        printf("\t\t\t\t\t\t\t----------------\n");
        while (fgets(line, sizeof(line), candi)) {
            printf("\t\t\t\t\t%s", line);
        }
        fclose(candi);
     }
     official_menu();
     
     
    }
    
    void voter(){
        FILE *voter;
        voter=fopen("voters.txt","r");

        if (voter==NULL)
        {
            printf("\033[1;31m\t\t\t\t\t\nNo Voters Registered Yet\033[0m");
            official_menu();
        }

        else{
            char line[100];
            printf("\033[1;33m\n\n\t\t\t\t\t\t\t  VOTER LIST\033[0m\n\n");
            printf("\t\t\t\t\t\t\t----------------\n");
            while (fgets(line, sizeof(line), voter)) {
                printf("\t\t\t\t\t\t%s", line);
            }
        
            fclose(voter);    }
            official_menu();
 }