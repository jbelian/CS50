#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Try again\n");
        return 1;
    }

    int key = atoi(argv[1]);                //key number (int)
    string s = get_string("plaintext: ");   //plaintext (string)

    printf("ciphertext: ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {

        if (isalpha(s[i]))
        {
            if (isupper(s[i]))
            {
                printf("%c", ((s[i] + key - 65) % 26) + 65);
            }
            if (islower(s[i]))
            {
                printf("%c", ((s[i] + key - 97) % 26) + 97);
            }
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
}