#include "compiler/assembler.h"

#ifndef PROJECT_SOURCE_DIR
#define PROJECT_SOURCE_DIR "."
#endif

static const char kDefaultInput[]  = PROJECT_SOURCE_DIR "/resources/programs/default.txt";
static const char kDefaultOutput[] = PROJECT_SOURCE_DIR "/resources/programs/new_program.bin";
static const char kDefaultLog[]    = PROJECT_SOURCE_DIR "/resources/programs/logfile.txt";

int main(int argc, const char *argv[])
{
    char InputFile[128];
    char OutputFile[128];
    
    if (argc > 1)
    {
        strcpy(InputFile, argv[1]);
        if (argc > 2)
            strcpy(OutputFile, argv[2]);
        else
            strcpy(OutputFile, kDefaultOutput);
    }
    else
    {
        strcpy(InputFile, kDefaultInput);
        strcpy(OutputFile, kDefaultOutput);
    }
    fprintf(stderr, "InputFile: %s\n OutputFile: %s\n", InputFile, OutputFile);

    labelArray_t labels;
    LabelCtor(&labels, amount_of_labels);
    
    if (!MakeMachCode(InputFile, OutputFile, kDefaultLog, 1, &labels))
    {
        LabelDtor(&labels);
        return 1;
    }
    if (!MakeMachCode(InputFile, OutputFile, kDefaultLog, 2, &labels))
    {
        return 1;
    }
    return 0;
}
