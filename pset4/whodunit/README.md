# Questions

## What's `stdint.h`?

stdint.h declares a set of integer types that have fixed widths, meaning they are guaranteed
to have a certain number of bits. This allows the code to be "more portable" in different
environments.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

uint32_t, for example, is guaranteed to be an unsigned 32 bit integer data type. Because
the data types declared in stdint.h are explicit, there should be no ambiguity when using
this code in multiple environments where an int may have a different size. The point of
using so many integer data types is flexibility in size and whether or not sign (+/-) is
desired.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM

## What's the difference between `bfSize` and `biSize`?

biSize is the size of the image: height, width, and padding. bfSize is all that and the size
of the headers.

## What does it mean if `biHeight` is negative?

Negative means the image is top-down and its origins starts from the upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

For reading, NULL would be returned if the inptr didn't exist. For reading or writing, NULL
would be returned if the user had insufficient permissions.

## Why is the third argument to `fread` always `1` in our code?

In this context, fread is used to read into RGBTRIPLE and the other two header structures from
the bmp.h file. The third argument states how many times to read; fread only needs to read
"something that is the size of the structure" just once.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

fseek is used to move a file stream position indicator relative to the beginning or end of a file
or relative to the indicator's current position. The second parameter, offset, moves the indicator
by a number of bytes forwards or backwards.

## What is `SEEK_CUR`?

It's the current position of a stream's indicator -- used in the third parameter of fseek.