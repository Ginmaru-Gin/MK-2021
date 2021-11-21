#pragma once

#include <errno.h>
#include <stdio.h>
#include <process.h>

#define ERR_SUCCESS             0
#define ERR_WRONG_FUNC_ARGS     -1
#define ERR_WRONG_CMD_ARGS      -2

void checkError(errno_t error);
