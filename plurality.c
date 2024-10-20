//#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char* name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char* name);
void print_winner(void);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = strdup(argv[i + 1]);
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    getchar();

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        
        char *name = NULL;
        size_t buffer_size = 0;

        printf("Vote: ");
        getline(&name, &buffer_size, stdin);
        name[strcspn(name, "\n")] = '\0';

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }

        free(name);
    }

    // Display winner of election
    print_winner();

    for(int i = 0; i < candidate_count; i++) {
        free(candidates[i].name);
    }
    return 0;
}

// Update vote totals given a new vote
bool vote(char* name)
{
    // Loop through candidates to check if the name matches
    //iterate over each candidate
    for(int i = 0; i < candidate_count; i++) {
        
        //check if candidates name matches
        if(strcmp(candidates[i].name, name) == 0) {

        //if yes, increment candidates votes and return true
        candidates[i].votes++;
        return true;
        }
    }
    
    //if not match, false
    return false;

}


// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest_total = 0;

    // Find the maximum number of votes
    for(int i = 0; i < candidate_count; i++) {
        if(candidates[i].votes > highest_total) {
            highest_total = candidates[i].votes;
        }
    }

    // Print the candidate (or candidates) with maximum votes
    for(int j = 0; j < candidate_count; j++) {
        if(candidates[j].votes == highest_total) {
            printf("%s\n", candidates[j].name);
        }
    }
    
}