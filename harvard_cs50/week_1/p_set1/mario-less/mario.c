#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = -1;

    // get user input of a height between 1 and 8
    while (height <= 0 || height > 8)
    {
        height = get_int("height: ");
    }

    // For each level of height
    for (int i = 1; i < height + 1;  i++)
    {
        // Create the proper amount of spaces for each row
        for (int l = height; l > i; l--)
        {
            printf(" ");
        }
        // Create the proper amount of # after spaces
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}