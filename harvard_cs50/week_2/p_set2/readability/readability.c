#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// The Coleman-Liau index is a way of determining readability by grade
// index = (0.0588 * L) - (0.296 * S) - 15.8
// L is the average number of letters per 100 words in the text, and S is the average number
// of sentences per 100 words in the text

float avg_len_words(string words);
float avg_len_sentences(string words);
void check_grade(int index);

int main(void)
{
    string words = get_string("Please paste your words: ");
    float avg_w = avg_len_words(words);
    float avg_s = avg_len_sentences(words);
    float cli_index = round(0.0588 * avg_w - 0.296 * avg_s - 15.8);
    check_grade(cli_index);

}
















// This function returns the average number of letters per word in a string of text
float avg_len_words(string words)
{
    float length = strlen(words);
    float word_length = 0;
    float word_total = 0;

    for (int i = 0; i < length; i++)
    {
        if ((words[i] >= 65 && words[i] <= 90) || (words[i] >= 97 && words[i] <= 122))
        {
            word_length ++;
        }
        else if (words[i] == 32 || i == length - 1)
        {
            word_total ++;

        }

    }
    return (word_length / word_total * 100);
}

// This finds the average amount of sentences
float avg_len_sentences(string words)
{
    float length = strlen(words);
    float total_words = 0;
    float total_sentences = 0;

    for (int i = 0; i < length; i++)
    {
        if (words[i] == 32)
        {
            total_words ++;
        }
        else if (words[i] == 46 || words[i] == 63 || words[i] == 33)
        {
            if (i == length - 1)
            {
                total_sentences ++;
                total_words ++;
            }
            else
            {
                total_sentences ++;
            }
        }
    }
    return (total_sentences / total_words * 100);
}

// Used to check grade number
void check_grade(int index)
{
    // this loops through 16 times, checking to see of the index matches i
    for (int i = 0; i < 16; i++)
    {
        if (index == i)
        {
            printf("Grade %i\n", i);
        }
    }
    // if nothing is matched, then we check if it is greater than 16
    // or less then 0
    if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
}