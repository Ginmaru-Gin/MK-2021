#include "ATM.h"

#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_MENU_SIGNAL -1

#define PASSWD_BUF_LENGTH 20
#define PASSWD_BUF_SIZE (PASSWD_BUF_LENGTH + 1)

errno_t stopATM(ATMPtr atm);
ClientPtr findClient(ATMPtr atm, card_t card);
errno_t addNewClient(ATMPtr atm, card_t card, char* password, phone_t phone, money_t balance);
errno_t loadData(ATMPtr atm, char* configFileName);
errno_t saveData(ATMPtr atm);
errno_t authentication(ATMPtr atm, card_t card, char* password);
errno_t getCash(ATMPtr atm, card_t card, money_t amount);
errno_t putCash(ATMPtr atm, card_t card, money_t amount);
errno_t payForPhone(ATMPtr atm, card_t card, money_t amount);
int mainMenu(ATMPtr atm);
void newClientMenu(ATMPtr atm);
void authMenu(ATMPtr atm);
void clientSessionMenu(ATMPtr atm, ClientPtr client);

int mainMenu(ATMPtr atm) {
    system("cls");
    printf_s("MENU:\n\
1. Start session\n\
2. I'm new client\n\
0. EXIT\n");
    unsigned char action = _getch();
    switch (action) {
    case '1':
        authMenu(atm);
        break;
    case '2':
        newClientMenu(atm);
        break;
    case '0':
        return -1;
    }
    return 0;
}
void newClientMenu(ATMPtr atm) {
    system("cls");
    card_t card;
    phone_t phone;
    char password[PASSWD_BUF_SIZE];
    printf_s("Enter your card number: ");
    scanf_s("%llu", &card);
    printf_s("Enter your phone number: ");
    scanf_s("%llu", &phone);
    printf_s("Enter your password: ");
    scanf_s("%s", password, PASSWD_BUF_SIZE);
    size_t passwdSize = strlen(password) + 1;
    addNewClient(atm, card, password, phone, 0);
}

void authMenu(ATMPtr atm) {
    card_t card;
    char password[PASSWD_BUF_SIZE];

    system("cls");
    printf_s("Enter your card number: ");
    scanf_s("%llu", &card);
    printf_s("Enter your password: ");
    scanf_s("%s", password, PASSWD_BUF_SIZE);

    errno_t authErr = authentication(atm, card, password);
    switch (authErr) {
    case ERR_SUCCESS:
        clientSessionMenu(atm, findClient(atm, card));
        break;
    case ERR_WRONG_PASSWORD:
        printf_s("ERROR: WRONG PASSWORD!\n");
        system("pause");
        break;
    case ERR_CLIENT_NOT_FOUND:
        printf_s("ERROR: there isn't this card in base.\n");
        system("pause");
        return;
        break;
    }
}

void clientSessionMenu(ATMPtr atm, ClientPtr client) {
    unsigned char action;
    money_t money;
    do {
        system("cls");
        printf_s("BALANCE: %llu\n\
1. Get cash\n\
2. Put cash to card\n\
3. Pay for phone\n\
0. Exit\n", client->balance);

        action = _getch();
        switch (action) {
        case '1':
            printf_s("Enter cash amount: ");
            scanf_s("%llu", &money);
            getCash(atm, client->card, money);
            break;
        case '2':
            printf_s("Enter cash amount: ");
            scanf_s("%llu", &money);
            putCash(atm, client->card, money);
            break;
        case '3':
            printf_s("Enter transaction size: ");
            scanf_s("%llu", &money);
            payForPhone(atm, client->card, money);
            break;
        }
    } while (action != '0');
    printf_s("Goodbye!\n");
    system("pause");
}

errno_t runATM(ATMPtr atm, char* configFileName) {
    loadData(atm, configFileName);
    while (mainMenu(atm) != EXIT_MENU_SIGNAL);
    stopATM(atm);
    return ERR_SUCCESS;
}

errno_t stopATM(ATMPtr atm) {
    saveData(atm);
    return ERR_SUCCESS;
}

