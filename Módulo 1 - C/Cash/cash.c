#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float cashTarget = 0;

    int coinsUsedTotal = 0;
    int twentyFiveCentsCoinsUsed = 0;
    int tenCentsCoinsUsed = 0;
    int fiveCentsCoinsUsed = 0;
    int oneCentCoinsUsed = 0;

    do
    {
        cashTarget = get_float("Enter the monetary amount: ");
    }
    while (cashTarget < 0);

    cashTarget = round(cashTarget * 100);

    while (cashTarget > 0)
    {

        if (cashTarget >= 25)
        {
            cashTarget -= 25;
            twentyFiveCentsCoinsUsed++;
        }
        else if (cashTarget >= 10)
        {
            cashTarget -= 10;
            tenCentsCoinsUsed++;
        }
        else if (cashTarget >= 5)
        {
            cashTarget -= 5;
            fiveCentsCoinsUsed++;
        }
        else
        {
            cashTarget -= 1;
            oneCentCoinsUsed++;
        }

        coinsUsedTotal++;
    }

    printf("Client coins result: \nTotal coins: %i \n\n25 cents: %i \n10 cents: %i \n5 cents: %i \n1 cents: %i\n",
           coinsUsedTotal, twentyFiveCentsCoinsUsed, tenCentsCoinsUsed, fiveCentsCoinsUsed, oneCentCoinsUsed);
}