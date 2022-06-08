#include <stdio.h>
//#include <cs50.h>

int main(void)
{
    int size;

    do
    {
        //Get a number of User
        size = get_int("Enter tower size: ");
    }
    while(size < 1 || size > 8);

    // Loop responsible for drawing the lines
    for(int i = 0; i < size; i++)
    {
        // Number of empty spaces a line will have
        int spacesCount = size - (i + 1);

        // Loop responsible for placing the characters on each line
        for(int x = 0; x < size; x++)
        {
            if(spacesCount > 0)
            {
                printf(" ");
                spacesCount--;
            }
            else
            {
                printf("#");
            }
        }

        printf("\n");
    }
}