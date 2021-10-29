#include <stdio.h>
#include <stdlib.h>


void usage(char *prog) {
    fprintf(stderr, "%s: Custom mv C program\n"\
                        "Usage:\t%s infile outfile\n", prog, prog);
}

int delete_check(char *name) {
    return 1;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage(argv[0]);
        return 0;
    }
    FILE *from = fopen(argv[1], "r");
    if (from == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argv[1]);
        exit(1);
    }
    FILE *to = fopen(argv[2], "w");
    if (to == NULL) {
        fclose(from);
        fprintf(stderr, "Unable to create/open file %s\n", argv[2]);
        exit(2);
    }
    const int BUFFER_LEN = 4;
    char buffer[BUFFER_LEN];
    int rc = 0;
    while (fgets(buffer, BUFFER_LEN, from) != NULL) {
        rc = fputs(buffer, to);
        if (rc == EOF) {
            perror("Error writing buffer");
            fclose(to);
            fclose(from);
            if (remove(argv[2])) {
                perror("Error deleting output file");
                exit(7);
            }
            exit(3);
        }
    }
    if (!feof(from)) {
        perror("Error while reading file: EOF not reached");
        fclose(to);
        fclose(from);
        if (remove(argv[2])) {
            perror("Error deleting output file");
            exit(7);
        }
        exit(4);
    } else if (ferror(from)) {
        perror("Error while reading file: unknown");
        fclose(to);
        fclose(from);
        if (remove(argv[2])) {
            perror("Error deleting output file");
            exit(7);
        }
        exit(5);
    }



    fclose(to);
    fclose(from);
    if (delete_check(argv[1])) {
        if (remove(argv[1])) {
            perror("Error deleting input file");
            exit(6);
        }
    }

    return 0;
}
