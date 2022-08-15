#include "cs50.h"
#include <stdio.h>

int main(void)
{   // Prompt user for x
    long x = get_long("x: ");

    // Prompt user for y
    long y = get_long("y: ");

    // you could also add int z = x + y;
    // and printf("%i\n, z)"); to save the result to a variable

    // Perform addition
    printf("%li\n", x + y);
}