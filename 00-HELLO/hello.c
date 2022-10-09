//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 28.09.2022 23:00:00
// Design Name: hello
//
// Description: User's name is requested then printed to the screen.
//
// Rules:
//
// Output: When a user enters their name, the output should look like this:
// Hello, Username
//////////////////////////////////////////////////////////////////////////////////

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("Could you please enter your name?\n");
    string name;
    name = get_string("Name: ");
    printf("Hello, %s\n", name);
}