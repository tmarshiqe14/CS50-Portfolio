#include <cs50.h>
#include <stdio.h>

long get_length(long number);
bool checksum(long number);
void checkCard(long number);
int getfirstTwoDigits(long number);
int getfirstDigit(long number);
int main(void)
{
    long number = get_long("Number: "); // getting the user's credit card number that was inputed
    bool Chsum = checksum(number);
    long length = get_length(number);

    if (Chsum == false) // Check the validity or checksum of the card using the Luhn method
    {
        printf("INVALID\n");
    }
    else
    {
        checkCard(number); // Checking what kind of card it is and if it's available
    }
}

void checkCard(long number) // function for checking the card
{
    long length1 = get_length(number);
    int Digits2 = getfirstTwoDigits(number);
    int Digit1 = getfirstDigit(number);

    if (length1 == 15 && (Digits2 == 34 || Digits2 == 37)) // requirements for American express card
    {
        printf("AMEX\n");
    }
    else if (length1 == 16 && (Digits2 == 51 || Digits2 == 52 || Digits2 == 53 || Digits2 == 54 ||
                               Digits2 == 55)) // requirements for MasterCard card
    {
        printf("MASTERCARD\n");
    }
    else if ((length1 == 13 || length1 == 16) && Digit1 == 4) // requirements for Visa card
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n"); // if it's none of the cards then it's an invalid number
    }
}

bool checksum(long number) // function for checking the validity of the card through luhn method
{
    bool luhn = false; // skipping the last number to go on to the second to last number
    int sum = 0;

    while (number > 0)
    {
        int digit = number % 10; // getting to the last digit of the update number
        if (luhn)
        {
            digit *= 2;    // multiplying every other digit by 2 starting from secont do last digit
            if (digit > 9) // if the number is 2 digits
            {
                digit = (digit % 10) + (digit / 10); // adding the first and second digit together
            }
        }

        sum += digit; // adding all the singular digits to the total sum
        number /= 10; // updating the number to get
        luhn = !luhn; // on and off switch
    }
    return (sum % 10 == 0);
}

long get_length(long number) // getting the length of the number
{
    int length = 0;
    while (number > 0)
    {
        number /= 10; // dividing by 10 until number gets to 0 depending on the length of the number
        length++;     // adding the amount of number to length variable
    }
    return length;
}

int getfirstTwoDigits(long number) // getting the first two digits of the inputed number
{
    while (number >= 100) // to get double digit numbers
    {
        number /= 10;
    }
    return number;
}

int getfirstDigit(long number) // getting the first digit of the inputed number
{
    while (number >= 10) // to get only single digit numbers
    {
        number /= 10;
    }
    return number;
}
