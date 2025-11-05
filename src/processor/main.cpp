#include "processor/processor.h"

#ifndef PROJECT_SOURCE_DIR
#define PROJECT_SOURCE_DIR "."
#endif

static const char kDefaultProgram[] = PROJECT_SOURCE_DIR "/resources/programs/new_program.bin";

int main(int argc, char* argv[])
{
    const char* program_path = (argc > 1) ? argv[1] : kDefaultProgram;

    SPU_t SPU = MakeNullSPU();
    if (!MakeBinSPU(program_path, &SPU))
    {
        fprintf(stderr, "Failed to load program: %s\n", program_path);
        return 1;
    }
    Run(&SPU);
    return 0;
}
