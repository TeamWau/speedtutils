#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>

#define PROGRAM_NAME "touch"
#define AUTHORS "fauxm, cxl"

int main( int argc, char** argv ) {
    struct stat f;

    if(stat(argv[1], &f) < 0){
        FILE* newfile;
        newfile = fopen( argv[1], "a" );

        fwrite( NULL, 0, 0, newfile );

        fclose( newfile );

    } 
    else {
        char* filename = argv[1];
        struct utimbuf newtime;

        newtime.actime = time(NULL);
        newtime.modtime = time(NULL);

        if (utime(filename, &newtime) < 0) {
            perror(filename); 
            return 1;
        }
    }

    return 0;
}
