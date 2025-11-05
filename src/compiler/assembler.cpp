#include "compiler/assembler.h"
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




    for(int i = 0; i < amountOfCommands; i++)
    {
        if(err && asmIp < amountOfCommands)
        {
            cmd = cmds_indexes[asmIp++].line_start; 
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
            break;
        }

    }

    fseek(machFile, txt_sizeptr, SEEK_SET);
    fprintf(machFile, "%0*x\n", 8, nCommands);

    fclose(machFile);

    if (iter == 2)
    {
        if (err != 0)
        {
            BinWrite(cmd_array, cmdFile, nCommands);
        }
        else
        {
            free(cmd_array);
        }
        LabelDtor(labels);
    }
    else
    {
        free(cmd_array);
    }
    return err != 0;
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
    
    free(cmd_array);
}

void LabelCtor(labelArray_t* lblarr, int nlabels)
{
    const int initial_capacity = (nlabels > 0) ? nlabels : 1;
    lblarr->array = (label_t*)calloc(initial_capacity, sizeof(label_t));
    if (!lblarr->array)
    {
        lblarr->capacity = 0;
        lblarr->used_labels = 0;
        return;
    }

    lblarr->capacity    = initial_capacity;
    lblarr->used_labels = 0;
    for (int i = 0; i < initial_capacity; i++)
    {
        lblarr->array[i].label_name[0] = '\0';
        lblarr->array[i].line_number   = -1;
    }
}

void LabelDtor(labelArray_t* lblarr)
{
    free(lblarr->array);
    lblarr->array       = NULL;
    lblarr->used_labels = 0;
    lblarr->capacity    = 0;
}

void LabelDump(labelArray_t* lblarr)
{
    if (lblarr->array == NULL)
    {
        fprintf(stderr, "LabelDump: no labels allocated\n");
        return;
    }

    fprintf(stderr, "-----------------------------------------------------------------------------------------------------------------------------------------------------\n"
                    "\n//////////---LabelDump---//////////\n");
    
    for (u_int32_t i = 0; i < lblarr->capacity; i++)
    {
        fprintf(stderr, "lbl name: %s; line_number: %d\n", lblarr->array[i].label_name, lblarr->array[i].line_number);
    }
    fprintf(stderr, "number of used labels: %u\n", lblarr->used_labels);
    fprintf(stderr, "-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void MakeLabel(labelArray_t* lblarr, char* labelName, int lineNumber)
{
    if (lblarr->used_labels >= lblarr->capacity)
    {
        u_int32_t new_capacity = (lblarr->capacity == 0) ? 1 : lblarr->capacity * 2;
        label_t* new_array = (label_t*)realloc(lblarr->array, new_capacity * sizeof(label_t));
        if (!new_array)
        {
            fprintf(stderr, "Label allocation failed, label %s ignored\n", labelName);
            return;
        }
        for (u_int32_t i = lblarr->capacity; i < new_capacity; i++)
        {
            new_array[i].label_name[0] = '\0';
            new_array[i].line_number   = -1;
        }
        lblarr->array    = new_array;
        lblarr->capacity = new_capacity;
    }

    //*(strchr(labelName, ':')) = '\0';
    strncpy(lblarr->array[lblarr->used_labels].label_name, labelName, max_label_name - 1);
    lblarr->array[lblarr->used_labels].label_name[max_label_name - 1] = '\0';
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
