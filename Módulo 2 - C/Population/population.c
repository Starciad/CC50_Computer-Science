#include <stdio.h>
//#include <cs50.h>

int main(void)
{
    int populationStartSize = 0;
    int pupulationEndSize = 0;

    int populationCurrentSize = 0;
    int populationYears = 0;

    //Get Start Size
    do
    {
        populationStartSize = get_int("Submit the start population size: ");
    } while(populationStartSize < 9);

    //Get End Size
    do
    {
        pupulationEndSize = get_int("Submit the end population size: ");
    } while(pupulationEndSize < populationStartSize);

    populationCurrentSize = populationStartSize;
    while(populationCurrentSize < pupulationEndSize)
    {
        int bornLlamas = populationCurrentSize / 3; //New members
        int deadLlamas = populationCurrentSize / 4; //Death members

        populationCurrentSize += bornLlamas - deadLlamas;

        populationYears++;
    }

    printf("Years: %i", populationYears);
}