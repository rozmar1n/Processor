#ifndef _ForIndexes_H
#define _ForIndexes_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/onegin/struct.h"

Line* MakeIndex(char* textik, int* AmountOfLines, long TextSize);
char* PutText(const char *TextFile, long* TextSize);
void OutputStrings(Line** strings, int AmountOfLines);

#endif
