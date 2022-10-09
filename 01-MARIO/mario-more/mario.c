//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 28.09.2022 23:55:00
// Design Name: mario
//
// Description: There some pyramids in the Nintendo's Super Mario Brothers
// game and Mario has to jump over them. In this design, pyramids are generated.
//
// Rules: How tall the pyramids are generated must based on user prompt positive
// numbers between and including 1 to 8. If user prompts other numbers or any
// other letters or words, the design must request the number again!
// Then the pyramid should be generated based on the number that the user entered.
//
// Output: When a user requests the height as 8, the output should look like this:
//        #  #
//       ##  ##
//      ###  ###
//     ####  ####
//    #####  #####
//   ######  ######
//  #######  #######
// ########  ########
//////////////////////////////////////////////////////////////////////////////////
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    do
    {
        height = get_int("Please enter a positive number for the height of the mario pyramid: ");
    }
    while ((height < 1) || (height > 8));

    for(int row = 0; row < height; row++)
    {
        for(int space = height - 1; space > row; space--)
        {
            printf(" ");
        }
        for(int left_hash = 0; left_hash <= row; left_hash++)
        {
           printf("#");
        }
        //Gap space
        printf("  ");
        for(int right_hash = 0; right_hash <= row; right_hash++)
        {
           printf("#");
        }
        printf("\n");
    }
}