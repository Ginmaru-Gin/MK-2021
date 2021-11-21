#pragma once

#include <errno.h>
#include <stdio.h>
#include <process.h>

#define ERR_SUCCESS             0

void checkError(errno_t error);
