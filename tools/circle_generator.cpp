#include <math.h>
#include <stdio.h>

#ifndef PROJECT_SOURCE_DIR
#define PROJECT_SOURCE_DIR "."
#endif

int main()
{    
    FILE* logfile = fopen(PROJECT_SOURCE_DIR "/resources/programs/circle.txt", "w");
    double R = 0;
    printf("Enter R:\t");
    scanf("%lg", &R);
    double n = R;
    double size = 5*(R * R);
    int  array[(int)size ] = {'\0'};
    int counter = 0;
    int x_1 = 0, x_2 = 0;
    while(n >= -1 * R)
    {
        x_1 = (int)ceil(R - sqrt(pow(R,2) - pow(n, 2))) + int(2*R*counter) + 1;
        array[x_1] = 1;
        fprintf(logfile, "push 64 \npop [%d] \n", x_1); 
        
        x_2 =  (int)floor(R + sqrt(pow(R,2) - pow(n, 2))) + int(2*R*counter) - 1;
        array[x_2] = 1;
        fprintf(logfile, "push 64 \npop [%d] \n", x_2);

        fprintf(logfile, "push 10 \npop [%d] \n", int(2*R*(counter+1)));

        counter++;
        n --;
    }

    for (size_t i = 0; i < (size_t)pow(2*R +2, 2); i++)
    {
        fprintf(logfile, "push [%lu]\nprint\n", i);
    }
    fprintf(logfile, "hlt\n");

    for (int i = 0; i <= 4*R*R; i++)
    {
        if (array[i] == 1)
        {
            fprintf(stderr, "%c  ", 64);
        }
        else
        {
            fprintf(stderr, "  ");
        }
        if (i % (int)(2*R) == 0)
        {
            fprintf(stderr, "\n");
        }
    }
}
