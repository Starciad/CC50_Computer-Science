#include <stdio.h>
//#include <cs50.h>

//4003600000000014
//12345678912345678

int main(void)
{
    long creditCardNum = get_long("Sand CreditCard number: ");

    long verifyDigits = creditCardNum;
    long oddDigits = creditCardNum / 10;
    long evenDigits = creditCardNum;
    long finalResult = 0;

    while((oddDigits * 10) >= 10)
    {
        long num = (oddDigits % 10) * 2;

        if(num >= 10)
        {
            while((num * 10) >= 10)
            {
                finalResult += num % 10;
                num /= 10;
            }
        }
        else
        {
            finalResult += num;
        }

        oddDigits /= 100;
    }

    //===========================//

    long resultNum = finalResult;
    finalResult = 0;

    while((evenDigits * 10) >= 10)
    {
        finalResult += evenDigits % 10;
        evenDigits /= 100;
    }

    finalResult += resultNum;

    if(finalResult % 2 == 0)
    {
        while(verifyDigits >= 100)
        {
            verifyDigits /= 10;
        }

        if(verifyDigits == 34 || verifyDigits == 37)
        {
            printf("AMEX\n");
        }
        else if(verifyDigits == 51 || verifyDigits == 52 || verifyDigits == 53 || verifyDigits == 54 || verifyDigits == 55)
        {
            printf("MASTERCARD\n");
        }
        else if(verifyDigits / 10 == 04)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}