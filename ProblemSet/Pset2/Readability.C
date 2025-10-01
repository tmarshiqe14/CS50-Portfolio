#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
//All of the libraries needed

//Prototype for functions in order to count letters, words, and sentences
int Count_Letters(string word);
int Count_words(string word);
int Count_Sentences(string word);

int main(void)
{
    //Getting text from the user
    string word = get_string("Text: ");
    int letter = Count_Letters(word);
    int words = Count_words(word);
    int Sentence = Count_Sentences(word);           // implementing the user's input to all of the functions


    float L = ((float) letter/words) * 100; //calculating for variabe L for the formula
    float S = ((float) Sentence/words) * 100; // calculating for variable S for the formula

    float index = .0588* L - 0.296 * S - 15.8; //formula for calculating grade level

    int grade = round(index); //rounding the grade level and putting it into a variable

    if (grade < 1) //finding out what grade level to output to the user based on the grade level variable formula
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
    return 0;

}


//Counting letters in the text
int Count_Letters(string word)
{
    int sum = 0;
    for(int i = 0, n = strlen(word); i < n; i++) //reading the text letter by letter depending on the length
    {
        if(isalpha(word[i])) //making sure to only count letters
    {
        sum++; //adds each letter to the sum
    }
    }
    return sum; // returning the variable sum which has total increments of the amount of letters in the given text
}


//Counting the number of words in the given text
int Count_words(string word)
{
    int NoWords = 1; //setting the variable of amount of words to 1
    for(int i = 0, n = strlen(word); i < n; i++) //Looping based on the size of the text
    {
        if (word[i] == ' ') //looking for spaces in the text to end a word
        {
            NoWords++; //incrementing the amount of words in the text
        }
    }
    return NoWords; // returning the variable
}


//Counting the amount of sentences
int Count_Sentences(string word)
{
    int NoSentences = 0; //No amount of sentences until user inputs either period, question mark, or exclamation mark
    for(int i = 0, n = strlen(word); i < n; i++) //Looping based on the length of the given text
    {
        if(word[i] == '.' || word[i] == '?' || word[i] == '!')
        {
            NoSentences++; // incrementing the amount of sentences
        }

    }
     return NoSentences; //returning the variable
}
