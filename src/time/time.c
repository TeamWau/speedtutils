#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int main( int argc, char **argv ) {
    long starttime;
    struct timespec res;
    int ctime = clock_getres( CLOCK_MONOTONIC_COARSE, &res );
    pid_t pID;

    ctime = clock_gettime( CLOCK_MONOTONIC_COARSE, &res );
    starttime = res.tv_nsec;
    printf( "Begin execution at approx: %ldns\n", starttime );

    pID = fork();
    if(pID == 0){
        execvp(argv[1],argv+1);
    } else if(pID < 0){
        return 1;
    } else {
        int rs;
        waitpid(pID, &rs, 0);
        ctime = clock_gettime( CLOCK_MONOTONIC_COARSE, &res );
        long endtime = res.tv_nsec;

        printf( "End execution at approx: %ldns\n", endtime );

        printf( "\nTotal approx. runtime: %ldns\n", endtime - starttime );
        return 0;
    }
}
