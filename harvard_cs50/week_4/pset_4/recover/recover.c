#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int check_start_of_photo(uint8_t *buffer);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }
    // opening memory card file
    int file_number = 0;
    int found_jpeg = 0;
    FILE *file = fopen(argv[1], "r");

    // Look for beginning of JPEG
    // creating buffer array
    char *filename;
    filename = (char *)malloc(8 * sizeof(char));
    uint8_t *buffer;
    buffer = (uint8_t *)malloc(512);

    int buffer_size = sizeof(buffer);

    // fread(data, size, number, inptr)

    // data: pointer to store data,
    // size: size of element to read,
    // number: number of elements to read,
    // inptr: file to read from
    sprintf(filename, "%03i.jpg", file_number);
    FILE *img = fopen(filename, "w");

    while (fread(buffer, 1, 512, file) ==  512)
    {


        if (check_start_of_photo(buffer) == 1)
        {
            if (found_jpeg == 0)
            {
                found_jpeg = 1;
                fwrite(buffer, 1, 512, img);
            }
            else
            {
                fclose(img);
                file_number ++;
                sprintf(filename, "%03i.jpg", file_number);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
        }
        else if (found_jpeg == 1)
        {
            fwrite(buffer, 1, 512, img);
        }

    }
    fclose(img);
    fclose(file);
    free(buffer);
    free(filename);
}


int check_start_of_photo(uint8_t *buffer)
{
    if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
    {
        return 1;
    }
    return 0;
}