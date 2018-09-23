# Questions

## What's `stdint.h`?


The <stdint.h> header shall declare sets of integer types having specified widths, and shall define corresponding sets of macros.
It shall also define macros that specify limits of integer types corresponding to types defined in other standard headers.


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?


It changes the amount of bytes allocated for an integer. Bigger allocations would put more strain on the machine.


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?


BYTE: 8
DWORD: 4
WORD: 2
LONG:4


## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."


ASCII: BM
Decimal: 66 77
Hexadecimal: 0x42 0x4d


## What's the difference between `bfSize` and `biSize`?


bfSize must be a Bitmap (BM) type file and it represents the size of this file. BiSize is the size of the file header and info header structure.


## What does it mean if `biHeight` is negative?


That the BM file a top-down DIB and its origin is at the top left corner


## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?


It's with biBitCount


## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

Unable to input or output the file. The file doesn't exist?

## Why is the third argument to `fread` always `1` in our code?

Because there is by default only element to be read. The function only has to get data from 1 element.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

It gets the information from the current pointer exluding the values after the padding.

## What is `SEEK_CUR`?

The current pointer, in contrast with a pointer that would start from the beginning of the file or the end of the file.
