// It's a encryption program.
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, string argv[])
{
    // Step 1: exactly one command-line argument required
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Step 2: ensure the key contains only digits (non-negative integer)
    for (size_t i = 0; i < strlen(argv[1]); i++)
    {
        // cast to unsigned char before ctype to avoid UB on non-ASCII
        if (!isdigit((unsigned char)argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Step 3: convert to integer and normalize to [0..25]
    int key = atoi(argv[1]);       // e.g., "27" -> 27
    key = key % 26;                // e.g., 27 % 26 -> 1

    // ----------------------------
    // Step 4: read plaintext line
    // ----------------------------
    string plaintext = get_string("plaintext: ");

    // ----------------------------
    // Step 5 & 6: rotate and print
    // ----------------------------
    printf("ciphertext: ");

    // Loop through every character in the plaintext
    for (size_t i = 0, n = strlen(plaintext); i < n; i++)
    {
        unsigned char c = (unsigned char) plaintext[i];

        if (isupper(c))
        {
            // Map 'A'..'Z' to 0..25, add key, wrap with %26, map back to 'A'..'Z'
            char enc = (char) (((c - 'A') + key) % 26 + 'A');
            printf("%c", enc);
        }
        else if (islower(c))
        {
            // Same idea for lowercase, preserve case
            char enc = (char) (((c - 'a') + key) % 26 + 'a');
            printf("%c", enc);
        }
        else
        {
            // Non-alphabetic: leave as-is (spaces, punctuation, digits, etc.)
            printf("%c", c);
        }
    }

    printf("\n");
    return 0;
}
