#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

#define CHUNK_SIZE 512

int main(int argc, char *argv[])
{
    int jpgCounter = 0;
    BYTE buffer[512];
    FILE *img = NULL;
    char filename[8];
    size_t readSize;

    //check for correct number of arguments
    if(argc != 2) {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //initialize file and check to see whether you were able to open it
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Could not open file!\n");
        return 1;
    }
    readSize = fread(&buffer, sizeof(BYTE), CHUNK_SIZE, file);
    //loop we have nothing left to read
    while(readSize == 512) {

        //did we find a valid jpg header and beginning of this chunk?
        bool isStartOfJPG = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;

        //we have an active jpg
        if(img != NULL) {
            //we found new jpg while previous file still open. close that file
            if(isStartOfJPG) {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpgCounter++);
                img = fopen(filename,"w");
            }
        }
        //if previous jpg is already closed open a new one except for first time
        else {
            sprintf(filename, "%03i.jpg", jpgCounter);
            img = fopen(filename,"w");
            //we dont want to increment first time we start parsing
            if(jpgCounter != 0) {
                jpgCounter++;
            }
        }

        //write data to appropriate file
        fwrite(buffer, sizeof(BYTE), readSize, img);

        //read next chunk of data
        readSize = fread(&buffer, sizeof(BYTE), CHUNK_SIZE, file);

    }

    //finish IO streams
    fclose(file);
    fclose(img);

    return 0;
}
