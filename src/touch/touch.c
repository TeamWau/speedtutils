#include <stdio.h>

int main( int argc, char** argv ) {

    FILE* filename;

    filename = fopen( argv[1], "a" );

    int *nothing[1] = { NULL };

    fwrite( NULL, 0, 0, filename );

    fclose( filename );
}
