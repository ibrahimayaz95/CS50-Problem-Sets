//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 08.01.2023 15:48:00
// Design Name: recover
//
// Description: Program for recovering JPEG files that are deleted but still stored
// as raw files. Detect 50 JPEG files and create new files for each of them and
// store their values!
// All the details about the Problem Set are described at the following link:
// https://cs50.harvard.edu/x/2022/psets/4/recover/
//
// Output: The output should generate 50 JPEG files recovered from the raw file.
//////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int block_size = 512;

int main(int argc, char *argv[])
{
    // If argc is not equal to 2 which means inputs to the command line are not as expected.
    // return 1 to exit the program
    if(argc != 2)
    {
        printf("Incorrect usage of the program! Usage: ./recover input.raw\n");
        return 1;
    }
    // Openning a file under the name of the given input file and creating a file pointer to point that file's
    // first element's address. The mode of the file is for reading.
    FILE *input_file = fopen(argv[1], "r");
    // If the pointer has not got any address, that means the file has not been opened.
    // return 2 to exit the program
    if(input_file == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }
    // buffer for storing the 512 bytes as a block from the input_file
    BYTE buffer[block_size];
    // counter for counting the image files which will be created
    int counter = 0;
    // File pointer to point at the new files. Initially it is NULL to ignore the bytes until the first JPEG!
    FILE *new_file = NULL;
    // The name of the files will be ###.jpeg that means there is need for 4 BYTES of space because
    // there will be /0 at the end of every string. The space is created from the heap to assign new
    // values each time a file is opened.
    char *file_name = malloc(4 * sizeof(char));
    // fread returns the number of data it writes to the buffer which means at the end of the input_file
    // fread will return 0 which will stop the while loop!
    while(fread(buffer, sizeof(BYTE), block_size, input_file))
    {
        // The header part of the JPEG files which is used for detection of a new JPEG is started
        if((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // Close the files after the first one is opened!
            if(counter != 0)
            {
                fclose(new_file);
            }
            // %03i.jpg - i is numbered by the counter's value and assigned as 3 digit naming
            // sprintf then assign this name to the file_name string
            sprintf(file_name, "%03i.jpg", counter);
            // new_file pointer is pointing the file_name string named file's first element
            // The mode of the file is for "writing"
            new_file = fopen(file_name, "w");
            // Increment the counter for the next JPEG file.
            counter++;
        }
        // Wait until the first JPEG, then for every JPEG write the block from buffer to the new_file!
        // When new JPEG is detected at the upper if statement, the buffer will be written to a different file!
        if(new_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), block_size, new_file);
        }
    }
    // Free the memory and close all of the files that are opened!
    free(file_name);
    fclose(new_file);
    fclose(input_file);
}