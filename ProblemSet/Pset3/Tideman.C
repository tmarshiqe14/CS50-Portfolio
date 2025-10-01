#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX]; //creates the amount of slots for the 2D array based on the max

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

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
void lock_pairs(void);
bool cycle_check(int start, int current);
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
                return 3;]
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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
         if (strcmp(candidates[i], name) == 0)
         {
            ranks[rank] = i;
            return true;
         }

    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) // compares the first candidate which in this example would be Tamer
    {
        for (int j = 0; j < candidate_count; j++) // Compares each candidate afterwards until the end, so first loops through Dyaa, then Khaled, then Baha, then Samya, and then it goes back to i and starts at Dyaa instead of starting at Tamer
        {
            if (i != j) //Makes sure that we aren't comparing the same name to each other
            {
                if(preferences[i][j] > preferences[j][i]) //Ex: if [Tamer][Dyaa] > [Dyaa][Tamer]
                {
                    pairs[pair_count].winner = i; //The winner in pairs[0].winner = Tamer
                    pairs[pair_count].loser = j; // In pairs[0].loser = Dyaa
                    pair_count++; // pair_count = 1; and so on
                }
        }
    }
}
    return;

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for ( int i = 0; i < pair_count - 1; i++) // This loops is to save time when sorting so once something is sorted a specific candidate is stored in the correct position, the loop takes away 1 so we only sort the candidates that arent in the right position
    {
        for (int j = 0; j < pair_count - 1; j++) // this loop is to make sure we sort each 2 pairs and we dont sort the last candidate to nothing next to it so we subtract 1 at the end because theres no one to compare the last candidate to
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner]; //Subtracts 4 wins of [Tamer][Dyaa] - 2 wins of [Dyaa][Tamer] which means strength1 = 2
            int strength2 = preferences[pairs[j+1].winner][pairs[j + 1].loser] - preferences[pairs[j+1].loser][pairs[j+1].winner]; //subtracts the next pairs which is 5 wins of [Tamer][Khaled] - 2 wins of [Khaled][Tamer] so strength2 = 3

            if (strength1 < strength2) //since strength1 is less than strength2 we swap to sort the most amount of wins first to lowest. This is for bubble sort
            {
                pair temp = pairs[j]; // Swapping formula for C
                pairs[j] = pairs[j+1];
                pairs[j+1] = temp;

            }


        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

        for (int i = 0; i < pair_count; i++) //loop through the amount of pairs there are one by one
        {
            if (!cycle_check(pairs[i].winner, pairs[i].loser)) //check if there's a cycle using the cycle_check function by using the specific index's pairs winner and loser
            {
                locked[pairs[i].winner][pairs[i].loser] = true; //if there is no cycle, then lock the winner and loser in the 2D array of locked[];
            }
        }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) //loops every candidate one by one
    {
        bool incoming = false; //sets a flag to false for now

        for (int j = 0; j < candidate_count; j++) //loops through every other candidate to compare the first candidate
        {
            if (locked[j][i]) //if the other candidate beats the current candidate then activate the flag
        {
            incoming = true;
            break;
        }

        }

        if (!incoming) //if there has been no flag meaning no one was able to beat the original candidate
        {
            printf("%s\n", candidates[i]); // print the winner, there is only one winner
            return; //leave the function once and for all
        }


    }

 }


bool cycle_check(int start, int current) //
{

    if (current == start)
    {
        return true;
    }


    for (int i = 0; i < candidate_count; i++)
    {
        if(locked[current][i])
        {
            if(cycle_check(start, i))
            {
                return true;
            }
        }
    }
    return false;
}
