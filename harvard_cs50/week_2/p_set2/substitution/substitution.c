#include <cs50.h>
#include <stdio.h>
#include <string.h>

string encrypt(string key, string message);
int check_index(char character);
bool check_if_alpha(char character);
bool check_case(char character);
void convert_to_uppercase(string key);
bool check_arg(int argc);
bool check_length(string key);
bool check_characters(string key);
bool check_duplicates(string key);

// creating a string of the alphabet for indexing
string alpha_lower = "abcdefghijklmnopqrstuvwxyz";
string alpha_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int main(int argc, string argv[])
{
    // if arg length is 2 proceed
    if (check_arg(argc))
    {
        // creating a variable key that is just argv to save on typing
        string key = argv[1];
        // converting all key characters to uppercase
        convert_to_uppercase(key);
        // checking if length is 26, if they are valid characters and
        // if there are any duplicates
        if (check_length(key) && check_characters(key) && check_duplicates(key))
        {
            // prompting for message and encrypting it
            string message = get_string("plaintext: ");
            string encrypted = encrypt(key, message);
            printf("ciphertext: %s\n", encrypted);
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

}




// main encryption function
string encrypt(string key, string message)
{
    int length = strlen(message);
    for (int i = 0; i < length; i++)
    {
        if (check_if_alpha(message[i]))
        {
            int index = check_index(message[i]);
            // if character is uppercase it remains unchanged
            if (check_case(message[i]))
            {
                message[i] = key[index];
            }
            // else character is changed to lowercase
            else
            {
                message[i] = key[index] + 32;
            }
        }
    }
    return message;
}




// This will return the proper key index for substitution
int check_index(char character)
{
    int length = strlen(alpha_lower);
    for (int i = 0; i < length; i++)
    {
        if (character == alpha_lower[i])
        {
            return i;
        }
        else if (character == alpha_upper[i])
        {
            return i;
        }
    }
    return 0;
}


// Checks whether or not a character is alphabetical
bool check_if_alpha(char character)
{
    if (character >= 65 && character <= 90)
    {
        return true;
    }
    else if (character >= 97 && character <= 122)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// will return true if uppercase and false otherwise
bool check_case(char character)
{
    if (character >= 65 && character <= 90)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// This converts the key to all uppercase letters
void convert_to_uppercase(string key)
{
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        if (!check_case(key[i]))
        {
            key[i] -= 32;
        }
    }
}

// checking multiple arguments
bool check_arg(int argc)
{
    if (argc == 2)
    {
        return true;
    }
    return false;
}

// check length of key
bool check_length(string key)
{
    if (strlen(key) == 26)
    {
        return true;
    }
    return false;
}

// checks if key has valid characters
bool check_characters(string key)
{
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        if (!check_if_alpha(key[i]))
        {
            return false;
        }
    }
    return true;
}

// checks if there are duplicate characters in key
bool check_duplicates(string key)
{
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (key[i] == key[j])
            {
                return false;
            }
        }
    }
    return true;
}
