#include "myErrors.h"

const char* errMsg[] = {
    "",
    "not enough funds on balance",
    "not enough cash on atm",
    "client isn't found",
    "wrong password"
};

void checkError(errno_t error) {
    if (error != ERR_SUCCESS) {
        if (error < 0) fprintf_s(stderr, "%s\n", errMsg[-error]);
        else perror("");
        exit(error);
    }
}