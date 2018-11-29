#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, const char* argv[])
{
    time_t start;
    start = time(NULL);

    if (argc != 2)
    {
        printf ("Usage: ./crack <hash>\n");  // quick test with hash 50WQhSkcouqck -- returns "ba"
        return 1;
    }
    else
    {
        printf("Working");
    }

    const char* hash = argv[1];

    char salt[3];
    for(int i = 0; i < 2; i++)
        salt[i] = hash[i];
    salt[2] = '\0';

    char alphabet[53] = {'\0','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char password[6];

    for(int i = 0; i < 53; i++)
    {
        if (strcmp(crypt(password, salt), hash) == 0)
        {
            break;
        }
        printf(".");
        password[0] = alphabet[i];

        for(int j = 0; j < 53; j++)
        {
            if (strcmp(crypt(password, salt), hash) == 0)
            {
                break;
            }
            password[1] = alphabet[j];

            for(int k = 0; k < 53; k++)
            {
                if (strcmp(crypt(password, salt), hash) == 0)
                {
                    break;
                }
                password[2] = alphabet[k];

                for(int m = 0; m < 53; m++)
                {
                    if (strcmp(crypt(password, salt), hash) == 0)
                    {
                        break;
                    }
                    password[3] = alphabet[m];

                    for(int n = 0; n < 53; n++)
                    {
                        if (strcmp(crypt(password, salt), hash) == 0)
                        {
                            break;
                        }
                        password[4] = alphabet[n];
                    }
                }
            }
        }
    }

    time_t end = time(NULL);
    time_t runtime = end - start;
    if(runtime > 60)
    {
        runtime = runtime / 60;
        printf("\nRuntime was %ld minutes. ", runtime);
    }
    else
    {
        printf("\nRuntime was %ld seconds. ", runtime);
    }
    if (strcmp(crypt(password, salt), hash) == 0)
    {
        printf("Found password:\n%s\n", password);
        return 0;
    }
    else
    {
        printf("Did not find password.\n");
    }
    return 1;
}
