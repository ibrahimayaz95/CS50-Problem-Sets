//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 08.10.2022 21:16:00
// Design Name: credit
//
// Description: Program for checking the validity of generic Credit Card numbers
// and categorizing them by their brands.
//
// Rules: Rules are described at the following link:
// https://cs50.harvard.edu/x/2022/psets/1/credit/
//
// Output: When a user enters a credit cart, answers can only be like on the below:
// AMEX
// MASTERCARD
// VISA
// INVALID
//////////////////////////////////////////////////////////////////////////////////
/*
    Description of the code
    1. Ask the user's Credit Card number with get_long function and store it to a variable.
    2. First step is to make sure that the Credit Card Number is a Valid number.
    Creating a total and a counter will help us to calculate the validatity of
    the credit card. When counter is an even number, the total number will
    be incremented directly by the modular 10 of the credit card number.
    When counter is an odd number, total number will be incremented
    seperately by adding two numbers which are calculated according to
    the validaty rules. Counter will be incremented and temporary will
    lost its one digit in every step! If the total number can be divided
    by 10, the process continous by determining the type of the card.
    3. We are using(for loop) same logic for calculating the amount of the digit numbers
    of the credit card. Then bunch of if-else statements are questioning the type
    by the general rules of the credit card types.
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long temporary = get_long("Please enter your credit card number: ");
    long credit = temporary;
    int counter = 0;
    int total = 0;
    while (temporary > 0)
    {
        if(counter % 2 == 1)
        {
            int temp_number = (temporary % 10) * 2;
            total = total + temp_number % 10;
            total = total + temp_number / 10;
        }
        else if (counter % 2 == 0)
        {
            total = total + temporary % 10;
        }
        temporary = temporary / 10;
        counter++;
    }

    if(total % 10 == 0)
    {
        counter = 0;
        temporary = credit;
        while (temporary > 0)
        {
            temporary = temporary / 10;
            counter++;
        }

        for(int i = 1; i < counter - 1; i++)
        {
            credit = credit / 10;
        }

        if(counter == 13 || counter == 16)
        {

            if(credit / 10 == 4)
            {
                printf("VISA\n");
            }
            else if(credit == 51 || credit == 52 || credit == 53 || credit == 54 || credit == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (counter == 15)
        {
            if(credit == 34 || credit == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}