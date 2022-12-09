//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 08.12.2022 23:50:00
// Design Name: tideman
//
// Description: Program for an election system called tideman. All the details
// about the election system and problem set rules are described at
// the following link:
// https://cs50.harvard.edu/x/2022/psets/3/tideman/
//
// Output: The output should print the winner of the election.
//////////////////////////////////////////////////////////////////////////////////
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool has_cycle(int winner, int loser);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Function updates the rank array with the voter's selections in order.
// If voter types a candidate name that is not in the candidates array,
// function returns false, otherwise function assigns the index of the
// candidate to the ranks array and returns true.
bool vote(int rank, string name, int ranks[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i],name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Function updates the preferences array with the preferences of the voters.
// This means that in the preferences array, how many times candidate "i" is preferred
// over candidate "j" is assigned.
void record_preferences(int ranks[])
{
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
}

// Function fills the pairs array where this array indicates all the pairs
// where one candidate is preffered over an other candidate.
// Function does this by comparing the votes at the preferences table.
// Function also updates the pair_count array that calculates the amount of
// the pairs.
void add_pairs(void)
{
    int index = 0;
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            if(preferences[i][j] > preferences[j][i])
            {
                (pairs[index]).winner = i;
                (pairs[index]).loser  = j;
                pair_count++;
                index++;
            }
            else if(preferences[i][j] < preferences[j][i])
            {
                (pairs[index]).winner = j;
                (pairs[index]).loser  = i;
                pair_count++;
                index++;
            }
        }
    }
}

// Function sorts the pairs array in decreasing order of strength of victory,
// where strength of victory is defined to be the number of voters who prefer
// the preferred candidate. If multiple pairs have the same strength of victory,
// the order doesn't matter.
void sort_pairs(void)
{
    pair temporary;
    for(int i = 0; i < pair_count; i++)
    {
        for(int j = i + 1; j < pair_count; j++)
        {
            if((preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]) < (preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner]))
            {
                temporary.winner    = pairs[i].winner;
                temporary.loser     = pairs[i].loser;
                pairs[i].winner     = pairs[j].winner;
                pairs[i].loser      = pairs[j].loser;
                pairs[j].winner     = temporary.winner;
                pairs[j].loser      = temporary.loser;
            }
        }
    }
}

// Function is a subfunction used int the lock_pairs function.
// It's purpose is to detect whether there is a cycle or not.
// If locked array has a potential cycle situation, it returns true
// Otherwise, it returns false.
// Cycle conditions are explained in detail in the problem set's webpage
bool has_cycle(int winner, int loser)
{
    if(locked[loser][winner] == true)
    {
        return true;
    }
    for(int i = 0; i < pair_count; i++)
    {
        if((locked[loser][i] == true) && (has_cycle(winner, i)))
        {
            return true;
        }
    }
    return false;
}

// Function fills the locked array with true by using
// the pairs array's winner and loser values as indexes.
// Specific values that create cycles are ignored and
// the related parts remain as false.
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser  = pairs[i].loser;
        if(!(has_cycle(winner, loser)))
        {
            locked[winner][loser] = true;
        }
    }
}

// Function prints the winner of the election by
// detecting a column with all of it to has only false values.
void print_winner(void)
{
    int column;
    for(column = 0; column < candidate_count; column++)
    {
        bool no_true = true;
        for(int row = 0; row < candidate_count; row++)
        {
            if(locked[row][column] == true)
            {
                no_true = false;
            }
        }
        if(no_true == true)
        {
            break;
        }
    }
    printf("%s\n", candidates[column]);
}