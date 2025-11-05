#include"../headers/assembler.h"
//TODO вынести 100000 в const и сделать степенью двойки



bool MakeMachCode(const char* ProgramFile, const char* cmdFile, const char* logFile, int iter, labelArray_t* labels)
{      

    FILE* machFile = fopen(logFile, "w");
    if (machFile == 0)
    {
        fprintf(stderr, "We couldn't open you logFile!!!\n");
        return 0;
    }

    long temp_size;
    char* cmd_buffer = PutText(ProgramFile, &temp_size);
    int amountOfCommands = 0;
    Line* cmds_indexes = MakeIndex(cmd_buffer, &amountOfCommands, temp_size);
    int asmIp = 0;

    fprintf(machFile, "%s\n", "ROST");
    fprintf(machFile, "%d\n", ass_version);

    long int txt_sizeptr = ftell(machFile);

        double* cmd_array = (double*)calloc(100000, sizeof(double));
        int cmd_counter = 0;

    for (int i = 0; i < 2*sizeof(unsigned int); i++)
    {
        fprintf(machFile, "0");
    }
    fprintf(machFile, "\n");

    char* cmd = NULL;
    int err = 1;
    u_int32_t nCommands = 0;




fprintf(stderr, "before while\n");
    for(int i = 0; i < amountOfCommands; i++)
    {
        if(err && asmIp < amountOfCommands)
        {
            cmd = cmds_indexes[asmIp++].line_start; 
            
            fprintf(stderr, "%s\n", cmd);
            if (strcmp(cmd, "push") == 0)
            {
                cmd = cmds_indexes[asmIp++].line_start;
                err = WritePushArgs(cmd, machFile, cmd_array, &cmd_counter, &nCommands);
                continue;
            }

            if (strcmp(cmd, "pop") == 0)
            {
                cmd = cmds_indexes[asmIp++].line_start;

                err = WritePopArgs(cmd, machFile, cmd_array, &cmd_counter, &nCommands);
                if(err == -1) err = 0;
                continue;
            }
            if (strcmp(cmd, "add") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_add);

                long long temp_cmd = cmd_add;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));

                nCommands++;
                continue;
            }
            if (strcmp(cmd, "sub") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_sub);

                long long temp_cmd = cmd_sub;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));

                nCommands++;
                continue;
            }
            if (strcmp(cmd, "mul") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_mul);
                long long temp_cmd = cmd_mul;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                nCommands++;
                continue;
            }
            if (strcmp(cmd, "div") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_div);
                long long temp_cmd = cmd_div;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                nCommands++;
                continue;
            }
            if (strcmp(cmd, "out") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_out);
                long long temp_cmd = cmd_out;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                nCommands++;
                continue;
            }
            if (strcmp(cmd, "in") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_in);
                long long int temp_cmd = cmd_in;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                nCommands++;
                continue;
            }
            if (strcmp(cmd, "sqrt") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_sqrt);
                long long temp_cmd = cmd_sqrt;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                nCommands++;
                continue;
            }
            if (strcmp(cmd, "sin") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_sin);
                long long temp_cmd = cmd_sin;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                nCommands++;
                continue;
            }
            if (strcmp(cmd, "cos") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_cos);

                long long temp_cmd = cmd_cos;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));

                nCommands++;
                continue;
            }
            if (strcmp(cmd, "dump") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_dump);
                long long temp_cmd = cmd_dump;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                nCommands++;
                continue;
            }
            if (strcmp(cmd, "hlt") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_hlt);

                long long int temp_cmd = cmd_hlt;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));

                nCommands++;
                continue;
            }
            if (strcmp(cmd, "jmp") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_jmp);
                long long temp_cmd = cmd_jmp;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                cmd = cmds_indexes[asmIp++].line_start;

                if (strchr(cmd, ':'))
                {
                    cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                    fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                    cmd_counter++;
                }
                else
                {
                    cmd_array[cmd_counter] = atof(cmd);
                    cmd_counter++;
                    fprintf(machFile, "%s ", cmd);
                }

                nCommands += 2;
                continue;
            }
            if (strcmp(cmd, "ja") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_ja);
                long long temp_cmd = cmd_ja;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                cmd = cmds_indexes[asmIp++].line_start;

                if (strchr(cmd, ':'))
                {
                    cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                    fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                    cmd_counter++;
                }
                else
                {
                    cmd_array[cmd_counter] = atof(cmd);
                    cmd_counter++;
                    fprintf(machFile, "%s ", cmd);
                }

                nCommands += 2;
                continue;
            }
            if (strcmp(cmd, "jae") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_jae);
                long long temp_cmd = cmd_jae;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                cmd = cmds_indexes[asmIp++].line_start;

                if (strchr(cmd, ':'))
                {
                    cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                    fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                    cmd_counter++;
                }
                else
                {
                    cmd_array[cmd_counter] = atof(cmd);
                    cmd_counter++;
                    fprintf(machFile, "%s ", cmd);
                }

                nCommands += 2;
                continue;
            }
            if (strcmp(cmd, "jb") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_jb);
                long long temp_cmd = cmd_jb;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                cmd = cmds_indexes[asmIp++].line_start;
                if (strchr(cmd, ':'))
                {
                    cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                    fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                    cmd_counter++;
                }
                else
                {
                    cmd_array[cmd_counter] = atof(cmd);
                    cmd_counter++;
                    fprintf(machFile, "%s ", cmd);
                }

                nCommands += 2;
                continue;
            }
            if (strcmp(cmd, "jbe") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_jbe);
                long long temp_cmd = cmd_jbe;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                cmd = cmds_indexes[asmIp++].line_start;

                if (strchr(cmd, ':'))
                {
                    cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                    fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                    cmd_counter++;
                }
                else
                {
                    cmd_array[cmd_counter] = atof(cmd);
                    cmd_counter++;
                    fprintf(machFile, "%s ", cmd);
                }

                nCommands += 2;
                continue;
            }
            if (strcmp(cmd, "je") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_je);
                long long temp_cmd = cmd_je;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                cmd = cmds_indexes[asmIp++].line_start;

                if (strchr(cmd, ':'))
                {
                    cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                    fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                    cmd_counter++;
                }
                else
                {
                    cmd_array[cmd_counter] = atof(cmd);
                    cmd_counter++;
                    fprintf(machFile, "%s ", cmd);
                }

                nCommands += 2;
                continue;
            }
            if (strcmp(cmd, "jne") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_jne);
                long long temp_cmd = cmd_jne;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(double));
                cmd = cmds_indexes[asmIp++].line_start;

                if (strchr(cmd, ':'))
                {
                    cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                    fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                    cmd_counter++;
                }
                else
                {
                    cmd_array[cmd_counter] = atof(cmd);
                    cmd_counter++;
                    fprintf(machFile, "%s ", cmd);
                }

                nCommands += 2;
                continue;
            }
            if(strcmp(cmd, "call") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_call);
                long long temp_cmd = cmd_call;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                cmd = cmds_indexes[asmIp++].line_start;

                if (strchr(cmd, ':'))
                {
                    cmd_array[cmd_counter] = TakeLabel(labels, cmd);
                    fprintf(machFile, "%lg ", cmd_array[cmd_counter]);
                    cmd_counter++;
                }
                else
                {
                    cmd_array[cmd_counter] = atof(cmd);
                    cmd_counter++;
                    fprintf(machFile, "%s ", cmd);
                }

                nCommands += 2;
                continue;
            }
            if(strcmp(cmd, "ret") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_ret);
                long long temp_cmd = cmd_ret;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                nCommands++;
                continue;
            }
            if (strchr(cmd, ':'))
            {
                if(!IsLabel(labels, cmd))
                {
                    MakeLabel(labels, cmd, nCommands);
                }
                continue;
            }
            if (strcmp(cmd, "print") == 0)
            {
                if(err) err = fprintf(machFile, "%d ", cmd_print);
                long long temp_cmd = cmd_print;
                memcpy(&(cmd_array[cmd_counter++]), &temp_cmd, sizeof(long long int));
                nCommands++;
                continue;
            }
            err = 0;
        }

        fseek(machFile, txt_sizeptr, SEEK_SET);
        fprintf(machFile, "%0*x\n", 8, nCommands);

        fclose(machFile);

        fprintf(stderr, "first dump: \n");
        LabelDump(labels);
        if (iter == 2)
        {
            BinWrite(cmd_array, cmdFile, nCommands);
            LabelDtor(labels);
        }
        fprintf(stderr, "second dump: \n");
        LabelDump(labels);
        return;
        }   
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

