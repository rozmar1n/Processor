#include "processor/processor.h"
const int BufferSize = 25;
const int InfoSize = 16;

bool  MakeBinSPU (const char *binFile, SPU_t *SPU)
{
    if (binFile == NULL || SPU == NULL)
    {
        fprintf(stderr, "MakeBinSPU: invalid arguments\n");
        return false;
    }

    FILE* machCode = fopen(binFile, "rb");
    if (machCode == NULL)
    {
        fprintf(stderr, "MakeBinSPU: unable to open '%s'\n", binFile);
        return false;
    }
    
    u_int32_t signature = 0;
    if (fread(&signature, sizeof(u_int32_t), 1, machCode) != 1)
    {
        fprintf(stderr, "MakeBinSPU: failed to read signature\n");
        fclose(machCode);
        return false;
    }
    if (signature != signatura)
    {
        fprintf(stderr, "MakeBinSPU: unsupported signature (got %u, expected %u)\n",
                signature, signatura);
        fclose(machCode);
        return false;
    }
    
    int ass_version = 0;
    if (fread(&ass_version, sizeof(int), 1, machCode) != 1)
    {
        fprintf(stderr, "MakeBinSPU: failed to read assembler version\n");
        fclose(machCode);
        return false;
    }
    if (ass_version != procVersion)
    {
        fprintf(stderr, "MakeBinSPU: incompatible versions (file %d, processor %d)\n",
                ass_version, procVersion);
        fclose(machCode);
        return false;
    }

    u_int32_t nComands = 0;
    if (fread(&nComands, sizeof(u_int32_t), 1, machCode) != 1)
    {
        fprintf(stderr, "MakeBinSPU: failed to read command count\n");
        fclose(machCode);
        return false;
    }

    double* buffer = (double*)calloc(nComands + 100, sizeof(double));
    if (buffer == NULL)
    {
        fprintf(stderr, "MakeBinSPU: out of memory for %u commands\n", nComands);
        fclose(machCode);
        return false;
    }

    size_t read = fread(buffer, sizeof(double), nComands, machCode);
    fclose(machCode);
    if (read != nComands)
    {
        fprintf(stderr, "MakeBinSPU: expected %u commands, read %zu\n", nComands, read);
        free(buffer);
        return false;
    }
    
    free(SPU->cmds);
    SPU->cmds = buffer;
    SPU->ip   = 0;

    return true;
}

void add_f(SPU_t *SPU) // prefix
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    double b = NAN;
    StackPop(&(SPU->stk), &b);
    assert(a != NAN && b != NAN);
    StackPush(&(SPU->stk), a + b);
    SPU->ip += 1;
}

void sub_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    double b = NAN;
    StackPop(&(SPU->stk), &b);
    assert(a != NAN && b != NAN);
    StackPush(&(SPU->stk), b - a);
    SPU->ip += 1;
}

void jmp_f(SPU_t *SPU)
{
    int temp_ip = SPU->cmds[SPU->ip+1];
    SPU->ip = temp_ip;
}

void ja_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b > a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip += 2;
}

void jae_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b >= a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip += 2;
}

void jb_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b < a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip += 2;
}

void jbe_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b <= a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip += 2;
}

void je_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b == a)
    {
        int temp_ip = (int)(SPU->cmds[SPU->ip+1]);
        SPU->ip = temp_ip;
    }
    else
        SPU->ip += 2;
}

void jne_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    double b = 0;
    StackPop(&SPU->stk, &b);
    if (b != a)
    {
        int temp_ip = SPU->cmds[SPU->ip+1];
        SPU->ip = temp_ip;
    }
    else
        SPU->ip += 2;
}

void div_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    double b = NAN;
    StackPop(&(SPU->stk), &b);
    assert(a != NAN && b != NAN);
    StackPush(&(SPU->stk), b/a);
    SPU->ip += 1;
}

void mul_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    double b = NAN;
    StackPop(&(SPU->stk), &b);
    assert(a != NAN && b != NAN);
    StackPush(&(SPU->stk), b*a);
    SPU->ip += 1;
}

void sqrt_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    assert(a != NAN);
    StackPush(&(SPU->stk), sqrt(a));
    SPU->ip += 1;
}

void sin_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    assert(a != NAN);
    StackPush(&(SPU->stk), sin(a));
    SPU->ip += 1;
}

void cos_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    assert(a != NAN);
    //fprintf(stderr, "%lg ", a);
    a = cos(a);
    //fprintf(stderr, "%lg \n", a);
    StackPush(&(SPU->stk), cos(a));
    SPU->ip += 1;
}

void call_f(SPU_t *SPU)
{
    StackPush(&SPU->proc_stk, (double)(SPU->ip));
    jmp_f(SPU);
}

void ret_f(SPU_t *SPU)
{
    double temp_ip = -1;
    StackPop(&SPU->proc_stk, &temp_ip);
    SPU->ip = (int)(temp_ip + 2);
}

void in_f(SPU_t *SPU)
{
    double a = NAN;
    scanf("%lg", &a);
    StackPush(&(SPU->stk), a);
    SPU->ip += 1;
}

