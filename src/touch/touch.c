#include <stdio.h>

int main( int argc, char** argv ) {

    //TODO: Make it so that it actually updates the file instead of merely creating
    //
    FILE* filename;

    filename = fopen( argv[1], "a" );

    fwrite( NULL, 0, 0, filename );

    fclose( filename );
}
