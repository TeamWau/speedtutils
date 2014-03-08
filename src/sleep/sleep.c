#include    <stdio.h>
#include    <unistd.h>

#define PROGRAM_NAME "SLEEP"
#define AUTHORS "blackfox, fauxm"

int main( int argc, char **argv ) {
    int c, n;
    char    *s;

    n = 0;
    if(argc != 2) {
        fprintf(stderr, "usage: sleep time\n");
        return(0);
    }
    s = argv[1];
    while((c = *s++)) {
        if(c<'0' || c>'9') {
            fprintf( stderr, "%s: bad character in argument\n", argv[0] );
            return(0);
        }
        n = n*10 + c - '0';
    }
    sleep(n);
}
