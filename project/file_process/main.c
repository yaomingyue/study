#include "main.h"
#include "mycopy.h"
#include "mmap_cp.h"
#include "process.h"
#include "process_cp.h"
#include "pipeline.h"

int main(int argc, const char *argv[])
{
    //mycopy(argv[1], argv[2]);
    //mmap_cp(argv[1], argv[2]);
    process();
    //process_cp(argv[1], argv[2], 2);
    //pipeline();
    return 0;
}

