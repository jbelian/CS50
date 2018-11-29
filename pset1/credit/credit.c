#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long n; //CC number
    int i = 0;   //digit counter
    int v = 0;   //validity counter
    int c = 0;   //card type check

    n = get_long_long ("Credit card number: ");

    if (n < 1000000000000 || n > 9999999999999999)
    {
        printf("INVALID\n");        //CC number must be between 13 and 16 digits
        return 0;
    }

    long long loop = n;             //stores new var of CC number for use inside loop

    for ( ; loop > 0; loop *= 0.1)  //loop through CC number by moving decimal one place to the left
    {
        if (i % 2 == 0)             //"if" statement counts every other digit place starting from R->L
        {
            int m = loop % 10;      //take singles place digit
            v += m % 10;            //add to validity counter
        }
        else
        {
            int m = loop % 10;      //take singles place digit
            m = m * 2;              //double it
            v += m % 10;            //add new singles place digit to validity counter
            if (m > 9)              //if tens place exists, add 1
            {
                v += 1;
            }
        }
        i += 1;                     //count each digit
    }

    if (v % 10 != 0)                //card valid only if singles place of validity counter equal to 0
    {
        printf("INVALID\n");
        return 0;
    }

    if (i == 16)
    {
        c = n * 0.00000000000001;
        if (c == 51 || c == 52 || c == 53 || c == 54 || c == 55)
        {
            printf ("MASTERCARD\n");
        }
        else
        {
            c *= 0.1;
            if (c == 4)
            {
                printf("VISA\n");
            }
        }
    }
    else if (i == 15)
    {
        c = n * 0.0000000000001;
        if (c == 34 || c == 37)
        {
            printf("AMEX\n");
        }
    }
    else if (i == 13)
    {
        c = n * 0.000000000001;
        if (c == 4)
        {
            printf("VISA\n");
        }
    }
    return 0;
}