//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 18.10.2022 07:30:00
// Design Name: scrabble
//
// Description: Program for comparing two strings as in the rules of scrabble
// where every word has a value in terms of numbers. Requesting two string inputs
// from the user and comparing them with their total values in numbers.
//
// Rules: Rules are described at the following link:
// https://cs50.harvard.edu/x/2022/labs/2/
//
// Output: The output can only be either Player 1 wins!, Player 2 wins!, or Tie!
//////////////////////////////////////////////////////////////////////////////////
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //Comparing the Results
    if(score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if(score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    char character;
    int result = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        character = word[i];
        //If the character is Upper case, we can subtract it's ASCI correspond from 'A' which is 65 in ASCI and also is the 0 index for our POINTS array.
        //Which will give the the index number at the POINTS array.
        if(isupper(character))
        {
            result += POINTS[word[i] - 'A'];
        }
        //If the character is Lower case, we can subtract it's ASCI correspond from 'a' which is 97 in ASCI and also is the 0 index for our POINTS array.
        //Which will give the the index number at the POINTS array.
        else if(islower(character))
        {
            result += POINTS[word[i] - 'a'];
        }
        else
        result += 0;
    }
    return result;
}