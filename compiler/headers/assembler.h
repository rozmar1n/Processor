#ifndef assm_h
#define assm_h


#include <string.h>

#include <assert.h>
#include <memory.h>
#include <stdbool.h>
#include "../../instructions.h"
#include "../../onegin/ForIndexes.h"
#include "commands.h"


const int       ass_version      = 2;
const size_t    max_label_name   = 128;
const int       amount_of_labels = 7;
//const char      nullstring[128]  = {'\0'}; 

bool   MakeMachCode(const char* ProgrammFile, const char* cmdFile, const char* logFile, int iter, labelArray_t* labels);
void   BinWrite    (double* cmd_array, const char* BinFileName, u_int32_t nComands);

int    FillReg(char* cmd);
int    WritePushArgs(char* cmd, FILE* machFile, double* cmd_array, int* cmd_counter, u_int32_t *nCommands);
int    WritePopArgs (char* cmd, FILE* machFile, double* cmd_array, int* cmd_counter, u_int32_t *nCommands);

void   LabelCtor  (labelArray_t* lblarr, int nlabels);
void   LabelDtor  (labelArray_t* lblarr);
void   LabelDump  (labelArray_t* lblarr);
void   MakeLabel  (labelArray_t* lblarr, char* labelName, int lineNumber);
//double TakeLabel  (labelArray_t* lblarr, char* labelName);
int    IsLabel    (labelArray_t* lblarr, char* labelName);
#endif //assm_h