void BinWrite(double* cmd_array, const char* BinFileName, u_int32_t nCommands)
{
    FILE* binFile = fopen(BinFileName, "wb");// assert(binFile);//TODO: обработать fopen без ассерта 
    if (binFile == NULL)
    {
        
        return;
    }
    


    fwrite(&signatura, sizeof(u_int32_t), 1, binFile); //TODO: if(fwrite == 0) goto close
    fwrite(&ass_version, sizeof(int), 1, binFile);
    fwrite(&nCommands, sizeof(u_int32_t), 1, binFile);

    /////
    //int temp = 0;
    //fwrite(&temp, sizeof(int), 1, binFile);
    /////
    fwrite(cmd_array, sizeof(double), nCommands, binFile);//TODO: обработать 
    fclose(binFile);
    
    fprintf(stderr, "\n\n\n\t\033[46mArrayDump\033[0m\n");
    for (int i = 0; i < nCommands; i++)
    {
        fprintf(stderr, "%lg  ", cmd_array[i]);
    }
    
    free(cmd_array);
}

void LabelCtor(labelArray_t* lblarr, int nlabels)
{
    lblarr->array = (label_t*)calloc(nlabels, sizeof(label_t));
    lblarr->used_labels = 0;
    for (size_t i = 0; i < nlabels; i++)
    {
        for (size_t j = 0; j < 128; j++)
        {
            lblarr->array[i].label_name[j] = '\0';
        }
        lblarr->array[i].line_number = -1;
    }
}

