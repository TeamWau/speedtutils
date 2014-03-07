#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define PROGRAM_NAME "cat"
#define AUTHORS "fauxm, cxl"

int main( int argc, char** argv ) {

    if( argc < 2 ) {
        printf("%s - memory mapping equivalent to `cat'\nProvides high-speed file reads\n\nError: please specify a file name!\nUsage: %s <filename>\n", argv[0], argv[0] );
        return( 1 );
    }

    char *buf;
    struct stat s;
    int infile = open( argv[1], O_RDONLY ); //explicitly define the file as read only
    if ( infile < 0 ) {
        perror( "Error: " ); 
        printf( "\nAbort! Abort!\n" );
        return( 1 );
    }

    fstat( infile, &s ); //get data about our file, store it in the struct

    /* map the struct (which now contains our file data) to memory.
     * We make our mapping read only and private (since it won't change)
     * No offsets.
     */
    buf = mmap( 0, s.st_size, PROT_READ, MAP_SHARED, infile, 0 );

    if( buf != ( void* ) - 1 ) {
        fwrite_unlocked( buf, s.st_size, 1, stdout ); //write everything from mapped memory
        munmap( buf, s.st_size ); //free up the memory we mapped
    }

    return( 0 );
}
