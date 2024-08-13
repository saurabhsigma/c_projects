#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int main() {
    printf("Hello World\n");

    printf("Welcome to the rock paper scissors game: \n");
    printf("1. Rock\n");
    printf("2. Paper\n");
    printf("3. Scissors\n");

    int  playing = 1; 
    while (playing) {
        int choice;
        printf("Do you want to play the game? (1 for yes, 0 for no): ");
        scanf("%d", &playing);

        if (playing) {
            printf("Enter your choice (1 for Rock, 2 for Paper, 3 for Scissors): ");
            scanf("%d", &choice);

            if (choice < 1 || choice > 3) {
                printf("Invalid choice. Please choose again.\n");
                continue;
            }

            int lower_bound = 1;
            int upper_bound = 3;

            srand(time(NULL));
            int random_number = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;

            printf("You chose: ");
            switch (choice) {
                case 1:
                    printf("Rock\n");
                    break;
                case 2:
                    printf("Paper\n");
                    break;
                case 3:
                    printf("Scissors\n");
                    break;
            }

            printf("Computer chose: ");
            switch (random_number) {
                case 1:
                    printf("Rock\n");
                    break;
                case 2:
                    printf("Paper\n");
                    break;
                case 3:
                    printf("Scissors\n");
                    break;
            }

            if (choice == random_number) {
                printf("It's a tie!\n");
            } else if ((choice == 1 && random_number == 3) ||
                       (choice == 2 && random_number == 1) ||
                       (choice == 3 && random_number == 2)) {
                printf("You win!\n");
              
            } else {
                printf("Computer wins!\n");
            }
        }
          }
    
    printf("Thanks for playing!\n");

    return 0;
}
