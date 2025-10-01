#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
//all included libraries

//prototype funcitons
bool is_valid_key(string key);
string substitute (string key, string plaintext);


int main(int argc, string argv[]) //command line argument
{
    if (argc != 2) //if the argument doesnt contain two command line arguments return to original
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }


    string key = argv[1]; //the key is the first string inputed in the command line argument
    if (!is_valid_key(key)) // if it isn't a valid key return
    {
        printf("Key must contain 26 alphabetical characters.\n");
        return 1;
    }

    string plaintext = get_string("Plain text: "); //get plaintext input from user

    string cipher_text = substitute(key, plaintext); //setting the variable cipher_text to the subtitute function of the combination of the user's key and plaintext
    printf("ciphertext: %s\n", cipher_text); //print output to user for the ciphertext



}


bool is_valid_key(string key) //function for checking the validity of the user's inputed key
{
    if (strlen(key) != 26) //if the length doesn't equal to 26 return
    {
        return false;
    }

    bool used[26] = {false}; //making sure to find the true or false for 26 characters for the given key

    for (int i = 0, n = strlen(key); i < n; i++) //looping each character throughout the length of the key
    {
        if (!isalpha(key[i])) //if it isn't an alphabet return
        {
            return false;
        }

        int index = toupper(key[i]) - 'A'; //setting the key character to an index
        if(used[index]) //if the index was used twice return
        {
            return false;
        }
        used[index] = true; //if it was used once continue

    }

    return true;

}


string substitute(string key, string plaintext) //function for substituting both the given key and plaintext from user to create ciphertext
{
    int len = strlen(plaintext); //creating a variable to have the length of the plaintext
    string cipher_text = plaintext; //creating the variable cipher text which includes the plaintext


    for (int i = 0, n = len; i < n; i++) // looping throughout each character of the plaintext
    {
        if (isupper(plaintext[i])) //if the character fo the plain text is an upper case letter
        {
            int index = plaintext[i] -'A'; // creating the index for that character and saving it to the index variable
            cipher_text[i] = toupper(key[index]); //taking the letter from the key depending on the index number from the plaintext
        }
        else if (islower(plaintext[i])) // same thing but for lower case letter in the plain text only
        {
            int index = plaintext[i] - 'a';
            cipher_text[i] = tolower(key[index]);
        }
        else
        {
            cipher_text[i] = plaintext[i]; //if it's neither than just include whatever is in that position
        }
    }
    return cipher_text; //return the completed cipher text to the subsitution result
}
