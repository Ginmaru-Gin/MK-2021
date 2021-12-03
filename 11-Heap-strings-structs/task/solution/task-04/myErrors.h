#pragma once

#include <errno.h>
#include <stdio.h>
#include <process.h>

#define ERR_SUCCESS                     0
#define ERR_NOT_ENOUGH_FUNDS_ON_BALANCE -1
#define ERR_NOT_ENOUGH_CASH_ON_ATM      -2
#define ERR_CLIENT_NOT_FOUND            -3
#define ERR_WRONG_PASSWORD              -4

void checkError(errno_t error);
