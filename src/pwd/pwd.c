#include	<stdlib.h>
#include	<stdio.h>
#include	<unistd.h>
#include	<limits.h>
char	name[PATH_MAX+1];

main()
{
	int length;
	if (getcwd(name, PATH_MAX + 1) == (char *)0) {
		fprintf(stderr, "pwd: cannot determine current directory!\n");
		exit(2);
	}
	length = strlen(name);
	name[length] = '\n';
	write(1, name, length + 1);
	exit(0);
}
