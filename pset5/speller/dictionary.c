// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Holds each word in hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Create hashtable of size 2^16
const int HASHTABLE_SIZE = 65536;
node *hashtable[HASHTABLE_SIZE];

// Count number of words
unsigned int counter;

// Hash function via CS50 staff member delipity
// https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn
int hash_it(char *needs_hashing)
{
    // Modify hash function to be case insensitive
    for (int i = 0; i < strlen(needs_hashing); i++)
        needs_hashing[i] = tolower(needs_hashing[i]);

    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char copy_word[LENGTH + 1];
    strcpy(copy_word, word);
    int index = hash_it(copy_word);

    node *cursor = hashtable[index];

    if(hashtable[index] == NULL)
        return false;

    while (cursor != NULL)
    {
        if(strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        counter++;
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        new_node->next = NULL;

        int index = hash_it(word);

        if(hashtable[index] == NULL)
        {
            hashtable[index] = new_node;
        }
        else
        {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
