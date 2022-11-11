//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 31.10.2022 17:50:00
// Design Name: recursion
//
// Description: Program for calculating how many steps that the given number has
// to forward in order to reach the number 1 based on the given equations of
// the practice homework.
//
// Rules: Rules are described at the following link:
// https://cs50.harvard.edu/extension/2022/fall/shorts/recursion/
//
// Output: The output should print the amount of steps.
//////////////////////////////////////////////////////////////////////////////////

#include <cs50.h>
#include <stdio.h>

//Function prototype
int collatz(int number);
//Global variable
int counter = 0;

int main (void)
{
    //Prompting the user's desired number
    //then giving this number as a parameter to the
    //collatz function to calculate the steps
    int n = get_int("Enter the desired number: ");
    int result = collatz(n);
    printf("result is: %i\n", result);

}

int collatz(int number)
{
    //This is a recursive function so we are going to
    //enter this if branch at the very end that means
    //it is a base case that the number to have the value of 1
    if(number == 1)
    {
        return 1;
        counter++;
    }
    //If the number is even, divide the number by 2
    else if(number % 2 == 0)
    {
        collatz(number / 2);
        counter++;
    }
    //If the number is odd, multiply the number by three and add 1
    else if (number % 2 == 1)
    {
        collatz((3 * number) + 1);
        counter++;
    }
    return counter;
}