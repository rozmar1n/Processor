#ifndef _Stack_H
#define _Stack_H

//#include"TXLib.h"
#include<cassert>

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>

typedef double StackElem_t;
typedef unsigned long long hash_t;

struct Stack_t
{
    StackElem_t* stk_array;
    size_t stk_size;
    size_t stk_capacity;
    hash_t stk_hash;
    FILE* logfile = NULL;
};

enum errors_t
{
    good_stack,
    bad_stk_size,
    left_canary_died,
    right_canary_died,
    hash_was_died,
    bad_log_file
};

int StackPush(Stack_t* stk, StackElem_t elem);
int StackPop(Stack_t* stk, StackElem_t* elem);
int StackCtor(Stack_t* stk, StackElem_t fst_elem);
int StackDtor(Stack_t* stk);
int StackDump(const Stack_t* stk);
enum errors_t StackError(const Stack_t* stk);
void StackAssert(const Stack_t* stk, const char *file_name, const int line);
hash_t StackHashFunc(const Stack_t* stk);




#endif 