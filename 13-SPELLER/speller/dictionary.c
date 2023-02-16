//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 16.02.2023 20:00:00
// Design Name: speller
//
// Description: Program for reading a text file and comparing every word with
// the given dictionary. Analyzing in terms of Misspelled words, loaded words
// from the dictionary, words in the given text file and run time of the program.
// All the details about the Problem set are described at the following link:
// https://cs50.harvard.edu/x/2022/psets/5/speller/
//
// Output: The output should generate a table which includes some statistics.
// Statistics include Misspelled word information, loaded words from the
// dictionary information, words in the given text file and the run time of
// each function that defined in this code.
//////////////////////////////////////////////////////////////////////////////////
// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 25*45;

//Global variable for keeping track of the words in the given dictionary
unsigned int size_of_dictionary = 0;

// Hash table
node *table[N];

// Loads dictionary into memory, returning true if successful, else false
// Load function takes the name of the dictionary file and loads all of it's
// contents to dynamically alocated memory which is created as a hash map.
bool load(const char *dictionary)
{
    //Openining the dictionary file with read mode
    FILE *d_file = fopen(dictionary, "r");
    if(d_file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    char d_word[LENGTH + 1];
    unsigned int hash_n = 0;
    // Allocating memory for the hash map's individual member
    // Initializing the variables inside of each member
    for(int i = 0; i < N; i++)
    {
        table[i] = malloc(sizeof(node));
        strcpy(table[i] -> word, "initialize");
        table[i] -> next = NULL;
    }
    // Reading the dictionary and writing each word one by one to d_word variable
    while(fscanf(d_file, "%s", d_word) != EOF)
    {
        // Allocating memory for a node in order to create linked lists for each member of the hash map
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            printf("Could not malloc at the load function while scanning the dictionary file\n");
            printf("Current word is %s\n", d_word);
            return false;
        }
        // Initializing the node's next variable
        n -> next = NULL;
        // Copying the word from d_word to the node's word variable
        strcpy(n -> word, d_word);
        size_of_dictionary++;
        // Calling hash function to determine the place of the linked list on the hash map
        hash_n = hash(n -> word);
        // If adding the node to head of a hash map member
        if(strcmp(table[hash_n] -> word, "initialize") == 0)
        {
            strcpy(table[hash_n] -> word, n -> word);
            table[hash_n] -> next = n -> next;
        }
        // Adding the variable to the linked list
        else
        {
            n -> next = table[hash_n] -> next;
            table[hash_n] -> next = n;
        }
    }
    fclose(d_file);
    return true;
}

// Hashes word to a number
// This function runs the hash algorithm to determine the place for the hash map
unsigned int hash(const char *word)
{
    unsigned int sum_ASCII = 0;
    // Reading the word's characters one by one
    // Calculating the key value
    for(int i = 0; i < strlen(word); i++)
    {
        sum_ASCII += (toupper(word[i]) - 'A');
    }
    if(sum_ASCII > N)
    {
        return sum_ASCII % N;
    }
    else
    {
        return sum_ASCII;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if(size_of_dictionary > 0)
    {
        return size_of_dictionary;
    }
    else
    {
        return 0;
    }
}

// Returns true if word is in dictionary, else false
// Checking the text's word against the loaded dictionary
bool check(const char *word)
{
    unsigned int hash_n = 0;
    // Calling the hash function to get the place of the hash map
    hash_n = hash(word);
    node *c = table[hash_n];
    // Checking every node on the determined linked list one by one until finding the word
    // If the word is not in the list that means it is not in the dictionary then return false
    while(c != NULL)
    {
        if(strcasecmp(c -> word, word) == 0)
        {
            return true;
        }
        else
        {
            c = c -> next;
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
// Freeing all the alocated memory of the hash map
bool unload(void)
{
    size_of_dictionary = 0;
    // Iterating every member of the hash map
    for(int i = 0; i < N; i++)
    {
        // Using two pointers to move and free the memory in the linked list
        node *cursor = table[i];
        while(cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
        free(cursor);
    }
    return true;
}