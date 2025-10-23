#include <stdio.h>
#include "candidate.c"
#include "voter.c"
#include "official.c"
void welcome();
void display();
int main() {
    welcome();
    display();
}
void welcome(){
      printf("\033[1;31m\n\t\t\t\tWelcome to the Election Management System\033[0m\n\n");
      printf("\t\t\t\t\t------------------------\n");
}

void display(){
     int optm;
     printf("\033[1;33m\n\n\t\t\tMAIN MENU\033[0m\n\n");
    
     printf("\033[1;34m\t\t\t1. Voter\n"
            "\t\t\t2. Candidate\n"
            "\t\t\t3. Official\n"
            "\t\t\t4. Exit\033[0m\n\n"
            "\t\t\tSelect an option: ");
     scanf("%d", &optm);

     switch (optm) {
        case 1:
            voter_menu();
            break;
        case 2:
            candidate_signin();
            break;
        case 3:
            official_login();
            break;
        case 4:
            printf("\033[1;31m\t\t\t\t\tExited\033[0m\n");
            exit(0);
        default:
            printf("\033[1;31m\n\t\t\t\t\tInvalid option. Please try again\033[0m\n");
            display();
            break;
    }
}


