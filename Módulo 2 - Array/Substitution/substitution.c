#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool keyValidation(string key, int lenght);
void encryptText(string str, string key);

int main(int argc, string argv[])
{
    if(argc == 2)
    {
        string key = argv[1];

        if(keyValidation(key, strlen(key)))
        {
            string plaintext = get_string("Submit a sentence: ");
            printf("ciphertext: ");
            encryptText(plaintext, key);

            return 0;
        }
        else
        {
            printf("ERROR: Invalid Key!");
            return 1;
        }
    }
    else
    {
        printf("ERROR: Invalid Input!");
        return 1;
    }
}

bool keyValidation(string key, int lenght)
{
    //Lenght validation
    if(lenght != 26)
    {
        return false;
    }

    //Character and Repeat validation
    char keyRepeatValidation[25];

    for(int i = 0; i < lenght; i++)
    {
        char letter = key[i];

        if(isalpha(letter))
        {
            for(int j = 0; j < lenght; j++)
            {
                if(keyRepeatValidation[j] == letter)
                {
                    return false;
                }
                else
                {
                    keyRepeatValidation[j] = letter;
                    continue;
                }
            }
        }
        else
        {
            return false;
        }
    }

    //Result
    return true;
}


void encryptText(string str, string key)
{
    for(int i = 0, n = strlen(str); i < n; i++)
    {
        char letter = str[i];

        //Find letter in key
        if(isalpha(letter) && isupper(letter))
        {
            int result = (letter - 65) % 26;
            printf("%c", toupper(key[result]));
        }
        else if(isalpha(letter) && islower(letter))
        {
            int result = (letter - 97) % 26;
            printf("%c", tolower(key[result]));
        }
        else
        {
            printf("%c", letter);
        }
    }

    printf("\n");
}