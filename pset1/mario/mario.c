#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            printf(" ");
        }
        for (int k = i + 1; k > 0; k--)
        {
            printf("#");
        }
        printf("  ");
        for (int l = i + 1; l > 0; l--)
        {
            printf("#");
        }
        printf("\n");
    }
}