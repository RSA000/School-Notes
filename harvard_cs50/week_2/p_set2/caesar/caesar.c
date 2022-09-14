#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Caesars cipher: c = (p + k)%26
// if you shifted z by one character it should result in a
// example c = 25 + 1 = 26, 26%26 = 0 or a

// declaring cipher function
string cipher(string message, int key);
bool only_digits(string input);
// creating a string of upper and lower characters
string alpha_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string alpha_lower = "abcdefghijklmnopqrstuvwxyz";

// The user is can provide a command line argument to choose the key (k)
int main(int argc, string argv[])
{
    // Error Hanlding
    if (argc == 2 && only_digits(argv[1]))
    {
        // converting argument into a int
        int key_int = atoi(argv[1]);
        // requesting a string and then ciphering it
        string msg = get_string("plaintext: ");
        string ciphered = cipher(msg, key_int);
        printf("ciphertext: %s\n", ciphered);
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}


bool only_digits(string input)
{
    // if any of the characters in the string are non numeric
    // the loop will return false and otherwise true
    int length = strlen(input);
    for (int i = 0; i < length; i++)
    {
        if (input[i] < 48 || input[i] > 57)
        {
            return false;
        }
    }
    return true;
}


string cipher(string message, int key)
{
    int length = strlen(message);
    for (int i = 0; i < length; i++)
    {
        if (message[i] >= 65 && message[i] <= 90)
        {
            int num = message[i] - 65;
            message[i] = alpha_upper[(num + key) % 26];
        }
        else if (message[i] >= 97 && message[i] <= 122)
        {
            int num = message[i] - 97;
            message[i] = alpha_lower[(num + key) % 26];
        }
    }
    return message;
}