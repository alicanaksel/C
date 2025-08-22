// Scrabble game in C
#include <stdio.h>
#include <string.h>

// Function prototype
int get_score(char word[], int points[]);

int main(void) {
    // Points for each letter A–Z
    int points[26] = {
        1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3,
        1, 1, 3,10, 1, 1, 1, 1, 4, 4, 8, 4,10
    };

    // Arrays to store player inputs (up to 49 characters + '\0')
    char player1[50];
    char player2[50];

    // Ask for Player 1 input
    printf("Player 1: ");
    scanf("%49s", player1);  // Read string safely (max 49 chars)

    // Ask for Player 2 input
    printf("Player 2: ");
    scanf("%49s", player2);

    // Calculate scores for both players
    int score1 = get_score(player1, points);
    int score2 = get_score(player2, points);

    // Compare scores and print result
    if (score1 > score2){
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2){
        printf("Player 2 wins!\n");
    }
    else{
        printf("Tie!\n");
    }
}

// Function to calculate the score of a given word
int get_score(char word[], int points[])
{
    int score = 0;
    // Loop through each character of the word
    for (int i = 0; i < strlen(word); i++) {
        char ch = word[i];

        // If the character is lowercase, convert to uppercase
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - 32;   // ASCII trick: 'a' - 'A' = 32
        }

        // If it is a letter, add corresponding points
        if (ch >= 'A' && ch <= 'Z') {
            score += points[ch - 'A'];
        }
    }
    return score;
}
