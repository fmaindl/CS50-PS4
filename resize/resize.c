// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage; are there 3 arguments given by the user to run the program?
    if (argc != 4)
    {
        fprintf(stderr, "Make sure to type in in the order a number between 0.0 and 100.0, the name of a BMP file and the final file's name\n");
        return 1;
    }

    // remember filenames *infile and *outfile are the addresses of the name of the original file and newly created file respectively
    char *infile = argv[2];
    char *outfile = argv[3];



    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //set the variable f, a float whose value is between 0.0 and 100.0

    float f = atof(argv[1]);
    if (f < 0.0 | f > 100.0)
    {
        fprintf(stderr, "Float value %f out of bound.\n", f);
        return 3;
    }
    int scale = f + 0.5;


    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_out;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_out = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_out;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_out = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    //update BITMAPINFOHEADER for new resized file
    bi_out.biWidth = bi.biWidth * scale;
    //if bi.biHeight is positive, convert to nagative.
    bi_out.biHeight *= scale;



    // determine if the new file will require padding or not for scanlines
    int padding_out = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //determine if there is a padding in the infile
    int padding_in = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate output file image size header
    bi_out.biSizeImage = ((bi_out.biWidth * sizeof(RGBTRIPLE)) + padding_out) * abs(bi_out.biHeight);

    //update BITMAPFILEHEADER for new resized file
    bf_out.bfSize = bi_out.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);




    // case if f >= 1

    //RGBTRIPLE *temp = calloc(bi_out.biWidth, sizeof(RGBTRIPLE));





    {
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {

            for (int repeat = 0; repeat < scale; repeat ++)
            {

                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);



                    for (int h = 0; h < scale; h++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }

                }
                fseek(inptr, padding_in, SEEK_CUR);


                for (int k = 0; k < padding_out; k++)
                {
                    fputc(0x00, outptr);
                }

                if (repeat < (scale - 1))
                {
                    fseek(inptr, -(bi.biWidth * 3 + padding_in), SEEK_CUR);

                }
            }
        }


    }







    // case if f < 1

    // if ((f < 1) & (f > 0)
    // {

    // }




    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
