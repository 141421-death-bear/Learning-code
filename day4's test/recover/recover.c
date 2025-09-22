#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Couldn't open this file\n");
        return 2;
    }

    uint8_t buffer[512];
    char filename[8];
    FILE *output = NULL;
    int count = 0;

    while (fread(buffer, 1, 512, input) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (output != NULL)
            {
                fclose(output);
            }
            sprintf(filename, "%03i.jpg", count);
            output = fopen(filename, "w");
            count++;
        }
        if (output != NULL)
        {
            fwrite(buffer, 1, 512, output);
        }
    }
    fclose(output);
    fclose(input);
}
