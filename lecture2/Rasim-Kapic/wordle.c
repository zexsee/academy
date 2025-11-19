#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define WORD_LEN 5
#define MAX_TRIES 6

int main() {
    const char *words[] = {
        "APPLE", "GRAPE", "BERRY", "MANGO", "LEMON", "PEACH", "CHILI",
        "OLIVE", "ONION", "BASIL", "COCOA", "HONEY", "SUGAR", "PIZZA",
        "BREAD", "PASTA", "CREAM", "TOAST", "FRUIT", "SALAD", "HAPPY"
    };
    int word_count = sizeof(words) / sizeof(words[0]);

    srand(time(NULL));
    const char *secret = words[rand() % word_count];

    char guess[100];
    char feedback[WORD_LEN + 1]; 
    int letter_counts[26];       

    printf("Welcome to Wordle!\n");
    printf("Try to guess the 5-letter secret word.\n");

    for (int attempt = 1; attempt <= MAX_TRIES; attempt++) {
        while (1) {
            printf("\nAttempt %d/%d: Enter your guess: ", attempt, MAX_TRIES);
            fgets(guess, sizeof(guess), stdin);

            guess[strcspn(guess, "\n")] = '\0';

            if (strlen(guess) != WORD_LEN) {
                printf("Your guess must be 5 letters.\n");
                continue;
            }

            int valid = 1;
            for (int i = 0; i < WORD_LEN; i++) {
                if (!isalpha(guess[i])) {
                    valid = 0;
                    break;
                }
            }
            if (!valid) {
                printf("Your guess must contain only letters.\n");
                continue;
            }

            break;
        }

        for (int i = 0; i < WORD_LEN; i++) {
            guess[i] = toupper(guess[i]);
        }

        for (int i = 0; i < 26; i++) {
            letter_counts[i] = 0;
        }

        for (int i = 0; i < WORD_LEN; i++) {
            if (guess[i] == secret[i]) {
                feedback[i] = 'G';
            } else {
                feedback[i] = '?';
                letter_counts[secret[i] - 'A']++;
            }
        }

        for (int i = 0; i < WORD_LEN; i++) {
            if (feedback[i] == 'G') continue;

            int index = guess[i] - 'A';
            if (letter_counts[index] > 0) {
                feedback[i] = 'Y'; 
                letter_counts[index]--;
            } else {
                feedback[i] = '.';
            }
        }

        feedback[WORD_LEN] = '\0'; 

        printf("Your guess: %s\n", guess);
        printf("Feedback:   %s\n", feedback);

        if (strcmp(feedback, "GGGGG") == 0) {
            printf("You guessed the word in %d attempt(s)!\n", attempt);
            return 0;
        }
    }
    printf("\nOut of attempts. The secret word was: %s\n", secret);
    return 0;
}
