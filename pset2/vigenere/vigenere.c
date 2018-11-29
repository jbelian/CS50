#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)                                          //check for two arguments only
    {                                                       //only one keyword can be used to encrypt the plaintext
        printf("Supply a one word key for encryption\n");
        return 1;
    }

    string key = argv[1];                                   //string key is variable to more easily handle the keyword

    for (int i = 0, n = strlen(key); i < n; i++)            //iterate over each character
    {                                                       //if any are not letters, cancel program
        if (isalpha(key[i]) == false)
        {
            printf("Key must be alphabetic only\n");
            return 1;
        }
        else
        {
            key[i] = tolower(key[i]);           //iterate over each letter and unify into one case (as case is irrelevant)
        }
    }

    string s = get_string("plaintext: ");       //s is the plaintext to encrypt
    int j = 0;                                  //j is a counter that skips non-letters
    int k;                                      //k marks the numbers place of letter in keyword, rolls over at end: e.g. a=0, b=1
    char cipher;                                //converts an ASCII decimal value into its corresponding alphabetic cipher

    printf("ciphertext: ");

    // iterate over every char in the string
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (isalpha(s[i]))
        {
            k = (j % strlen(key));
            cipher = key[k] - 97;

            if (isupper(s[i]))
            {
                printf("%c", ((s[i] + cipher - 65) % 26) + 65);
            }
            if (islower(s[i]))
            {
                printf("%c", ((s[i] + cipher - 97) % 26) + 97);
            }
            j++;
        }
        else
        {
            printf("%c", s[i]);
        }
    }
    printf("\n");
    return 0;
}