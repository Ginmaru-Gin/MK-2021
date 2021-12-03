#pragma once

#include <stddef.h>
#include <stdio.h>

#include "Client.h"
#include "myErrors.h"
#include "dynArr.h"


typedef struct {
    DynamicArrayPtr clients;
    money_t cash;
    char* configFileName;
} ATM;

typedef ATM* ATMPtr;

errno_t runATM(ATMPtr atm, char* configFileName);
