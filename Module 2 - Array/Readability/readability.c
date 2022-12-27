// =================== //
//                     //
//                     //
// === NOT WORKING === //
//                     //
//                     //
// =================== //

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Submit a Text: ");

    int letters = 0;
    int words = 1;
    int sentences = 0;

    //Find text infos
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        if(isalpha(text[i]))
        {
            letters++;
        }
        else if(isspace(text[i]))
        {
            words++;
        }
        else if(text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    //Execution of the formula
    float l = (float)letters / (float)words * 100;
    float s = (float)sentences / (float)words * 100;

    float result = round(0.0588 * l - 0.296 * s - 15.8);

    if(result < 1)
    {
        printf("Before Grade 1\n");
    }
    if(result >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int) result);
    }
}