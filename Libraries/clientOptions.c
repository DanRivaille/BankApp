#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "TDA-List/List.h"
#include "TDA-Map/Map.h"
#include "typesData.h"
#include "fileFunctions.h"
#include "clientOptions.h"

/** Prototipos de funciones estaticas */
static void createAccNumber(Map *acc_numbers, typeAccount *account);
static void createAccFiles(typeClient *client, typeAccount *account);

void createAccount(Map *acc_numbers, typeClient *client, char account_type)
{
    typeAccount *new_account;
    new_account = (typeAccount *) calloc(1, sizeof(typeAccount));

    new_account->account_type = account_type;
    new_account->transactions_history = createList();
    new_account->addressees = createMap(stringHash, stringEqual);

    if(account_type == SAVING_ACC)                          //si la cuenta es de ahorro
    {
        createAccNumber(acc_numbers, new_account);              //se crea el numero de cuenta aleatorio
        client->saving_account = new_account;
    }
    else
    {
        strcpy(new_account->account_number, client->rut);       //sino el numero de cuenta es igual al rut del cliente
        client->rut_account = new_account;
    }

    typeAddressee *new_acc_number;                          //se un typeAddressee para guardar el nuevo numero de cuenta
    new_acc_number = (typeAddressee *) calloc(1, sizeof(typeAddressee));

    strcpy(new_acc_number->rut, client->rut);
    strcpy(new_acc_number->name, client->name);
    strcpy(new_acc_number->account_number, new_account->account_number);
    new_acc_number->account_type = account_type;
    new_acc_number->favorite = false;

    insertMap(acc_numbers, new_acc_number->account_number, new_acc_number);

    createAccFiles(client, new_account);
}

/** Procedimiento que crea un numero de cuenta aleatorio */
static void createAccNumber(Map *acc_numbers, typeAccount *account)
{
    srand(time(NULL));
    do
    {
        int i;
        for(i = 0; i < 8; i++)
        {
            account->account_number[i] = (rand() % 10) + 48;
        }
        account->account_number[i] = '\0';

    }while(searchMap(acc_numbers, account->account_number) != NULL);
}

static void createAccFiles(typeClient *client, typeAccount *account)
{
    char client_path[MAX_PATH + 1] = "Data//Users//";
    strcat(client_path, client->rut);
    strcat(client_path, "//");

    if(account->account_type == RUT_ACC)
        strcat(client_path, "rut-acc");
    else
        strcat(client_path, "saving-acc");

    mkdir(client_path, 0777);
}
