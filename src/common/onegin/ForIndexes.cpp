#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/onegin/ForIndexes.h"
#include "common/onegin/struct.h"

Line* MakeIndex(char* textik, int* AmountOfLines, long TextSize)
{
    int nstrings          = 0;

    Line *strings_in_func = (Line*)calloc(TextSize, sizeof(Line));
    ((strings_in_func + 0) -> line_start) = textik;

    int CurStrLength = 0;
    int inCmd        = 0;

    for (size_t i = 0; i < TextSize; i++)
    {
        if (textik[i] == ';')
        {
            while(textik[i] != '\n')
            {
                i++;
            }
            i--;
        }
        else
        {
            if (textik[i] == '\n' || textik[i] == '\r' || isspace(textik[i]) || textik[i] == '\0')
            {
                textik[i] = '\0';
                if (inCmd)
                {
                    strings_in_func[nstrings].line_size = CurStrLength;
                    CurStrLength = 0;
                    nstrings++;
                    textik[i] = '\0';
                }
                inCmd = 0;
            }
            else
            {
                if(inCmd)
                {
                    CurStrLength++;
                }
                else
                {
                    strings_in_func[nstrings].line_start = &(textik[i]);
                }
                inCmd = 1;
            }
        }
    }

    *AmountOfLines = nstrings;
    return strings_in_func;
}

char* PutText(const char *TextFileName, long* TextSize)
{
    FILE *Text_ptr = fopen(TextFileName, "r");
    char* buffer = NULL;
    
    if(!Text_ptr)
    {
        fprintf(stderr, "We cannot open your file!\n");
        return buffer;
    }
    else
    {
        fseek(Text_ptr, 0, SEEK_END);
        long OneginSize = ftell(Text_ptr);

        buffer = (char*)calloc(OneginSize + 1, sizeof(char));

        rewind(Text_ptr);
        fread(buffer, sizeof(char), OneginSize, Text_ptr);
        fclose(Text_ptr);
        buffer[OneginSize + 1] = '\0';
        
        *TextSize = OneginSize + 1;
        return buffer;
    }
}

void OutputStrings(Line** strings, int AmountOfLines)
{
    for (int string_number = 0; string_number < AmountOfLines; string_number++)
    {
        if ((*(strings) + string_number)->line_size)
        {
            printf("%s\n", (*(strings) + string_number)->line_start);
        }
    }
    printf("\n\n\n");
}
