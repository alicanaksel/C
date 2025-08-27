#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Loop over all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If the name matches a candidate
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Record the candidate's index in preferences
            preferences[voter][rank] = i;
            return true;
        }
    }
    // If no candidate name matched
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // For each voter...
    for (int i = 0; i < voter_count; i++)
    {
        // ...scan their ranked preferences from highest to lowest
        for (int j = 0; j < candidate_count; j++)
        {
            int cand_index = preferences[i][j];   // j-th choice's candidate index

            // If this candidate is still in the race, count this ballot for them
            if (!candidates[cand_index].eliminated)
            {
                candidates[cand_index].votes++;
                break;  // very important: stop at the first non-eliminated choice
            }
            // else: this preference is eliminated; try the next rank (j+1)
        }
    }
}


// Print the winner of the election, if there is one
// If any non-eliminated candidate has > half of all votes, print their name and return true.
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false; // no majority yet
}

// Return the minimum vote total among candidates still in the election
int find_min(void)
{
    int min = voter_count; // upper bound: no one can have more than voter_count
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all remaining candidates
bool is_tie(int min)
{
    // All non-eliminated candidates must have the same (== min) number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate candidate(s) who have the minimum number of votes
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}

