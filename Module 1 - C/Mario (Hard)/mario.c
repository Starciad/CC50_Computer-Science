#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int size;

    do
    {
        size = get_int("Enter tower size: ");
    }
    while(size < 1 || size > 8);

    for(int i = 0; i < size; i++)
    {
        int spacesCount = size - (i + 1);
        int builtWalls = 0;

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
                builtWalls++;
            }
        }

        printf("  ");

        for(int x = 0; x < builtWalls; x++)
        {
            printf("#");
        }

        printf("\n");
    }
}