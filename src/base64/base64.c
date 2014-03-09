#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define PROGRAM_NAME "base64"
#define AUTHORS "cxl"

/*
TODO: Handle input from stdin
*/

const static int mod_tl[] = {0, 2, 1};
const static char enc_tl[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                              'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                              'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                              'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                              'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                              'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                              'w', 'x', 'y', 'z', '0', '1', '2', '3',
                              '4', '5', '6', '7', '8', '9', '+', '/'
                             };
const static unsigned char dec_tl[]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 62, 0, 0, 0, 63, 52, 53,
                                     54, 55, 56, 57, 58, 59, 60, 61, 0, 0,
                                     0, 0, 0, 0, 0, 0, 1, 2, 3, 4,
                                     5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                     15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
                                     25, 0, 0, 0, 0, 0, 0, 26, 27, 28,
                                     29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
                                     39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
                                     49, 50, 51, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0,
                                    };

char* b64_enc(const unsigned char *data, size_t inlength, size_t *outlength) {
    *outlength = (((inlength-1)/3)*4)+4;
    char *edata = (char *)malloc(sizeof(outlength));
    if (edata==NULL){ return NULL;} //Problem (we had one)
    int i, j;
    for (i=0, j=0;i<inlength;) {
        uint32_t oct_a = i < inlength ? (unsigned char)data[i++] : 0;
        uint32_t oct_b = i < inlength ? (unsigned char)data[i++] : 0;
        uint32_t oct_c = i < inlength ? (unsigned char)data[i++] : 0;
        uint32_t trip = (oct_a << 0x10) + (oct_b << 0x08) + oct_c;

        edata[j++] = enc_tl[(trip >> 3 * 6) & 0x3F]; edata[j++] = enc_tl[(trip >> 2 * 6) & 0x3F];
        edata[j++] = enc_tl[(trip >> 1 * 6) & 0x3F]; edata[j++] = enc_tl[(trip >> 0 * 6) & 0x3F];
    }

    for (i=0; i<mod_tl[inlength % 3]; i++){
        edata[*outlength - 1 - i] = '=';
    }

    return edata;
}


unsigned char* b64_dec(const char *data, size_t inlength, size_t *outlength) {
    unsigned char *ddata ;
    int posO=0;
    int padding = 0 ;

    if( inlength < 2 ) {
        printf( "Invalid base 64 string" ) ;
        *outlength=0; return 0;
    }

    if(data[inlength-1]=='=') ++padding; if(data[inlength-2]=='=') ++padding ;

    *outlength = (3*(inlength/4))-padding;
    ddata = (unsigned char*)malloc(sizeof(outlength)) ;

    int i;
    for(i=0; i<=(inlength-4-padding); i+=4) {
        int a=dec_tl[data[i]];   int b=dec_tl[data[i+1]];
        int c=dec_tl[data[i+2]]; int d=dec_tl[data[i+3]];

        ddata[posO++] = (a<<2) | (b>>4); ddata[posO++] = (b<<4) | (c>>2);
        ddata[posO++] = (c<<6) | (d);
    }

    if( padding==1 ) {
        int a=dec_tl[data[i]]; int b=dec_tl[data[i+1]];
        int c=dec_tl[data[i+2]];

        ddata[posO++] = (a<<2) | (b>>4) ; ddata[posO++] = (b<<4) | (c>>2) ;
    }
    else if (padding==2) {
        int a=dec_tl[data[i]]; int b=dec_tl[data[i+1]];
        ddata[posO++] = (a<<2) | (b>>4) ;
    }

    return ddata;
}


int main( int argc, char** argv ) {

    char *buf;
    struct stat s;
    int encoding = 1;
    int opt, infile;


    if( argc < 2 ) {
        printf("%s - equivalent to `base64'\nEncodes and decodes files\n\nError: please specify a file name!\nUsage: \nEncoding: %s <filename>\nDecoding: %s -d <filename>\n", argv[0], argv[0], argv[0] );
        return 1;
    }

    while ((opt = getopt (argc, argv, "d:")) != -1)
        switch (opt) {
        case 'd':
            encoding = 0;
            break;
        default:
            abort();
        }

    if(encoding){
        infile = open( argv[1], O_RDONLY );
    } else {
        infile = open( argv[2], O_RDONLY );
    }

    if ( infile < 0 ) {
        perror( "Error" );
        printf( "\nAbort! Abort!\n" );
        return 2;
    }

    fstat( infile, &s );

    buf = mmap( 0, s.st_size, PROT_READ, MAP_SHARED, infile, 0 );

    if( buf != ( void* ) - 1 ) {
        size_t s_out;
        if(encoding){
            char *output;
            output = b64_enc( buf, s.st_size, &s_out );
            printf("%s \n", output);
        } else {
            unsigned char *output;
            output = b64_dec( buf, s.st_size, &s_out );
            printf("%s", output);
        }
        munmap( buf, s.st_size );
    }

    return 0;
}
