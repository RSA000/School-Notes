#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = -1;
    // Check if height is between
    while (height <= 0 || height > 8)
    {
        height = get_int("Please select height: ");
    }

    // Loops through height number of times
    for (int i = 0; i < height; i++)
    {
        // loops through creating the amount spacing for the first pyramid
        for (int k = height - 1; k > i; k--)
        {
            printf(" ");
        }
        // loops through creating # blocks on the left
        for (int j = -1; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        // Generate right side of blocks
        for (int p = -1; p < i; p++)
        {
            printf("#");
        }
        printf("\n");
    }
}