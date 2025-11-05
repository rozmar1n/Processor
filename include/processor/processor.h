#ifndef processor_h
#define processor_h

#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common/instructions.h"
#include "common/stack/Stack.h"

const int nRegisters = 8;
const int procVersion = 2;
const int ram_volume = 10000;

struct SPU_t
{
    double*    cmds;
    int        ip;
    Stack_t    stk;
    Stack_t    proc_stk;
    double*    registers;
    double*    ram;
    FILE*      logfile;
};

bool  MakeBinSPU (const char *binFile, SPU_t *SPU);
void  Run        (SPU_t *SPU);
SPU_t MakeNullSPU();
#endif //processor
