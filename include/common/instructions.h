#ifndef instructions_h
#define instructions_h

#include <stdlib.h>

const u_int32_t signatura = 82798384;

//TODO: массив структур для названия команды в ассемблере, в коде и ее номер 

enum instruction_t
{
    cmd_push           =  1,
    cmd_pushr          =  2,
    cmd_push_pushr     =  3,
    cmd_ram_push       =  5,
    cmd_ram_pushr      =  6,
    cmd_ram_push_pushr =  7,

    cmd_pop_r          = 8,
    cmd_pop_m          = 12,
    cmd_pop_m_r        = 14,
    cmd_pop_mpr        = 13,
    cmd_pop_mpm        = 15,

    cmd_add            = 38,
    cmd_sub            = 39,
    cmd_mul            = 40,
    cmd_div            = 41,
    cmd_out            = 42,
    cmd_in             = 43,
    cmd_sqrt           = 44,
    cmd_sin            = 45,
    cmd_cos            = 46,
    cmd_dump           = 47,
    cmd_jmp            = 49,
    cmd_ja             = 50,
    cmd_jae            = 51,
    cmd_jb             = 52,
    cmd_jbe            = 53,
    cmd_je             = 54,
    cmd_jne            = 55,
    cmd_call           = 56,
    cmd_ret            = 57,
    cmd_print          = 58,
    cmd_hlt            = -1
};

enum registr_t
{
    ax = 0,
    bx = 1,
    cx = 2,
    dx = 3,
    ex = 4,
    fx = 5,
    gx = 6,
    hx = 7
};

#endif //instructions_h