#include "compiler/commands.h"
#include "compiler/assembler.h"

static bool EmitJumpWithOperand(interest* data, int opcode)
{
    if (data == NULL || data->machFile == NULL || data->cmds_indexes == NULL)
    {
        return false;
    }

    fprintf(data->machFile, "%d ", opcode);
    long long temp_cmd = opcode;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));

    *data->cmd = data->cmds_indexes[(*data->asmIp)++].line_start;
    if (strchr(*data->cmd, ':'))
    {
        data->cmd_array[*data->cmd_counter] = TakeLabel(data->labels, *data->cmd);
        fprintf(data->machFile, "%lg ", data->cmd_array[*data->cmd_counter]);
    }
    else
    {
        data->cmd_array[*data->cmd_counter] = atof(*data->cmd);
        fprintf(data->machFile, "%s ", *data->cmd);
    }

    (*data->cmd_counter)++;
    (*data->nCommands) += 2;
    return true;
}

bool WritePush(interest* data)
{
    *(data->cmd) = (data->cmds_indexes[(*data->asmIp)++]).line_start;
    int ret_val = 0;
    ret_val = WritePushArgs(*(data->cmd), data->machFile, data->cmd_array, data->cmd_counter, data->nCommands);
    return ret_val;
}

bool WritePop(interest* data)
{
    *(data->cmd) = (data->cmds_indexes[(*data->asmIp)++]).line_start;
    int ret_val = 0;
    ret_val = WritePopArgs(*(data->cmd), data->machFile, data->cmd_array, data->cmd_counter, data->nCommands);
    return ret_val;
}

bool WriteAdd(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_add);

    long long temp_cmd = cmd_add;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));

    (*data->nCommands)++;
    return true;
}

