// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t byte;
typedef int16_t int16;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    byte headerBuffer[HEADER_SIZE];

    fread(headerBuffer, HEADER_SIZE, 1, input);
    fwrite(headerBuffer, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    int16 contentBuffer;

    while(fread(&contentBuffer, sizeof(int16), 1, input)){
        contentBuffer *= factor;
        fwrite(&contentBuffer, sizeof(int16), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