void out_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    assert(a != NAN);
    if (SPU->logfile)
    {
        fprintf(SPU->logfile, "\tOUT: %lg\n", a);
    }
    fprintf(stdout, "\tOUT: %lg\n", a);
    fflush(stdout);
    SPU->ip += 1;
}

void print_f(SPU_t *SPU)
{
    double a = NAN;
    StackPop(&(SPU->stk), &a);
    assert(a != NAN && a < 256);
    

    if (a < 0.00001)
    {
        if (SPU->logfile)
        {
            fprintf(SPU->logfile, "  ");
        }
        fprintf(stdout      , "  ");
    }
    else
    {
        if (SPU->logfile)
        {
            fprintf(SPU->logfile, "%c ", (char)(a));
        }
        fprintf(stdout, "%c ", (char)(a));
        fflush(stdout);
    }
    SPU->ip += 1;
}

void pushr_f(SPU_t *SPU)
{
    int64_t reg = -1;
    reg = (int64_t)(SPU->cmds[SPU->ip + 1]);
    //fprintf(stderr, "reg: %ld\n", reg);
    StackPush(&SPU->stk, SPU->registers[reg]);
    SPU->ip += 2;
}

void push_pushr_f(SPU_t * SPU)
{
    int64_t reg = -1;
    reg = (int64_t)(SPU->cmds[SPU->ip + 1]);
    
    double addition = -1;
    addition = SPU->cmds[SPU->ip + 2];
    StackPush(&SPU->stk, SPU->registers[reg] + addition);
    SPU->ip += 3;
}

void ram_push_f(SPU_t *SPU)
{
    int64_t ram_cell = -1;
    ram_cell = SPU->cmds[SPU->ip + 1];
    StackPush(&SPU->stk, SPU->ram[ram_cell]);
    SPU->ip += 2;
}
void ram_pushr_f(SPU_t *SPU)
{
    int64_t reg = -1;
    reg = (int64_t)(SPU->cmds[SPU->ip + 1]);
    int64_t ram_cell = (int64_t)(SPU->registers[reg]);
    StackPush(&SPU->stk, SPU->ram[ram_cell]);
    SPU->ip += 2;
}
void ram_push_pushr_f(SPU_t *SPU)
{
    int64_t reg = -1;
    //memcpy(&reg, &(SPU->cmds[SPU->ip + 1]), sizeof(int64_t));
    reg = (int64_t)(SPU->cmds[SPU->ip + 1]);
    int64_t ram_cell = (int64_t)(SPU->registers[reg]);

    int64_t addition = -1;
    addition = (int64_t)(SPU->cmds[SPU->ip + 2]);

    StackPush(&SPU->stk, SPU->ram[ram_cell + addition]);
    SPU->ip += 3;
}

void pop_r_f(SPU_t *SPU)
{
    double a = 0;
    StackPop(&SPU->stk, &a);
    SPU->registers[(long long int)(SPU->cmds[SPU->ip + 1])] = a;
    SPU->ip += 2;
}

void pop_m_f(SPU_t *SPU)
{
    double a = -1;
    StackPop(&SPU->stk, &a);
    SPU->ram[(long long int)(SPU->cmds[SPU->ip + 1])] = a;
    SPU->ip += 2;
}

void pop_m_r_f(SPU_t *SPU)
{
    int64_t reg = -1;
    memcpy(&reg, &(SPU->cmds[SPU->ip+1]), sizeof(int64_t));
    double data = 0;
    StackPop(&SPU->stk, &data);
    SPU->ram[(long long int)(SPU->registers[reg])] = data;
    SPU->ip += 2;
}

void pop_mpr_f(SPU_t *SPU)
{
    int64_t reg = -1;
    memcpy(&reg, &(SPU->cmds[SPU->ip+1]), sizeof(int64_t));
    int64_t addition = -1;
    addition = (int64_t)SPU->cmds[SPU->ip+2];
    double data = 0;
    StackPop(&SPU->stk, &data);
    SPU->ram[(long long int)(SPU->registers[reg]) + addition] = data;
    SPU->ip += 3;
}

