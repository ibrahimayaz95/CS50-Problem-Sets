//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 23.10.2022 18:50:00
// Design Name: substitution
//
// Description: Program for encrypting the user's message by a key that is
// provided by the user at run time. The key is provided by typing 26 alphabetic
// non ordered letters on command line after the executable command.
// The program will give the output by encrypting the user's message with the
// usage of the user's provided key.
//
// Rules: Rules are described at the following link:
// https://cs50.harvard.edu/x/2022/psets/2/substitution/
//
// Output: The output should print the encrypted version message of the user's
// original message. There are some other error messages should be printed if
// the user doesn't obey the rules.
//////////////////////////////////////////////////////////////////////////////////

//Libraries are added to manipulate strings with functions that are predefined
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Function prototype
string encryption(string key);

int main(int argc, string argv[])
{
    //Storing the user's key
    string key;
    key = argv [1];

    //Returning an error message if user does not provide any key
    if(argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if(argc == 2)
    {
        //Returning an error message if user types non alphabetic characters
        int counter = 0;
        for(int i = 0; i < strlen(key); i++)
        {
            if(isalpha(key[i]))
            {
                counter++;
            }
            else
            {
            printf("Key must contain 26 characters.\n");
            return 1;
            }
        }
        //Returning an error message if user types less than 26 characters which corresponds an encrypted alphabet
        if(counter != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else
        {
            //Returning an error message if user enters duplicated letters inside of the key
            for(int i = 0; i < strlen(key); i++)
            {
                for(int j = i + 1; j < strlen(key); j++)
                {
                    if(key[i] == toupper(key[j]))
                    {
                        printf("Key must contain 26 different characters.\n");
                        return 1;
                    }
                    else if(key[i] == tolower(key[j]))
                    {
                        printf("Key must contain 26 different characters.\n");
                        return 1;
                    }
                }
            }
            //Function call back of achieved encrypted message
            string real_string = encryption(key);
            printf("ciphertext: %s\n", real_string);
            return 0;
        }
    }
    else
    {
        //Returning an error message for the other conditions such as typing multiple keys
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

string encryption(string key)
{
    //Requesting the message from the user that will be encrypted
    string user_input = get_string("plaintext: ");
    string lower_case_alphabet = "abcdefghijklmnopqrstuvwxyz";
    string upper_case_alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //Handling all the characters of the user's message one by one
    //If a character is upper-case, upper-case alphabet string is searched for finding the index
    //of that exact character. After finding the index on the upper-case alphabet
    //this index will be used on key to find the corresponded character.
    //When a character is upper-case, key can contain that character as upper-case or lower-case form
    //So the user input message's letter is changed by the key's forcly converted upper-case
    //letter.
    //If a character is lower-case, the exact logic is implemented in terms of lower case version
    for (int i = 0; i < strlen(user_input); i++)
    {
        char temp = user_input[i];
        if(isupper(temp))
        {
            for(int j = 0; j < strlen(key); j++)
            {
                if(upper_case_alphabet[j] == temp)
                {
                    user_input[i] = toupper(key[j]);
                }
            }
        }
        else if(islower(temp))
        {
            for(int j = 0; j < strlen(key); j++)
            {
                if(lower_case_alphabet[j] == temp)
                {
                    user_input[i] = tolower(key[j]);
                }
            }
        }
    }
    return user_input;
}