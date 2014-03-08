#include    <stdio.h>
#include    <unistd.h>

#define PROGRAM_NAME "SLEEP"
#define AUTHORS "blackfox, fauxm"

int main( int argc, char **argv ) {
    int time;

    if( argc != 2 ) {
        fprintf(stderr, "usage: %s time\n", argv[0]);
        return 1;
    }

//todo: make this catch *all* letters in argv[1], currently it only fails if there's one at the start.
    if( ( time = atoi( argv[1] ) ) != NULL ) { 
        sleep( time );
        return 0;
    }
    else {
        fprintf( stderr, "%s: error: invalid character in argument\n", argv[0] );
        return 1;
    }
}
