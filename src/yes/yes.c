#include <stdio.h>

#define PROGRAM_NAME "yes"
#define AUTHORS "fauxm"

//todo: add support for other strings

int main( int argc, char** argv ) {
    if( argc == 1 ) {
        while( 1 ) {
            printf( "y\n" );
        }
    }
    return 0;
}
