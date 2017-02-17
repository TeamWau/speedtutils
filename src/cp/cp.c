#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define PROGRAM_NAME "cp"
#define AUTHORS "fauxm, cxl"

int main(int argc, char** argv) 
{
    if (argc < 2) {
        printf("%s - memory mapping equivalent to `cp'\nProvides high-speed file reads\n\nError: please specify a file name!\nUsage: %s <original> <copy>\n", argv[0], argv[0]);
        return 1;
    }

    char *buf;
    struct stat s;
    int infile = open(argv[1], O_RDONLY); //explicitly define the input file as read only
    if (infile < 0) {
        perror("Error"); 
        printf("\nAbort! Abort!\n");
        return 2;
    }
    
    struct stat of;
    int ofi = open(argv[2], O_RDONLY);
    fstat(ofi, &of);
    int isdir = S_ISDIR(of.st_mode);
    close(ofi);

    FILE* outfile;
    char* fn;
    if (isdir == 0) {
        outfile = fopen(argv[2], "w");
    } else {
        //We want to make sure argv[2] has a trailing slash before trying to strcat it with argv[1]
        fn = argv[2];
        if (fn[strlen(fn) - 1] != '/') {
            fn = strcat(fn, "/");
        }
        outfile = fopen(strcat(fn, argv[1]), "w");
    }

    fstat(infile, &s); //get data about our input file, store it in the struct

    /* map the struct (which now contains our file data) to memory.
     * We make our mapping read only and private (since it won't change)
     * No offsets.
     */
    buf = mmap(0, s.st_size, PROT_READ, MAP_SHARED, infile, 0);

    if (buf != (void*) - 1) {
        fwrite_unlocked(buf, s.st_size, 1, outfile); //write everything from mapped memory to the output file
        munmap(buf, s.st_size); //free up the memory we mapped
    }

    fclose(outfile);
    close(infile);

    return 0;
}
