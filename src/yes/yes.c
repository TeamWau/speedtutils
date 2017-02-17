#include <stdio.h>

#define PROGRAM_NAME "yes"
#define AUTHORS "fauxm"

int main(int argc, char** argv) 
{
    if (argc == 1) {
        while (1) {
            printf("y\n");
        }
    } else if (argc > 1) {
        int count;
        while (1) {
            for (count = 1; count < argc; count++) {
                if (count == argc - 1) {
                    printf("%s", argv[count]);
                } else {
                    printf("%s ", argv[count]);
                }
            }
            printf("\n");
        }
    }

    return 0;
}
