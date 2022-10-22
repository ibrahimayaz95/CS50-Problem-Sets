//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 19.10.2022 23:30:00
// Design Name: readability
//
// Description: Program for determining user's grade by evaluating the string
// that entered by the user.
//
// Rules: Rules are described at the following link:
// https://cs50.harvard.edu/x/2022/psets/2/readability/
//
// Output: The output can only be either Before Grade 1, Grade X (X is the number
// of the grade until 16) or Grade 16+
//////////////////////////////////////////////////////////////////////////////////

//Libraries are added to manipulate strings with functions that are predefined
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Function prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Prompted the string from the user and stored it in a variable called text
    string text = get_string("Text: ");
    //Function call from a function called count_letters which counts how many letter
    //does this string contains in an int form and stored it in a variable called letter_called
    int letter_count = count_letters(text);
    //Function call from a function called count_words which counts how many words
    //does this string contains in an int form and stored it in a variable called word_count
    int word_count = count_words(text);
    //Function call from a function called count_sentences which counts how many sentences
    //does this string contains in an int form and stored it ina variable called sentence_count
    int sentence_count = count_sentences(text);

    //To calculate the equations that are described in the Problem Set, all the variables are
    //stored in a double typed variables.
    double L = 0;
    double S = 0;
    double LC = letter_count;
    double WC = word_count;
    double SC = sentence_count;

    //L is the average number of letters per 100 words
    L = ((LC) / (WC)) * 100;
    //S is the average number of sentences per 100 words
    S = ((SC) / (WC)) * 100;

    double grade;
    //Grade calculation
    grade = (0.0588 * L) - (0.296 * S) - (15.8);

    //At the end, grade should be rounded to an integer
    int converted_grade = (int)grade;
    int rounded_grade = 0;

    //Rounding implementation
    if(grade < converted_grade + 0.5)
    {
        rounded_grade = converted_grade;
    }
    else
    {
        rounded_grade = converted_grade + 1;
    }
    //Grade determination logic
    if(rounded_grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if(rounded_grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", rounded_grade);
    }
}

//With the usage of ctype and string libraries, every char is evaluated one by one
//wheter they are alphabetic or not to determine the letter count.
int count_letters(string text)
{
    int letter_count = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if(isalpha(text[i]))
        {
            letter_count++;
        }
        else
        {
            letter_count += 0;
        }
    }
    return letter_count;
}

//With the usage of ctype and string libraries, every word is evaluated by
//searching blanks or spaces to determine the word count. (Evey word should
//be seperated by spaces)
int count_words(string text)
{
    int word_count = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if(isspace(text[i]) || isblank(text[i]))
        {
            word_count++;
        }
        else
        {
            word_count += 0;
        }
    }
    word_count++;
    return word_count;
}

//With the usage of ctype and string libraries, every sentence is evaluated by
//searching '.', '!' or '?' to determine the sentence count. (Evey sentence should
//be seperated by this symbols according to the problem set's rules)
int count_sentences(string text)
{
    int sentence_count = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if(text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence_count++;
        }
        else
        {
            sentence_count += 0;
        }
    }
    return sentence_count;
}