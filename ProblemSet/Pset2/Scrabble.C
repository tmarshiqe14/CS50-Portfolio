#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int Compute_Word(string s);


int main(void)
{
    //Get each player's word
    string Player1 = get_string("Palyer1: ");
    string Player2 = get_string("Player2: ");

    // Compute the scores
    int Computed1 = Compute_Word(Player1);
    int Computed2 = Compute_Word(Player2);


    //Print who the winner is
    if (Computed1 > Computed2)
    {
        printf("Player 1 Wins!\n");
    }
    else if (Computed1 < Computed2)
    {
        printf("Player 2 Wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

}

//Compute the player's word
int Compute_Word(string s)
{
    //Keep Track of score
    int score = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Compute score for each character
        if (isupper(s[i]))
        {
            score += POINTS[s[i] - 'A'];
        }
        else if (islower(s[i]))
        {
            score += POINTS[s[i] - 'a'];
        }
        //Add it to the sum


    }
    return score;

}
