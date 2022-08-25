#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // First, we use get_string to get the users name
    string name = get_string("What is your name? ");
    //Second, we print out hello followed by the users name
    printf("hello, %s\n", name);
}