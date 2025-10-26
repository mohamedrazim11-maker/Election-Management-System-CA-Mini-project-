#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "party.c"
void candidate_signin();
void register_candidate();
void display();
struct Candidate {
    char name[20];
    char party[20];
    char district[20];
    int number;
};
void save_candidate_data(struct Candidate newCandidate);


void candidate_signin() {
    char D_Username[] = "user";
    char D_Password[] = "user123";
    char T_Username[20];
    char T_Password[20];

    printf("\033[1;33m\n\n\t\t\tCANDIDATE LOGIN\033[0m\n\n");
    printf("\t\t\t\t\t\tUser name is: user\n");  
    printf("\033[1;34m\t\t\tEnter username:\033[0m");               //user name and pass is already given
    scanf("%s",T_Username);                                    //to approved candidates
    printf("\t\t\t\t\t\tPassword is: user123\n");               
    printf("\033[1;34m\t\t\tEnter password:\033[0m");               
    scanf("%s", T_Password);

    if (strcmp(T_Username, D_Username) == 0 && strcmp(T_Password, D_Password) == 0) {
        printf("\n\t\t\t\t\tLogin successful!\n");
        register_candidate();
    } else {
        printf("\033[1;31m\n\t\t\t\t\tInvalid username or password.033[0m\n");
        display();
    }
}
void register_candidate() {
    struct Candidate newCandidate;
    printf("\033[1;33m\n\n\t\t\tCANDIDATE REGISTRATION PAGE\033[0m\n\n");
    printf("\033[1;34m\t\t\tCandidate's name:\033[0m");
    while (getchar() != '\n'); 
    fgets(newCandidate.name, sizeof(newCandidate.name), stdin);
    newCandidate.name[strcspn(newCandidate.name, "\n")] = 0;

    district();

    printf("\033[1;34m\n\t\t\tCandidate's district :\033[0m");                       
    fgets(newCandidate.district, sizeof(newCandidate.district), stdin);
    newCandidate.district[strcspn(newCandidate.district, "\n")] = 0;

    party();

    printf("\033[1;34m\t\t\tCandidate's party:\033[0m");
    fgets(newCandidate.party, sizeof(newCandidate.party), stdin);
    newCandidate.party[strcspn(newCandidate.party, "\n")] = 0;

    printf("\033[1;34m\n\t\t\tEnter candidate's number:\033[0m");
    scanf("%d", &newCandidate.number);
    while (getchar() != '\n'); 

    save_candidate_data(newCandidate);
    display();
}
void save_candidate_data(struct Candidate newCandidate) {
    FILE *fptr;
    fptr = fopen("candi_data.txt", "a");

    if (fptr == NULL) {
        printf("\033[1;31m\t\t\t\t\tError !\033[0m\n");
        register_candidate();
    }

    fprintf(fptr, "Name: %s, District: %s, Party: %s, Number: %d\n", newCandidate.name,newCandidate.district, newCandidate.party, newCandidate.number);
    fclose(fptr);
    printf("\033[1;32m\n\t\t\t\t\tSaved Successfull !\033[0m\n");
}