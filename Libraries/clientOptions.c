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
#include "auxiliaryFunctions.h"
#include "clientOptions.h"

/** Prototipos de funciones estaticas */
static void createAccNumber(Map *acc_numbers, typeAccount *account);
static void createAccFiles(typeClient *client, typeAccount *account);
static void readAccountNumber(Map *acc_numbers, typeAccount *account, typeAddressee *new_addressee);
static typeAddressee *setDestination(Map *acc_numbers, typeAccount *account);
static typeAddressee *transferFavorite(typeAccount *account);
static typeAddressee *transferAddressee(typeAccount *account);
static typeAddressee *tranferAccount(Map *acc_numbers);
static void makeTransaction(typeAccount *origin_acc, typeAddressee *dest_owner, long int amount);

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

void menuTransaction(Map *acc_numbers, typeAccount *account)
{
    typeAddressee *destination_owner = setDestination(acc_numbers, account);

    long int amount;
    printf("Ingrese el monto a transferir: ");
    scanf("%li", &amount);

    while((amount < 1) && (amount > account->balance))
    {
        printf("Monto ingresado no valido, intetelo nuevamente: ");
        scanf("%li", &amount);
    }

    makeTransaction(account, destination_owner, amount);
}

static typeAddressee *setDestination(Map *acc_numbers, typeAccount *account)
{
    typeAddressee *destination_owner;
    int option;

    do
    {
        printf("Elegir cuenta destino\n\n");
        printf("1 - Destinatarios favoritos\n");
        printf("2 - Destinatarios\n");
        printf("3 - A terceros\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        switch(option)
        {
            case 1  : destination_owner = transferFavorite(account);    break;
            case 2  : destination_owner = transferAddressee(account);   break;
            case 3  : destination_owner = tranferAccount(acc_numbers);  break;
            default : printf("Opcion ingresada no valida\n");
        }
        system("clear");
    }while((option < 1) || (option > 3));

    return destination_owner;
}

void showHistory(typeAccount *account)
{
    typeTransaction *transaction;
    transaction = (typeTransaction *) firstList(account->transactions_history);

    while(transaction != NULL)
    {
        printf("Numero de cuenta: %s | Monto: %li", transaction->associated_acount->account_number, transaction->amount);
        printf(" | %i/%i/%i\n", transaction->date->day, transaction->date->month, transaction->date->year);

        transaction = (typeTransaction *) nextList(account->transactions_history);
    }
    _pause();
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

void deleteAddressee(typeAccount *account)
{
   char account_number[MAX_CARACT + 1];
   typeAddressee *addressee;

   printf("Ingrese el numero de cuenta: ");
   scanf("%s", account_number);

   while(searchMap(account->addressees, account_number) == NULL)
   {
       getchar();
       printf("No se encontro un destinatario con el numero de cuenta ingresado, intente nuevamente: ");
       scanf("%s", account_number);
   }

   addressee = (typeAddressee *) eraseKeyMap(account->addressees, account_number);
   free(addressee);
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

static typeAddressee *transferFavorite(typeAccount *account)
{
    typeAddressee *destination_owner;
    char acc_number[MAX_CARACT + 1];

    showFavAddressees(account);

    printf("Ingrese el numero de cuenta: ");
    scanf("%s", acc_number);

    while((destination_owner = (typeAddressee *) searchMap(account->addressees, acc_number)) == NULL)
    {
        getchar();
        printf("El numero de cuenta ingresado no es valido, intenten nuevamente: ");
        scanf("%s", acc_number);
    }

    return destination_owner;
}

static typeAddressee *transferAddressee(typeAccount *account)
{
    typeAddressee *destination_owner;
    char acc_number[MAX_CARACT + 1];

    showAddressees(account);

    printf("Ingrese el numero de cuenta: ");
    scanf("%s", acc_number);

    while((destination_owner = (typeAddressee *) searchMap(account->addressees, acc_number)) == NULL)
    {
        getchar();
        printf("El numero de cuenta ingresado no es valido, intenten nuevamente: ");
        scanf("%s", acc_number);
    }

    return destination_owner;
}

static typeAddressee *tranferAccount(Map *acc_numbers)
{
    typeAddressee *destination_owner;
    char acc_number[MAX_CARACT + 1];

    printf("Ingrese el numero de cuenta: ");
    scanf("%s", acc_number);

    while((destination_owner = (typeAddressee *) searchMap(acc_numbers, acc_number)) == NULL)
    {
        getchar();
        printf("El numero de cuenta ingresado no es valido, intenten nuevamente: ");
        scanf("%s", acc_number);
    }

    return destination_owner;
}

static void makeTransaction(typeAccount *origin_acc, typeAddressee *dest_owner, long int amount)
{
    char *acc_path;                                         //cadena que guardara la ruta de la carpeta de la cuenta destino
    typeAccount *dest_acc;                                  //guardara la informacion de la cuenta destino

    acc_path = setAccPath(dest_owner->rut, dest_owner->account_type); //se establece la ruta de la carpeta de la cuenta destino
    dest_acc = (typeAccount *) calloc(1, sizeof(typeAccount));        //se le asigna espacio a la cuenta destino
    dest_acc->account_type = dest_owner->account_type;                //se inicializa el tipo de cuenta de la cuenta destino
    loadAccInfo(dest_acc, acc_path);                                  //se carga la informacion de la cuenta destino

    origin_acc->balance -= amount;                          //se decrementa la cantidad ingresada en la cuenta origen
    dest_acc->balance += amount;                            //se deposita la cantidad ingresada en la cuenta destino

    char *file_path = setAccPath(dest_owner->rut, dest_acc->account_type);
    strcat(file_path, "history-file.txt");                  //se establece la ruta del archivo "history.txt" de la cuenta destino

    FILE *history_file = fopen(file_path, "a");             //se abre el archivo en modo adicion
    validFileOpening(history_file);

    Date *current_date = getCurrentDate();                  //se obtiene la fecha en el momento de la transaccion
    typeTransaction *transaction = (typeTransaction *) malloc(sizeof(typeTransaction) * 1);

    fprintf(history_file, "%li;%i,%i,%i;", amount, current_date->day, current_date->month, current_date->year);
    fprintf(history_file, "20191104;------;%s;", origin_acc->account_number);

    if(origin_acc->account_type ==  RUT_ACC)
        fprintf(history_file, "rut-acc;false\n");
    else
        fprintf(history_file, "saving-acc;false\n");

    transaction->amount = -amount;                              //se crea la transaccion que se guardara en el historial
    transaction->associated_acount = dest_owner;                //de la cuenta origen.
    transaction->date = current_date;
    pushBack(origin_acc->transactions_history, transaction);

    fclose(history_file);                                       //se cierra el archivo "history.txt" de la cuenta destino
    free(file_path);                                            //se libera la memoria de la ruta del archivo
    free(acc_path);                                             //se libera la memoria de la ruta de la memoria
    free(dest_acc);                                             //se libera la memoria de la cuenta destino
}