bool WriteSub(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_sub);
    long long temp_cmd = cmd_sub;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteMul(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_mul);
    long long temp_cmd = cmd_mul;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteDiv(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_div);
    long long temp_cmd = cmd_div;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteOut(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_out);
    long long temp_cmd = cmd_out;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteIn(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_in);
    long long int temp_cmd = cmd_in;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteSqrt(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_sqrt);
    long long temp_cmd = cmd_sqrt;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteSin(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_sin);
    long long temp_cmd = cmd_sin;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteCos  (interest* data)
{
    fprintf(data->machFile, "%d ", cmd_cos);
    long long temp_cmd = cmd_cos;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteDump (interest* data)
{
    fprintf(data->machFile, "%d ", cmd_dump);
    long long temp_cmd = cmd_dump;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteHult (interest* data)
{
    fprintf(data->machFile, "%d ", cmd_hlt);
    long long temp_cmd = cmd_hlt;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteJump (interest* data)
{
    return EmitJumpWithOperand(data, cmd_jmp);
}

bool WriteJa (interest* data)
{
    return EmitJumpWithOperand(data, cmd_ja);
}

bool WriteJae  (interest* data)
{
    return EmitJumpWithOperand(data, cmd_jae);
}

bool WriteJb(interest* data)
{
    return EmitJumpWithOperand(data, cmd_jb);
}

bool WriteJbe(interest* data)
{
    return EmitJumpWithOperand(data, cmd_jbe);
}

bool WriteJe(interest* data)
{
    return EmitJumpWithOperand(data, cmd_je);
}

bool WriteJne(interest* data)
{
    return EmitJumpWithOperand(data, cmd_jne);
}

bool WriteCall(interest* data)
{
    return EmitJumpWithOperand(data, cmd_call);
}

bool WriteRet(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_ret);
    long long temp_cmd = cmd_ret;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}

bool WriteLabel(interest* data)
{
    if (data == NULL || data->labels == NULL || data->cmds_indexes == NULL)
    {
        return false;
    }
    *data->cmd = data->cmds_indexes[(*data->asmIp)++].line_start;
    MakeLabel(data->labels, *data->cmd, (int)(*data->nCommands));
    return true;
}

bool WritePrint(interest* data)
{
    fprintf(data->machFile, "%d ", cmd_print);
    long long temp_cmd = cmd_print;
    memcpy(&(data->cmd_array[(*data->cmd_counter)++]), &temp_cmd, sizeof(long long int));
    (*data->nCommands)++;
    return true;
}



int FillReg(char* cmd)
{
    if(strchr(cmd, 'x'))
    {
        if (strchr(cmd, 'a')) return ax;
        if (strchr(cmd, 'b')) return bx;
        if (strchr(cmd, 'c')) return cx;
        if (strchr(cmd, 'd')) return dx;
        if (strchr(cmd, 'e')) return ex;
        if (strchr(cmd, 'f')) return fx;
        if (strchr(cmd, 'g')) return gx;
        if (strchr(cmd, 'h')) return hx;
        
        return -1;
    }
    else
    {
        return -1;
    }
}

int WritePushArgs(char* cmd, FILE* machFile, double* cmd_array, int* cmd_counter, u_int32_t *nCommands)
{
    double    PushArg = 0;
    u_int64_t PushCmd = 0;
    if (strchr(cmd, '['))
    {
        *(strchr(cmd, '[')) = '\0';
        cmd = cmd + 1;
        if(strchr(cmd, ']'))
        {
            *(strchr(cmd, ']')) = '\0';
            PushCmd += 4;
            if (strchr(cmd, '+'))
            {
                char* plus_ptr = strchr(cmd, '+');
                *plus_ptr = '\0';

                PushCmd += 3;

                fprintf(machFile, "%lu ", PushCmd);
                memcpy(&(cmd_array[(*cmd_counter)++]), &PushCmd, sizeof(long long int));

                *plus_ptr = '\0';
                int reg = -1;
                reg = FillReg(cmd);
                if (reg != -1)
                {
                    fprintf(machFile, "%d ", reg);
                    cmd_array[(*cmd_counter)++] = reg;
                }
                else
                {
                    fprintf(machFile, "%s ", cmd);
                    cmd_array[(*cmd_counter)++] = atof(cmd);
                }

                reg = FillReg(plus_ptr + 1);
                if (reg != -1)
                {
                    fprintf(stderr, "WRONG SYNTAX!!!\n");
                }
                else
                {
                    fprintf(machFile, "%s ", plus_ptr + 1);
                    cmd_array[(*cmd_counter)++] = atof(plus_ptr + 1);
                }

                (*nCommands) += 3; 
            }
            else
            {
                PushCmd += 1;
                int reg = -1;
                reg = FillReg(cmd);
                if (reg != -1)
                {
                    //fprintf(stderr, "not null register!!!\n");
                    //fprintf(stderr, "register: %d ", reg);
                    
                    PushCmd += 1;
                    fprintf(machFile, "%lu ", PushCmd);
                    memcpy(&(cmd_array[(*cmd_counter)++]), &PushCmd, sizeof(long long int));
                    fprintf(machFile, "%d ", reg);

                    cmd_array[*cmd_counter] = (double)reg;
                    (*cmd_counter)++;

                    (*nCommands) += 2;
                }
                else
                {
                    fprintf(machFile, "%lu ", PushCmd);
                    memcpy(&(cmd_array[(*cmd_counter)++]), &PushCmd, sizeof(long long int));

                    fprintf(machFile, "%s ", cmd);
                    cmd_array[*cmd_counter] = atof(cmd);
                    (*cmd_counter)++;

                    (*nCommands) += 2;
                }
            }
            
        }
        else
        {
            fprintf(stderr, "\nWRONG SYNTAX\n");
            return 0;
        }
        
    }
    else
    {
        if (strchr(cmd, '+'))
        {
            char* plus_ptr = strchr(cmd, '+');
            *plus_ptr = '\0';
            
            PushCmd += 3;

            fprintf(machFile, "%d ", cmd_push_pushr);
            memcpy(&(cmd_array[(*cmd_counter)++]), &PushCmd, sizeof(long long int));
            
            int reg = -1;
            reg = FillReg(cmd);
            if (reg != -1)
            {
                fprintf(machFile, "%d ", reg);
                cmd_array[(*cmd_counter)++] = reg;
            }
            else
            {
                fprintf(machFile, "%s ", cmd);
                cmd_array[(*cmd_counter)++] = atof(cmd);
            }

            reg = FillReg(plus_ptr + 1);
            if (reg != -1)
            {
                fprintf(stderr, "WRONG SYNTAX!!!\n");
                return 0;
            }
            else
            {
                fprintf(machFile, "%s ", plus_ptr + 1);
                cmd_array[(*cmd_counter)++] = atof(plus_ptr + 1);
            }

            (*nCommands) += 3;
        }
        else
        {
            int reg = -1;
            reg = FillReg(cmd);
            if (reg != -1)
            {
                PushCmd += 2;
                fprintf(machFile, "%lu ", PushCmd);
                memcpy(&(cmd_array[(*cmd_counter)++]), &PushCmd, sizeof(long long int));
                fprintf(machFile, "%d ", reg);
                (u_int64_t)reg;
                cmd_array[*cmd_counter] = reg;
                (*cmd_counter)++;
                (*nCommands) += 2;
            }
            else
            {
                PushCmd += 1;
                fprintf(machFile, "%lu ", PushCmd);
                memcpy(&(cmd_array[(*cmd_counter)++]), &PushCmd, sizeof(long long int));
                fprintf(machFile, "%s ", cmd);
                cmd_array[*cmd_counter] = atof(cmd);
                (*cmd_counter)++;

                (*nCommands) += 2;
            }
        }
    }
    return 1;
}

int WritePopArgs (char* cmd, FILE* machFile, double* cmd_array, int* cmd_counter, u_int32_t *nCommands)
{
    double popArg = 999;
    u_int64_t popCmd = 8;

    if(strchr(cmd, '['))
    {
        *(strchr(cmd, '[')) = '\0';
        cmd += 1;
        if (strchr(cmd, ']'))
        {
            popCmd += 4;
            *strchr(cmd, ']') = '\0';

            if (strchr(cmd, '+'))
            {
                char* plus_ptr = strchr(cmd, '+');
                *plus_ptr = '\0';
                plus_ptr += 1;
                
                (*nCommands) += 3;

                popArg = FillReg(cmd);
                if (popArg > -1)
                {
                    popCmd += 1;

                    fprintf(machFile, "%lg %lu ", popArg, popCmd);
                    memcpy(&(cmd_array[(*cmd_counter)++]), &popCmd, sizeof(u_int64_t));
                    memcpy(&(cmd_array[(*cmd_counter)++]), &popArg, sizeof(  int64_t));

                }
                else
                {
                    popArg = atof(cmd);
                    popCmd += 3;

                    fprintf(machFile, "%lg %lu ", popArg, popCmd);
                    memcpy(&(cmd_array[(*cmd_counter)++]), &popCmd, sizeof(u_int64_t));
                    memcpy(&(cmd_array[(*cmd_counter)++]), &popArg, sizeof(  int64_t));
                }

                popArg = FillReg(plus_ptr);
                if (popArg > -1)
                {
                    popCmd = -1;
                    popArg = -1;
                    return -1;

                }
                else
                {
                    popArg = atof(plus_ptr);
                    fprintf(machFile, "%lg %lu ", popArg, popCmd);
                    memcpy(&(cmd_array[(*cmd_counter)++]), &popArg, sizeof(  int64_t));
                    return 1;
                }
                
            }
            else
            {
                popArg = FillReg(cmd);
                if (popArg > -1)
                {
                    popCmd +=2;

                    fprintf(machFile, "%lu %lg ", popCmd, popArg);
                }
                else 
                {
                    popArg = atof(cmd);

                    fprintf(machFile, "%lu %lg ", popCmd, popArg);
                }

                (*nCommands) +=2;
            }
        }
        else
        {
            fprintf(stderr, "WRONG SYNTAX");
            popArg = -1;
            popCmd = -1;

            return -1;
        }
    }
    else
    {
        popArg = FillReg(cmd);
        if (popArg != -1)
        {
            fprintf(machFile, "%lu %lg ", popCmd, popArg);
            (*nCommands) += 2;
        }
        else
        {
            fprintf(stderr, "UNDEFINED COMMAND!!!\n");
            popCmd = -1;
            popArg = -1;

            return -1;
        }
        
    }
    memcpy(&(cmd_array[(*cmd_counter)++]), &popCmd, sizeof(u_int64_t));
    memcpy(&(cmd_array[(*cmd_counter)++]), &popArg, sizeof(  int64_t));

    return 1;
}

double TakeLabel(labelArray_t* lblarr, char* labelName)
{
    double ret_line;
    for (int i = 0; i < lblarr->used_labels; i++)
    {
        if (strcmp(labelName, lblarr->array[i].label_name) == 0)
        {
            return double(lblarr->array[i].line_number);
        }
    }
    return -1;
}
