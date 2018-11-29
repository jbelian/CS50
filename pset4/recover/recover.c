#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // attempt to open memory card
    FILE *memcard = fopen(argv[1], "r");
    if (memcard == NULL)
    {
        fprintf(stderr, "Could not read image\n");
        return 1;
    }

    // memory card block size is 512 bytes
    typedef uint8_t BYTE;
    BYTE block[512];

    // image file
    FILE *img = NULL;

    // jpg filename and number
    char filename[8];
    int jpg_number = 0;

    // determines when first image is found
    int found = 0;

    // until end of card, read block size into buffer
    while(fread(&block, sizeof(block), 1, memcard))
    {
        // finds new jpg header
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // close and stop writing to previous image unless this is the first image
            if(found == 1)
                fclose(img);
            else
                found = 1;

            // create filename and number of next jpg
            jpg_number++;
            sprintf(filename, "%03i.jpg", jpg_number);

            // open image to be written to
            img = fopen(filename, "w");
        }

        // write next block from memory card into currently open image
        if(found == 1)
            fwrite(&block, sizeof(block), 1, img);
    }

    fclose(img);
    fclose(memcard);
    return 0;
}