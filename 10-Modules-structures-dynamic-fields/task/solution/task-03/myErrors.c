#include "myErrors.h"

const char* errMsg[] = {
    ""
};

void checkError(errno_t error) {
    if (error != ERR_SUCCESS) {
        if (error < 0) fprintf_s(stderr, "%s\n", errMsg[-error]);
        else perror("");
        exit(error);
    }
}
