// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

//prototypes
void free_list(node *current_node);

// Number of possible starting characters
const unsigned int N = 26 * LENGTH * 26;

// word in dictionary count
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *current_node = table[hash(word)];
    while (true)
    {
        if (current_node == NULL)
        {
            return false;
        }
        else if (strcasecmp(current_node->word, word) == 0)
        {
            return true;
        }
        else if (current_node->next == NULL)
        {
            return false;
        }
        current_node = current_node->next;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A' + strlen(word);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dict, "%s", word) != -1)
    {
        int word_hash = (hash(word));
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        word_count ++;
        strcpy(new_node->word, word);
        new_node->next = table[word_hash];
        table[word_hash] = new_node;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        free_list(table[i]);
    }
    return true;
}


void free_list(node *current_node)
{
    while (true)
    {
        if (current_node == NULL)
        {
            free(current_node);
            break;
        }
        else
        {
            free_list(current_node->next);
            break;
        }
    }
    free(current_node);
}