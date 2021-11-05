#define _GNU_SOURCE
#include <string.h>
#include <dlfcn.h>

typedef int (*remove_type)(const char* pathname);

int remove(const char* pathname) {
    if (strstr(pathname, "PROTECT") != NULL) {
        return 0;
    }

    remove_type true_remove = (remove_type)dlsym(RTLD_NEXT, "remove");
    return true_remove(pathname);
}