void LabelDtor(labelArray_t* lblarr)
{
    free(lblarr->array);
    lblarr->used_labels = -1;
}

void LabelDump(labelArray_t* lblarr)
{
    fprintf(stderr, "-----------------------------------------------------------------------------------------------------------------------------------------------------\n"
                    "\n//////////---LabelDump---//////////\n");
    
    for (int i = 0; i < amount_of_labels; i++)
    {
        fprintf(stderr, "lbl name: %s; line_number: %d\n", lblarr->array[i].label_name, lblarr->array[i].line_number);
    }
    fprintf(stderr, "number of used labels: %u\n", lblarr->used_labels);
    fprintf(stderr, "-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void MakeLabel(labelArray_t* lblarr, char* labelName, int lineNumber)
{
    //*(strchr(labelName, ':')) = '\0';
    strcpy(lblarr->array[lblarr->used_labels].label_name, labelName);
    lblarr->array[lblarr->used_labels].line_number = lineNumber;
    lblarr->used_labels++;
}

// double TakeLabel(labelArray_t* lblarr, char* labelName)
// {
//     double ret_line;
//     for (int i = 0; i < lblarr->used_labels; i++)
//     {
//         if (strcmp(labelName, lblarr->array[i].label_name) == 0)
//         {
//             return double(lblarr->array[i].line_number);
//         }
//     }
//     return -1;
// }

int    IsLabel (labelArray_t* lblarr, char* labelName)
{
    for (int i = 0; i < lblarr->used_labels; i++)
    {
        if (strcmp(labelName, lblarr->array[i].label_name) == 0)
        {
            return 1;
        }
    }
    return 0;
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

int    WritePopArgs (char* cmd, FILE* machFile, double* cmd_array, int* cmd_counter, u_int32_t *nCommands)
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



