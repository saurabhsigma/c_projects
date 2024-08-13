#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TRIES 6

// Function prototypes
void initialize(char* secretWord, char* guessedWord);
void updateGuessedWord(char guess, char* secretWord, char* guessedWord, int wordLength);
int checkWin(int blanksRemaining);
void drawHangman(int remainingTries);
void drawWord(char* guessedWord);

int main() {
    char secretWord[20];
    char guessedWord[20];
    char guess;
    int tries = 0;
    int wordLength;

    printf("Enter the secret word: ");
    scanf("%s", secretWord);
    wordLength = strlen(secretWord);

    initialize(secretWord, guessedWord);

    while (tries < MAX_TRIES && !checkWin(guessedWord)) {
 
        printf("\n\n");
        drawHangman(MAX_TRIES - tries);
        drawWord(guessedWord);
        printf("\nEnter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);

        if (!isalpha(guess)) {
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }

        if (strchr(secretWord, guess) != NULL) {
            printf("\nGood guess!");
            updateGuessedWord(guess, secretWord, guessedWord, wordLength);
            if (checkWin(wordLength)) {
                printf("\nCongratulations! You guessed the word: %s\n", secretWord);
                return 0;
            }
        } else {
            printf("\nIncorrect guess.");
            tries++;
        }
    }

    printf("\nYou ran out of tries! The word was: %s\n", secretWord);

    return 0;
}

// Initialize guessed word with dashes
void initialize(char* secretWord, char* guessedWord) {
    int i;
    for (i = 0; i < strlen(secretWord); i++) {
        guessedWord[i] = '_';
    }
    guessedWord[i] = '\0';
}

// Update guessed word with correctly guessed letters
void updateGuessedWord(char guess, char* secretWord, char* guessedWord, int wordLength) {
    int i;
    for (i = 0; i < wordLength; i++) {
        if (secretWord[i] == guess) {
            guessedWord[i] = guess;
        }
    }
}

// Check if player wins
int checkWin(int blanksRemaining) {
    return blanksRemaining == 0;
}

// Draw hangman based on remaining tries
void drawHangman(int remainingTries) {
    switch (remainingTries) {
        case 6:
            printf(" ________\n");
            printf(" |      |\n");
            printf(" |\n");
            printf(" |\n");
            printf(" |\n");
            printf("_|__________\n");
            break;
        case 5:
            printf(" ________\n");
            printf(" |      |\n");
            printf(" |      O\n");
            printf(" |\n");
            printf(" |\n");
            printf("_|__________\n");
            break;
        case 4:
            printf(" ________\n");
            printf(" |      |\n");
            printf(" |      O\n");
            printf(" |      |\n");
            printf(" |\n");
            printf("_|__________\n");
            break;
        case 3:
            printf(" ________\n");
            printf(" |      |\n");
            printf(" |      O\n");
            printf(" |     /|\n");
            printf(" |\n");
            printf("_|__________\n");
            break;
        case 2:
            printf(" ________\n");
            printf(" |      |\n");
            printf(" |      O\n");
            printf(" |     /|\\\n");
            printf(" |\n");
            printf("_|__________\n");
            break;
        case 1:
            printf(" ________\n");
            printf(" |      |\n");
            printf(" |      O\n");
            printf(" |     /|\\\n");
            printf(" |     /\n");
            printf("_|__________\n");
            break;
        case 0:
            printf(" ________\n");
            printf(" |      |\n");
            printf(" |      O\n");
            printf(" |     /|\\\n");
            printf(" |     / \\\n");
            printf("_|__________\n");
            break;
    }
}

// Draw current state of guessed word
void drawWord(char* guessedWord) {
    printf("Word: %s\n", guessedWord);
}

