#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo %s\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    FILE *jpeg = NULL;
    char *jpeg_name = malloc(8 * sizeof(char));
    int img_counter = 0;
    while (fread(buffer, sizeof(BYTE), 512, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(jpeg_name, "%03i.jpg", img_counter);
            jpeg = fopen(jpeg_name, "w");
            img_counter++;
        }

        if (jpeg)
        {
            fwrite(buffer, sizeof(char), 512, jpeg);
        }
    }

    fclose(jpeg);
    fclose(file);
    free(jpeg_name);
    return 0;
}