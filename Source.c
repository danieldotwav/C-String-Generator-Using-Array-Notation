#define _CRT_SECURE_NO_WARNINGS /* disable security warnings in Microsoft Visual Studio*/
#include <stdio.h>
#include <stdlib.h>

#define S1LENGTH 40
#define S2LENGTHMIN 2
#define S2LENGTHMAX 20

char* generateS1(void);
void generateS2(char s2[S2LENGTHMAX + 1]);

int isUpperCaseLetter(int iochar);

int main(void) {
    char* s1 = generateS1();

    char s2[S2LENGTHMAX];
    generateS2(s2);

    puts(s2);

    return 0;
}

char* generateS1(void) {
    char s1[S1LENGTH + 1];
    int rand_num;
    char rand_char;

    for (int i = 0; i < S1LENGTH; ++i) {
        /* Generate random number between 1 and 26 */
        rand_num = rand() % 26;

        /* Shift the range to 65-90 and cast to char */
        rand_char = (char)(rand_num + 65);

        printf("Random uppercase letter: %c\n", rand_char);

        /* Store random letter in array of chars */
        s1[i] = rand_char;
    }

    /* Null-terminating string */
    s1[S1LENGTH] = '\0';

    return s1;
}

void generateS2(char s2[S2LENGTHMAX + 1]) {
    /* Get the user string */
    printf("Enter a string of uppercase letters 'A' - 'Z'\n");
    printf("Must contain between %d and %d characters: ", S2LENGTHMIN, S2LENGTHMAX);

    int numCharacters = 0; /* Keep track of num characters */
    int invalidCharacterDetected = 0; /* Flag to keep track of valid characters */
    int hasExceededCharacterLimit = 0; /* Flag to keep track of string length */
    char currentCharacter; /* Keep track of current character being processed */

    /* Process input while:
    /* 1. There are still characters in the input buffer,
    /* 2. We haven't encountered an invalid character, AND
    /* 3. The number of characters does not exceed the S2LENGTHMAX limit */
    while ((currentCharacter = getchar()) != EOF && currentCharacter != '\n') {
        ++numCharacters; /* Increment character count */

        /* If we've already encountered an invalid character, simply increment the character counter */
        if (!invalidCharacterDetected) {
            /* Now we check to see if we've exceeded the character limit */
            hasExceededCharacterLimit = (numCharacters > S2LENGTHMAX);

            if (!hasExceededCharacterLimit) {
                /* Finally, we check for invalid character */
                if (isUpperCaseLetter(currentCharacter)) {
                    s2[numCharacters - 1] = currentCharacter;
                }
                else {
                    invalidCharacterDetected = 1;
                }
            }
        }
    }

    /* Check if user input meets min string length requirement */
    int isLessThanRequiredLength = (numCharacters < S2LENGTHMIN);

    /* Print appropriate error messages */
    if (invalidCharacterDetected) {
        printf("Error: Invalid characters detected. Input must contain ONLY uppercase alphabetical characters\n");
    }

    if (hasExceededCharacterLimit || isLessThanRequiredLength) {
        printf("Error: Invalid string length. Input must be between %d and %d characters long\n", S2LENGTHMIN, S2LENGTHMAX);
    }

    /* If any of the error flags were raised, set the first index of the array to the null terminating character */
    if (invalidCharacterDetected || hasExceededCharacterLimit || isLessThanRequiredLength) {
        s2[0] = '\0';
    }
    else {
        s2[numCharacters] = '\0';
    }
}

int isUpperCaseLetter(int iochar) {
    return (iochar >= 'A' && iochar <= 'Z');
}