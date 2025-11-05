#ifndef commands_h
#define commands_h

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "common/instructions.h"
#include "common/onegin/struct.h"

struct label_t
{
    char      label_name[128];
    int       line_number;
};

struct labelArray_t
{
    label_t*  array;
    u_int32_t used_labels;
    u_int32_t capacity;
};

struct interest
{
    Line* cmds_indexes;
    int* asmIp;
    char** cmd;
    FILE* machFile;
    double* cmd_array;
    int* cmd_counter;
    u_int32_t* nCommands;
    labelArray_t* labels;
};

bool WritePush (interest* data);
bool WritePop  (interest* data);
bool WriteAdd  (interest* data);
bool WriteSub  (interest* data);
bool WriteMul  (interest* data);
bool WriteDiv  (interest* data);
bool WriteOut  (interest* data);
bool WriteIn   (interest* data);
bool WriteSqrt (interest* data);
bool WriteSin  (interest* data);
bool WriteCos  (interest* data);
bool WriteDump (interest* data);
bool WriteHult (interest* data);
bool WriteJump (interest* data);
bool WriteJa   (interest* data);
bool WriteJae  (interest* data);
bool WriteJb   (interest* data);
bool WriteJbe  (interest* data);
bool WriteJe   (interest* data);
bool WriteJne  (interest* data);
bool WriteCall (interest* data);
bool WriteRet  (interest* data);
bool WriteLabel(interest* data);
bool WritePrint(interest* data); 

int FillReg      (char* cmd);
int WritePushArgs(char* cmd, FILE* machFile, double* cmd_array, int* cmd_counter, u_int32_t *nCommands);
int WritePopArgs (char* cmd, FILE* machFile, double* cmd_array, int* cmd_counter, u_int32_t *nCommands);

double TakeLabel(labelArray_t* lblarr, char* labelName);
#endif//commands_h
