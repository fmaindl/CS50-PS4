#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"
#include <stdbool.h>


//PSEUDOCODE
// 1) open infile card.raw
// 2) Iterate over every group of 512 bytes until end of file is reached
// 3) Create an array variable in a buffer using dynamic memory allocation to stop groups of 512 bytes
// 4) Is this the beginning of a JPEG file? no? go to the next byte yes? start another iteration until reach the beginning of another
// JPEG and store it in the buffer. When reach another JPEG, write the JPEG in a file and output it.


int main(int argc, char *argv[])
{
    // ensure proper usage; is there 1 argument given by the user to run the program?
    if (argc != 2)
    {
        fprintf(stderr, "Make sure to include the name of the memory file to parse\n");
        return 1;
    }

    // remember filenames *infile and *outfile are the addresses of the name of the original file and newly created file respectively
    char *file = argv[1];

    // open input file
    FILE *inptr = fopen(file, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", file);
        return 2;
    }


    // create a buffer to store the data for each JPEG file found in the memory card
    unsigned char* buffer;
    buffer = malloc(sizeof(char) * 512);



    //iterate over each group of 512 bytes in the given file
    //note if this while condition doesn't work, try with fgetc function
    bool done = false;
    bool new_JPEG = false;
    int file_counter = 1;
    char *filename = malloc(8);
    FILE* img = NULL;


    while (done == false)
    {
        if (fread(buffer, 512, 1, inptr) == true)
        {

            // condition for the beginning of a JPEG File
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0)
            {


                sprintf(filename, "%03d.jpg", file_counter);
                file_counter += 1;
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);



                while (new_JPEG == false)
                {
                    if (fread(buffer, 512, 1, inptr) != 512)

                    {
                        done = true;
                    }

                    else if (buffer[0] == 0xff &&
                    buffer[1] == 0xd8 &&
                    buffer[2] == 0xff &&
                    (buffer[3] & 0xf0) == 0xe0)
                    {
                        new_JPEG = true;
                        fclose(img);
                        fseek(inptr, -512, SEEK_CUR);
                    }

                    else
                    {
                        fwrite(buffer, 512, 1, img);


                    }
                }
                new_JPEG = false;

            }
        }
        else
        {
            done = true;

        }
    }
    if (filename != NULL)
    {
        free(filename);
    }
    if (buffer != NULL)
    {
        free(buffer);
    }
    fclose(inptr);
    fclose(img);
}
//note sprintf(filename, "%03i.jpg", 2); (get info for the new file
//note FILE *img = fopen(filename, "w");