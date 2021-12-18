#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "rhash.h"
#include <errno.h>

#ifdef READLINE
#include <readline/readline.h>
#endif

int extract(char *line, char **token_1, char **token_2) {
    *token_1 = strtok(line, " ");
    if (*token_1) {
        *token_2 = strtok(NULL, " ");
        if (*token_2) {
            return 0;
        } else {
            fprintf(stderr, "Invalid string - 1 arg\n");
            return 1;
        }
    } else {
        fprintf(stderr, "Invalid string - 0 arg\n");
        return 1;
    }
}

int test_op(char *op, int *mode, int *encoding) {
    int len = strlen(op);
    if (len && isalpha(op[0])) {
        *encoding = isupper(op[0]) ? RHPR_HEX : RHPR_BASE64;
    } else {
        fprintf(stderr, "Invalid hash name\n");
        return 1;
    }
    for (int i = 0; i < len; ++i) {
        char tmp = op[i];
        if isalnum(tmp) {
            op[i] = isalpha(tmp) ? tolower(tmp) : tmp;
        } else {
            fprintf(stderr, "Invalid hash name\n");
            return 1;
        }
    }
    //printf("%s\n", op);
    if (!strcmp(op, "md5")) {
        *mode = RHASH_MD5;
    } else if (!strcmp(op, "sha1")) {
        *mode = RHASH_SHA1;
    } else if (!strcmp(op, "tth")) {
        *mode = RHASH_TTH;
    } else {
        fprintf(stderr, "Invalid hash name\n");
        return 1;
    }
    return 0;
}

int ww(char **line) {
#ifdef READLINE
    *line = readline("");
    return *line != NULL;
#endif
    size_t len = 4;
    int read;
    if ((read = getline(line, &len, stdin)) != -1 && !feof(stdin)) {
        (*line)[read - 1] = 0;
        return 1;
    } 
    return 0;
}

int main(int argc, char* argv[]) {
    rhash_library_init();
    //char *heh = readline("");
    //printf("%d", RHASH_SHA1);

    char *line = NULL;
    char *op, *data;

    while (ww(&line)) {
        if (!extract(line, &op, &data)) {
            // do stuff
            int mode, encoding;
            if (!test_op(op, &mode, &encoding)) {
                // do stuff
                unsigned char digest[64];
                char output[130];
                int res;
                if (data[0] == '"') {
                    // data[1:]
                    res = rhash_msg(mode, data + 1, strlen(data) - 1, digest);
                } else {
                    res = rhash_file(mode, data, digest);
                }
                if(res < 0) {
                    fprintf(stderr, "LibRHash error: %s: %s\n", data, strerror(errno));
                    continue;
                }
                rhash_print_bytes(output, digest, rhash_get_digest_size(mode),
                   //(encoding | RHPR_UPPERCASE));
		   encoding);
                printf("%s\n", output);
            }
        }
    }

    free(line);
    return 0;
}


