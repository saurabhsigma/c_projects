#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

// Function to initialize the game
void initialize(int board[]) {
    // Initialize all positions with 0
    for (int i = 0; i < SIZE; i++) {
        board[i] = 0;
    }

    // Define snakes and ladders
    board[16] = 6; // Snake at position 16, moves down to 6
    board[47] = 26; // Snake at position 47, moves down to 26
    board[49] = 11; // Snake at position 49, moves down to 11
    board[56] = 53; // Snake at position 56, moves down to 53
    board[62] = 19; // Snake at position 62, moves down to 19
    board[64] = 60; // Snake at position 64, moves down to 60
    board[87] = 24; // Snake at position 87, moves down to 24
    board[93] = 73; // Snake at position 93, moves down to 73
    board[95] = 75; // Snake at position 95, moves down to 75
    board[98] = 78; // Snake at position 98, moves down to 78

    board[4] = 25; // Ladder at position 4, moves up to 25
    board[13] = 46; // Ladder at position 13, moves up to 46
    board[33] = 49; // Ladder at position 33, moves up to 49
    board[42] = 63; // Ladder at position 42, moves up to 63
    board[50] = 69; // Ladder at position 50, moves up to 69
    board[62] = 81; // Ladder at position 62, moves up to 81
    board[74] = 92; // Ladder at position 74, moves up to 92
    board[81] = 97; // Ladder at position 81, moves up to 97
}

// Function to roll a dice
int rollDice() {
    return rand() % 6 + 1; // Generates a random number between 1 and 6
}

// Function to play the game
void playGame(int board[]) {
    int playerPosition = 0;
    int dice;

    // Loop until the player reaches position 100
    while (playerPosition < SIZE - 1) {
        printf("Press Enter to roll the dice: ");
        getchar(); // Wait for user to press Enter
        dice = rollDice();
        printf("You rolled: %d\n", dice);
        playerPosition += dice;

        // Check if player landed on a snake or ladder
        if (board[playerPosition] != 0) {
            printf("Encountered a snake or ladder!\n");
            playerPosition = board[playerPosition];
        }

        // Ensure player doesn't go beyond position 100
        if (playerPosition >= SIZE - 1) {
            printf("Congratulations! You've reached position 100. You win!\n");
            break;
        }
        printf("Your current position is: %d\n", playerPosition);
    }
}

int main() {
    int board[SIZE];

    // Seed the random number generator
    srand(time(NULL));

    // Initialize the game board
    initialize(board);

    // Play the game
    playGame(board);

    return 0;
}

