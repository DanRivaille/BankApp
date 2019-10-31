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
static void readAccountNumber(Map *acc_numbers, typeAccount *account, typeAddressee *new_addressee);

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

void addAddressee(Map *acc_numbers, typeAccount *account)
{
    typeAddressee *new_addressee;
    new_addressee = (typeAddressee *) calloc(1, sizeof(typeAddressee));

    readAccountNumber(acc_numbers, account, new_addressee);

    printf("Ingrese el nombre: ");
    scanf("%[^\n]s", new_addressee->name);

    int favorite;
    printf("¿Desea guardarlo como favorito? (1 - SI | 2 - NO): ");
    scanf("%i", &favorite);

    while((favorite != 1) && (favorite != 2))
    {
        printf("Opcion ingresada no valida, vuelva a intentarlo: ");
        scanf("%i", &favorite);
    }

    if(favorite == 1)
        new_addressee->favorite = true;
    else
        new_addressee->favorite = false;

    insertMap(account->addressees, new_addressee->account_number, new_addressee);
}

void showAddressees(typeAccount *account)
{
    typeAddressee *addressee = (typeAddressee *) firstMap(account->addressees);

    while(addressee != NULL)
    {
        printf("Nombre: %s  |  Rut: %s ", addressee->name, addressee->rut);
        printf("|  Numero de cuenta: %s\n", addressee->account_number);

        addressee = (typeAddressee *) nextMap(account->addressees);
    }
}

void showFavAddressees(typeAccount *account)
{
    typeAddressee *addressee = (typeAddressee *) firstMap(account->addressees);

    while(addressee != NULL)
    {
        if(addressee->favorite == true)
        {
            printf("Nombre: %s  |  Rut: %s ", addressee->name, addressee->rut);
            printf("|  Numero de cuenta: %s\n", addressee->account_number);
        }

        addressee = (typeAddressee *) nextMap(account->addressees);
    }
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

/** Procedimiento que crea la carpeta de la nueva cuenta */
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

/** Procedimiento que lee el numero de cuenta del nuevo destinatario y realiza las validaciones adecuadas */
static void readAccountNumber(Map *acc_numbers, typeAccount *account, typeAddressee *new_addressee)
{
    bool successfully_added = false;
    typeAddressee *addressee_saved;

    while(successfully_added != true)
    {
        printf("Ingrese el numero de la cuenta: ");
        scanf("%s", new_addressee->account_number);
        getchar();

        if((addressee_saved = (typeAddressee *) searchMap(acc_numbers, new_addressee->account_number)) == NULL)
            printf("No se encontro una cuenta con el numero de cuenta ingresado, intente nuevamente\n");
        else
            if(searchMap(account->addressees, new_addressee->account_number) != NULL)
                printf("Ya se encuentra agregado un destinatario con el mismo numero de cuenta, intentelo nuevamente\n");
            else
                if(strcmp(account->account_number, new_addressee->account_number) == 0)
                    printf("No se puede agregar esta misma cuenta como destinatario, intentelo nuevamente\n");
                else
                    successfully_added = true;
    }

    strcpy(new_addressee->rut, addressee_saved->rut);
    new_addressee->account_type = addressee_saved->account_type;
}
