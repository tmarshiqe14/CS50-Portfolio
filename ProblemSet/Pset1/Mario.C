#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    // creates integer value called height
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);
    // asks user for input of height until it's greater than or equal to 1

    for (int i = 1; i <= height; i++)
    // sets the amount of rows
    {
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        // sets amount of spaces depending on the number of rows
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        // prints the amount of hashtag blocks depending on number of that row
        printf("  ");
        // creates a whole space to start another triangle

        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        // prints the mirrored version of that same row
        printf("\n");
        // goes to the next row or line
    }
}
