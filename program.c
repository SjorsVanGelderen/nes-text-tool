// Copyright 2020, Sjors van Gelderen

#include <stdlib.h>
#include <stdio.h>

int BUFFER_SIZE = 512;

char* helpText = "nes-text-tool\n\n"
    "Example usage: nes-text-tool text-box-width chr-text-offset in-text-file out-chr-file";

int main(int argc, char* argv[])
{
    int textBoxWidth;
    int chrTextOffset;
    char* inTextPath;
    char* outChrPath;
    char buffer[BUFFER_SIZE];
    char c;
    int i;
    FILE* inTextFile;
    FILE* outChrFile;
    
    if(argc != 5)
    {
        puts(helpText);
        return 0;
    }

    textBoxWidth = atoi(argv[1]);
    chrTextOffset = atoi(argv[2]);
    inTextPath = argv[3];
    outChrPath = argv[4];

    inTextFile = fopen(inTextPath, "r");
    if(inTextFile == NULL)
    {
        puts("Failed to open input text file!");
        return 1;
    }

    outChrFile = fopen(outChrPath, "wb+");
    if(outChrFile == NULL)
    {
        puts("Failed to open output text file!");
        return 1;
    }

    i = 0;
    while(i < BUFFER_SIZE)
    {
        c = fgetc(inTextFile);
        if(c == EOF)
        {
            fputc(0, outChrFile); // Null terminator
            break;
        }

	// + 2 because of special characters
	// - 97 because of the ASCII offset
        fputc(c + chrTextOffset - 95, outChrFile);

        i++;
        if(i == textBoxWidth)
        {
            fputc(1, outChrFile); // Line break
            i = 0;
        }
    }

    fclose(inTextFile);
    fclose(outChrFile);
    
    return 0;
}
