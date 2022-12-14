//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 15.11.2022 12:50:00
// Design Name: plurality
//
// Description: Program for the election that the most voted candidate wins.
// All the details about the election system and problem set rules are described at
// the following link:
// https://cs50.harvard.edu/x/2022/psets/3/plurality/
//
// Output: The output should print the winner of the election.
//////////////////////////////////////////////////////////////////////////////////
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i].name,name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //This for loop inside of the for loop is for shifting bigger values of votes
    //and their names to the left where the biggest value will be placed on the first index
    //of the array, second biggest value or an equal value to the biggest will be placed on the second index and so on..
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            int temporary;
            string stemporary;
            if(candidates[i].votes < candidates[j].votes)
            {
                temporary = candidates[i].votes;
                stemporary = candidates[i].name;
                candidates[i].votes = candidates[j].votes;
                candidates[i].name = candidates[j].name;
                candidates[j].votes = temporary;
                candidates[j].name = stemporary;
            }
        }
    }
    //These if-else statements are for printing the winner of the election
    //If there are more than one winners, all of their names will be printed.
    if(candidates[0].votes > candidates[1].votes)
    {
        printf("%s\n",candidates[0].name);
    }
    else if(candidates[0].votes == candidates[1].votes)
    {
        printf("%s\n",candidates[0].name);
        for(int i = 0; i < candidate_count; i++)
        {
            if(candidates[i].votes == candidates[i+1].votes)
            {
                printf("%s\n",candidates[i + 1].name);
            }
        }
    }
}