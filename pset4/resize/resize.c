// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize <scale by> <infile> <outfile>\n");
        return 1;
    }

    // remember scale size and filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // n > 0 and n <= 100
    if (n <= 0 || n > 100)
    {
        fprintf(stderr, "Resize must be supplied a positive integer less than or equal to 100.");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf_in;
    fread(&bf_in, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi_in;
    fread(&bi_in, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_in.bfType != 0x4d42 || bf_in.bfOffBits != 54 || bi_in.biSize != 40 ||
        bi_in.biBitCount != 24 || bi_in.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


    //bi_in.biSizeImage = (sizeof(RGBTRIPLE) * bi_in.biWidth + in_padding) * abs(bi_in.biHeight);
    //bf_in.bfSize = bi_in.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    BITMAPFILEHEADER bf_out = bf_in;
    BITMAPINFOHEADER bi_out = bi_in;

    bi_out.biWidth = bi_in.biWidth * n;
    bi_out.biHeight = bi_in.biHeight * n;

    int in_padding = (4 - (bi_in.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_out.biSizeImage = (sizeof(RGBTRIPLE) * bi_out.biWidth + out_padding) * abs(bi_out.biHeight);
    bf_out.bfSize = bi_out.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER                     // bfSize total size: pixels, padding, and headers
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);   // bf_in.bfSize == bi_in.biSizeImage + both headers

    // write outfile's BITMAPINFOHEADER                     // width (no padding), height, biSizeImage (total size
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);   // of image with padding)


    // iterate over infile's scanlines
    for (int h = 0, biHeight = abs(bi_in.biHeight); h < biHeight; h++)
    {
        // for each row
        for (int i = 0; i < n; i++)
        {
            // for each pixel
            for (int j = 0; j < bi_in.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // store pixel from infile in buffer
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write pixel n times to outfile
                for (int k = 0; k < n; k++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // add outfile padding
            for (int l = 0; l < out_padding; l++)
                fputc(0x00, outptr);

            // return cursor to beginning of current infile scanline until the next infile scanline needs to be read
            if (i < n - 1)
                fseek(inptr, -bi_in.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }
        fseek(inptr, in_padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}