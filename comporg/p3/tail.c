#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int CIRCULAR_BUFFER_SIZE = 10;
const int LINE_BUFFER_SIZE = 4096;
const int MAX_BUFFER_USE = 4094;

int main(int argc, char* argv[]) 
{
    char* inputFileName = argv[1];  // read the file name from console
    FILE* inFile = fopen(inputFileName, "r");   // open the file in read mode ("r")

    // error message output & program exits if the file isn't found
    if (!inFile)   
    {
        perror("- file read error: check filepath -\n");
        exit(-1);
    }

    // size 10 buffer of pointers to character buffers
    char* circularBuffer[CIRCULAR_BUFFER_SIZE];   
    char* write;
    int readWriteIndex = 0;

    // preset all 10 buffers to be null pointers
    for (int i = 0; i < CIRCULAR_BUFFER_SIZE; i++)
    {
        circularBuffer[i] = NULL;
    }

    // data for moving through file characters, & a buffer of size 4096 for temporary storage
    int currentCharInt;
    int lineIndex = 0;
    char lineBuffer[LINE_BUFFER_SIZE];
    
    // loop through all characters in the file
    while((currentCharInt = fgetc(inFile)) != EOF)
    {
        // update a tempoary 'lineBuffer', continually adding characters
        lineBuffer[lineIndex] = currentCharInt;
        lineIndex++;

        // identify a new line, move to storage in circular buffer
        if (currentCharInt == '\n')    
        {
            lineBuffer[lineIndex] = '\0';

insert:     lineIndex = 0;

            // if the circular buffer is full, have to free the next location for new data
            if (circularBuffer[readWriteIndex] != NULL)
            {
                free(circularBuffer[readWriteIndex]);
            }

            // 'write' pointer set to allocate exact amount of space for the line
            write = malloc(strlen(lineBuffer));
            if (write == NULL)  // check to make sure malloc was successful,
            {                       // output error and exit if not
                perror("- malloc failed - exiting program -\n");
                perror(lineBuffer);
                exit(-1);
            }

            // copy over from temporary 'lineBuffer' to write, then move into circular buffer
            strcpy(write, lineBuffer);
            circularBuffer[readWriteIndex] = write;

            // update circular buffer index for next data, loops back to 0 if at index 9
            readWriteIndex++;
            if (readWriteIndex == CIRCULAR_BUFFER_SIZE)
            {
                readWriteIndex = 0;
            }

            // clearing out the temporary buffer each time, make way for next line in file
            char charTemp;
            for (int i = 0; i < LINE_BUFFER_SIZE; i++)   
            {
                charTemp = lineBuffer[i];
                lineBuffer[i] = 0;
                if (charTemp == '\0')   // break the loop if null terminator was last cleared
                {
                    break;
                } 
            }
        }
        else if (lineIndex == MAX_BUFFER_USE)   // if reached 4094 chars b4 a newline
        {
            lineBuffer[lineIndex + 1] = '\n';   // add newline & null terminator
            lineBuffer[lineIndex + 2] = '\0';   // (this section may need additional testing)
            lineIndex = 0;
            goto insert;
        }

    }

    // to include the last line of the file without a newline,
    if (lineIndex > 0)  //  jump up to 'insert' label (above)
    { 
        goto insert;
    }

    // print contents of circular buffer and then free memory
    for (int i = readWriteIndex; i < CIRCULAR_BUFFER_SIZE; i++)   
    {
        printf("%s", circularBuffer[i]);
        free(circularBuffer[i]);
    }
    for (int i = 0; i < readWriteIndex; i++)
    {
        printf("%s", circularBuffer[i]);
        free(circularBuffer[i]);
    }
    printf("\n");

    // close the file, set 'inFile' pointer to NULL
    fclose(inFile);
    inFile = NULL;

    return 0;
}