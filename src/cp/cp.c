#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main( int argc, char** argv ) {

    if( argc < 2 ) {
        printf("%s - memory mapping equivalent to `cp'\nProvides high-speed file reads\n\nError: please specify a file name!\nUsage: %s <original> <copy>\n", argv[0], argv[0] );
        return( 1 );
    }

    char *buf;
    struct stat s;
    int infile = open( argv[1], O_RDONLY ); //explicitly define the input file as read only
    if ( infile < 0 ) {
        perror( "Error: " ); 
        printf( "\nAbort! Abort!\n" );
        return( 1 );
    }
    FILE* outfile = fopen( argv[2], "w" );

    fstat( infile, &s ); //get data about our input file, store it in the struct

    /* map the struct (which now contains our file data) to memory.
     * We make our mapping read only and private (since it won't change)
     * No offsets.
     */
    buf = mmap( 0, s.st_size, PROT_READ, MAP_PRIVATE, infile, 0 );

    if( buf != ( void* ) - 1 ) {
        fwrite_unlocked( buf, s.st_size, 1, outfile ); //write everything from mapped memory to the output file
        munmap( buf, s.st_size ); //free up the memory we mapped
    }

    return( 0 );
}
