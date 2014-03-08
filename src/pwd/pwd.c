#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#define PROGRAM_NAME "PWD"
#define AUTHORS "blackfox, fauxm"

int main( int argc, char **argv ) {

    char pwd[PATH_MAX];

	if ( getcwd( pwd, PATH_MAX ) == NULL ) {
		fprintf( stderr, "%s: cannot determine current directory!\n", argv[0] );
		return 2;
	}

    printf( "%s\n", pwd );

	return 0;
}
