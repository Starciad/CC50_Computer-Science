#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool checkForNumbers(string setence);
void getEncryptedString(string str, int key);

//==============================//

int main(int argc, string argv[])
{
    if(argc == 2 && argv[1] > 0)
    {
        //Not numbers
        if(!checkForNumbers(argv[1]))
        {
            int key = atoi(argv[1]);
            string sentence = get_string("plaintext: ");

            printf("ciphertext: ");
            getEncryptedString(sentence, key);
            return 0;
        }
        else
        {
            printf("./ceaser key");
            return 1;
        }
    }
    else
    {
        printf("ERROR: Invalid Input! \n");
        return 1;
    }
}

bool checkForNumbers(string setence)
{
    for(int i = 0, n = strlen(setence); i < n; i++)
    {
        if(isalpha(setence[i]))
        {
            return true;
        }
    }

    return false;
}

void getEncryptedString(string str, int key)
{
    for(int i = 0, n = strlen(str); i < n; i++)
    {
        char letter = str[i];

        if(isalpha(letter) && isupper(letter))
        {
            char c = (letter - 65 + key) % 26 + 65;
            printf("%c", c);
        }
        else if(isalpha(letter) && islower(letter))
        {
            printf("%c", (letter - 97 + key) % 26 + 97);
        }
        else
        {
            printf("%c", letter);
        }
    }

    printf("\n");
}