ClientPtr findClient(ATMPtr atm, card_t card) {
    for (size_t i = 0; i < atm->clients->size; ++i) {
        ClientPtr client = dynArrGet(atm->clients, i);
        if (client->card == card) return client;
    }
    return NULL;
}

errno_t addNewClient(ATMPtr atm, card_t card, char* password, phone_t phone, money_t balance) {
    if (findClient(atm, card) != NULL) {
        printf_s("ERROR: This card already exists in base.\n");
        system("pause");
        return ERR_SUCCESS;
    }
    Client client;
    client.card = card;
    client.phone = phone;
    client.balance = balance;
    client.password = password;
    dynArrAdd(atm->clients, &client);
    return ERR_SUCCESS;
}

#define DEFAULT_CLIENTS_ARRAY_CAPACITY 10

errno_t loadData(ATMPtr atm, char* configFileName) {
    FILE* config;

    size_t confFileNameBufSize = strlen(configFileName) + 1;
    if (!(atm->configFileName = (char*)malloc(sizeof(char) * confFileNameBufSize))) return errno;
    strcpy_s(atm->configFileName, confFileNameBufSize, configFileName);

    fopen_s(&config, configFileName, "r");
    if (errno != ERR_SUCCESS) {
        if (errno == ENOENT) {
            atm->cash = 0;
            atm->clients = newDynamicArray(DEFAULT_CLIENTS_ARRAY_CAPACITY);
            return ERR_SUCCESS;
        }
        else return errno;
    }

    size_t clientsCount;
    fscanf_s(config, "%llu %llu", &atm->cash, &clientsCount);
    if ((atm->clients = newDynamicArray(clientsCount)) == NULL) {
        fclose(config);
        return errno;
    }
    char passwordBuf[PASSWD_BUF_SIZE];
    Client client;
    client.password = passwordBuf;
    for (size_t i = 0; i < clientsCount; ++i) {
        if (fscanf_s(config, "%llu %llu %llu %s",
            &client.card, &client.balance, &client.phone, client.password, PASSWD_BUF_SIZE) != 4) {
            fclose(config);
            return errno;
        }
        addNewClient(atm, client.card, client.password, client.phone, client.balance);
    }
    fclose(config);
    return ERR_SUCCESS;
}

errno_t saveData(ATMPtr atm) {
    FILE* config;
    if (fopen_s(&config, atm->configFileName, "w")) return errno;
    fprintf_s(config, "%llu\n%llu\n", atm->cash, atm->clients->size);
    for (size_t i = 0; i < atm->clients->size; ++i) {
        ClientPtr client = dynArrGet(atm->clients, i);
        fprintf_s(config, "%llu %llu %llu %s\n", client->card, client->balance, client->phone, client->password);
    }
    fclose(config);
    return ERR_SUCCESS;
}

errno_t authentication(ATMPtr atm, card_t card, char* password) {
    ClientPtr client = findClient(atm, card);
    if (!client) return ERR_CLIENT_NOT_FOUND;
    if (strcmp(client->password, password)) return ERR_WRONG_PASSWORD;
    return ERR_SUCCESS;
}

errno_t getCash(ATMPtr atm, card_t card, money_t amount) {
    ClientPtr client = findClient(atm, card);
    if (!client) return ERR_CLIENT_NOT_FOUND;
    if (client->balance < amount) return ERR_NOT_ENOUGH_FUNDS_ON_BALANCE;
    if (atm->cash < amount) return ERR_NOT_ENOUGH_CASH_ON_ATM;
    atm->cash -= amount;
    client->balance -= amount;
    return ERR_SUCCESS;
}

errno_t putCash(ATMPtr atm, card_t card, money_t amount) {
    ClientPtr client = findClient(atm, card);
    if (!client) return ERR_CLIENT_NOT_FOUND;
    atm->cash += amount;
    client->balance += amount;
    return ERR_SUCCESS;
}

errno_t payForPhone(ATMPtr atm, card_t card, money_t amount) {
    ClientPtr client = findClient(atm, card);
    if (!client) return ERR_CLIENT_NOT_FOUND;
    if (client->balance < amount) return ERR_NOT_ENOUGH_FUNDS_ON_BALANCE;
    client->balance -= amount;
    return ERR_SUCCESS;
}
