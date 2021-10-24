#include <stdio.h>
#include <stdlib.h>


void usage(char *prog) {
        fprintf(stderr, "%s: Print sequence to stdout\n"\
                                "Usage:\t%s N - [0, 1, … N-1]\n"\
                                "\t%s M N - [M, M+1, … N-1]\n"\
                                "\t%s M N S - [M, M+S, M+2S, … N-1]\n", prog, prog, prog, prog);
}


int main(int argc, char *argv[]) {
    long start = 0;
    long end = 0;
    long step = 1;

    switch (argc) {
        case 2: end = strtol(argv[1], NULL, 10);
                break;
        case 4: step = strtol(argv[3], NULL, 10);
        case 3: start = strtol(argv[1], NULL, 10);
                end = strtol(argv[2], NULL, 10);
                break;
        default: usage(argv[0]);
                 return 0;
    }
    long i = 0;
    for (i = start; i < end; i += step) {
        printf("%ld\n", i);
    }
    return 0;
}