void pop_mpm_f(SPU_t *SPU)
{
    int64_t ram_cell = -1;
    ram_cell = (int64_t)(SPU->cmds[SPU->ip+1]);
    ram_cell += (int64_t)(SPU->cmds[SPU->ip+2]);
    double data = 0;
    StackPop(&SPU->stk, &data);
    SPU->ram[ram_cell] = data;
    SPU->ip += 3;
}
void Run(SPU_t *SPU)
{
    if (SPU == NULL || SPU->cmds == NULL)
    {
        fprintf(stderr, "Run: no program loaded\n");
        return;
    }
    int runCond = 0;
    int64_t t_cmd = 6669;
    while(runCond == 0)
    {
        memcpy(&t_cmd, &(SPU->cmds[SPU->ip]), sizeof(int64_t));
        if (SPU->logfile)
        {
            fprintf(SPU->logfile, "cmd: %ld\n", t_cmd);
        }
        //fprintf(stderr, "cmd: %ld\n", t_cmd);
        if ((t_cmd & 240))
        {   
            switch (t_cmd)
            {
            case cmd_add: {
                add_f(SPU);
                break;
            }
            case cmd_sub: {
                sub_f(SPU);
                break;
            }
            case cmd_div: {
                div_f(SPU);
                break;
            }    
            case cmd_mul: {
                mul_f(SPU);
                break;
            }
            case cmd_sqrt: {
                sqrt_f(SPU);
                break;
            }
            case cmd_sin: {
                sin_f(SPU);
                break;
            }
            case cmd_cos: {
                cos_f(SPU);
                break;
            }
            case cmd_hlt: {
                if (SPU->logfile)
                {
                    fprintf(SPU->logfile, "The program has finished.\n");
                }
                StackDtor(&(SPU->stk));
                StackDtor(&(SPU->proc_stk));
                free(SPU->ram);
                free(SPU->cmds);
                free(SPU->registers);
                if (SPU->logfile)
                {
                    if (SPU->logfile != stderr)
                    {
                        fclose(SPU->logfile);
                    }
                    else
                    {
                        fflush(stderr);
                    }
                }
                SPU->logfile = NULL;
                runCond = 1;
                break;
            }
            case cmd_dump: {
                StackDump(&(SPU->stk));//TODO: написать нормальный дамп
                SPU->ip += 1;
                break;
            }
            case cmd_in: {
                in_f(SPU);
                break;
            }
            case cmd_out: {
                out_f(SPU);
                break;
            }
            case cmd_jmp: {
                jmp_f(SPU);
                break;
            }
            case cmd_ja: {
                ja_f(SPU);
                break;
            }
            case cmd_jae: {
                jae_f(SPU);
                break;
            }
            case cmd_jb: {
                jb_f(SPU);
                break;
            }
            case cmd_jbe: {
                jbe_f(SPU);
                break;
            }
            case cmd_je: {
                je_f(SPU);
                break;
            }
            case cmd_jne: {
                jne_f(SPU);
                break;
            }
            case cmd_call: {
                call_f(SPU);
                break;
            }
            case cmd_ret: {
                ret_f(SPU);
                break;
            }
            case cmd_print: {
                print_f(SPU);
                break;
            }
            default: 
                fprintf(stderr, 
                "\n------------------Invalid command"
                "--------------\n");
                exit(0);
                break;
            }
        }
        else
        {   
            if (t_cmd & 8ll)
            {
                if (t_cmd & 4)
                {
                    if(t_cmd & 2)
                    {
                        if (t_cmd & 1)
                        {
                            //fprintf(stderr, "This is pop_mpm\n");
                            pop_mpm_f(SPU);
                        }
                        else
                        {
                            //fprintf(stderr, "This is pop_m_r\n");
                            pop_m_r_f(SPU);
                        }
                    }
                    else
                    {
                        if(t_cmd & 1)
                        {
                            //fprintf(stderr, "This is pop_mpr\n");
                            pop_mpr_f(SPU);
                        }
                        else
                        {
                            //fprintf(stderr, "This is pop_m\n");
                            pop_m_f(SPU);
                        }
                    }
                }
                else
                {
                    //fprintf(stderr, "This is pop_r)))\n");
                    pop_r_f(SPU);
                }
            }
            else
            {
                if (t_cmd & 4)
                {
                    if (t_cmd & 2)
                    {
                        if (t_cmd & 1)
                        {
                            //fprintf(stderr, "This is ram_push_pushr\n");
                            ram_push_pushr_f(SPU);
                        }
                        else
                        {
                            //fprintf(stderr, "This is ram_pushr\n");
                            ram_pushr_f(SPU);
                        }
                    }
                    else
                    {
                        //fprintf(stderr, "This is ram_push\n");
                        ram_push_f(SPU);

                    }
                }
                else
                {
                    if (t_cmd & 2)
                    {
                        if (t_cmd & 1)
                        {
                            //fprintf(stderr, "This is push_pushr\n");
                            push_pushr_f(SPU);
                        }
                        else
                        {
                            //fprintf(stderr, "This is pushr\n");
                            pushr_f(SPU);
                        }
                    }
                    else
                    {
                        if (t_cmd & 1)
                        {
                            //fprintf(stderr, "This is push\n");
                            StackPush(&(SPU->stk), SPU->cmds[SPU->ip+1]);
                            SPU->ip += 2;
                        }
                        else
                        {
                            fprintf(stderr, "\n\n\tWe don't know what the shit it is!!!\n\n");
                            runCond = 1;
                        }
                    }
                }
            }
        }
    }
}

SPU_t MakeNullSPU()
{
    SPU_t NullSPU;
    
    Stack_t null_stk;
    StackCtor(&null_stk, 0);
    
    Stack_t null_proc_stk;
    StackCtor(&null_proc_stk, 0);

    NullSPU.cmds      = NULL;
    NullSPU.ip        = 0;
    NullSPU.stk       = null_stk;
    NullSPU.proc_stk  = null_proc_stk;
    NullSPU.registers = (double*)calloc(nRegisters, sizeof(double));
    NullSPU.ram       = (double*)calloc(ram_volume, sizeof(double));
    NullSPU.logfile   = NULL;

    return NullSPU;
}
