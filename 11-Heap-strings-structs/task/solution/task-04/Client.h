#pragma once

typedef unsigned long long phone_t;
typedef unsigned long long card_t;
typedef unsigned long long money_t;

typedef struct
 {
    char* password;
    card_t card;
    phone_t phone;
    money_t balance;
} Client;

typedef Client* ClientPtr;
