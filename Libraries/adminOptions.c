#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "typesData.h"
#include "fileFunctions.h"
#include "auxiliaryFunctions.h"
#include "adminOptions.h"

/** Prototipos de funciones estaticas */
static typeProfile *createProfile(char new_rut[]);
static void removeAccNumbers(Map *acc_numbers, typeClient *client);
static void removeClientFiles(typeClient *client);
static void removeAccFiles(char rut[], char type_account);
static void createPass(typeProfile *profile);
static typeClient *createClient(char new_rut[]);
static void createClientFiles(typeClient *new_client);

void addClient(Map *profiles)
{
    char new_rut[MAX_CARACT + 1];

    printf("Ingrese el rut del nuevo cliente: ");
    scanf("%s", new_rut);
    getchar();

    while(searchMap(profiles, new_rut) != NULL)
    {
        printf("Ya existe un cliente con el rut ingresado\n");
        printf("Intente nuevamente: ");
        scanf("%s", new_rut);
        getchar();
    }

    typeProfile *new_profile;
    new_profile = createProfile(new_rut);

    insertMap(profiles, new_profile->rut, new_profile);

    typeClient *new_client;
    new_client = createClient(new_rut);

    createClientFiles(new_client);

    printf("Su password inicial es : %s\n", new_profile->pass);

    _pause();                           //se intenta simular system("pause"); de window
}

void removeClient(Map *acc_numbers, Map *clients_profiles)
{
    char rut[MAX_CARACT + 1];
    typeClient *client;

    printf("Ingrese el rut del cliente a eliminar: ");
    scanf("%s", rut);

    while(searchMap(clients_profiles, rut) == NULL)
    {
        getchar();
        printf("No se encontro un perfil que coincida con el rut ingresado\n");
        printf("Intente nuevamente: ");
        scanf("%s", rut);
    }

    eraseKeyMap(clients_profiles, rut);

    client = loadClientInfo(rut);
    removeAccNumbers(acc_numbers, client);
    removeClientFiles(client);
}

typeClient* searchClientRut(Map *clients_profiles)
{
    char rut[MAX_CARACT + 1];

    printf("Ingrese el rut del cliente a buscar: ");
    scanf("%s", rut);

    while(searchMap(clients_profiles, rut) == NULL)
    {
        getchar();
        printf("No se encontro un perfil que coincida con el rut ingresado\n");
        printf("Intente nuevamente: ");
        scanf("%s", rut);
    }

    typeClient *client = loadClientInfo(rut);

    return client;
}

typeAddressee *searchAccNumber(Map *acc_numbers)
{
    char number[MAX_CARACT + 1];
    typeAddressee *account_owner;

    printf("Ingrese el numero de cuenta a buscar: ");
    scanf("%s", number);

    while((account_owner = (typeAddressee *) searchMap(acc_numbers, number)) == NULL)
    {
        getchar();
        printf("No se encontro una cuenta que coincida con el numero de cuenta ingresado\n");
        printf("Intente nuevamente: ");
        scanf("%s", number);
    }

    return account_owner;
}

void addNotice(typeClient *client)
{
    char client_path[MAX_PATH + 1] = "Data//Users//";
    strcat(client_path, client->rut);
    strcat(client_path, "//notices.txt");

    FILE *notices_file = fopen(client_path, "a");
    validFileOpening(notices_file);

    char new_notice[MAX_NOTICES + 1];

    printf("Ingrese el nuevo aviso:\n\n");
    scanf("%[^\n]s", new_notice);

    fprintf(notices_file, "%s\n", new_notice);
    fclose(notices_file);

    client->notices++;
    system("clear");
}

void makeDeposit(typeAccount *destination_acc, char rut[])
{
    long int amount;
    printf("Ingrese el monto a depositar: ");
    scanf("%li", &amount);

    while(amount < 0)
    {
        printf("Monto ingresado no valido, intentelo nuevamente: ");
        scanf("%li", &amount);
    }

    destination_acc->balance += amount;

    char *file_path = setAccPath(rut, destination_acc->account_type);
    strcat(file_path, "history-file.txt");

    FILE *history_file = fopen(file_path, "a");
    validFileOpening(history_file);

    Date *current_date = getCurrentDate();

    fprintf(history_file, "%li;%i,%i,%i;", amount, current_date->day, current_date->month, current_date->year);
    fprintf(history_file, "03112019;Sucursal BankApp;07092019;rut-acc;false\n");

    fclose(history_file);
    free(file_path);
}

void showClient(typeClient *client)
{
    printf("Nombre: %s\n", client->name);
    printf("Rut:    %s\n", client->rut);
    printf("Cuentas activas:\n\n");

    if(client->rut_account != NULL)
        printf("\t-Cuenta Rut\n\n");

    if(client->saving_account != NULL)
        printf("\t-Cuenta Ahorro\n\n");
}

static typeProfile *createProfile(char new_rut[])
{
    typeProfile *new_profile = (typeProfile *) calloc(1, sizeof(typeProfile));
    strcpy(new_profile->rut, new_rut);

    createPass(new_profile);

    return new_profile;
}

/** Procedimiento que elimina del mapa de cuentas, las cuentas que tenga activas el cliente.  */
static void removeAccNumbers(Map *acc_numbers, typeClient *client)
{
    char *acc_path;
    typeAccount *account;

    if(client->rut_account != NULL)                                 //si tiene la cuenta rut activa
    {
        acc_path = setAccPath(client->rut, RUT_ACC);                    //se establece la ruta de la carpeta de la cuenta
        account = (typeAccount *) calloc(1, sizeof(typeAccount));       //se le asigna memoria a la cuenta
        account->account_type = RUT_ACC;                                //se inicializa el tipo de cuenta
        loadAccInfo(account, acc_path);                                 //se carga el numero de cuenta
        eraseKeyMap(acc_numbers, account->account_number);              //se elimina esa cuenta del mapa de cuentas validas
        free(account);                                                  //se libera la memoria asignada a la cuenta
        free(acc_path);                                                 //se libera la memoria asignada a la ruta de la carpeta
    }

    if(client->saving_account != NULL)                                 //si tiene la cuenta de ahorros activa
    {
        acc_path = setAccPath(client->rut, SAVING_ACC);                 //se establece la ruta de la carpeta de la cuenta
        account = (typeAccount *) calloc(1, sizeof(typeAccount));       //se le asigna memoria a la cuenta
        account->account_type = SAVING_ACC;                             //se inicializa el tipo de cuenta
        loadAccInfo(account, acc_path);                                 //se carga el numero de cuenta
        eraseKeyMap(acc_numbers, account->account_number);              //se elimina esa cuenta del mapa de cuentas validas
        free(account);                                                  //se libera la memoria asignada a la cuenta
        free(acc_path);                                                 //se libera la memoria asignada a la ruta de la carpeta
    }
}

static void removeClientFiles(typeClient *client)
{
    char *client_path = setClientPath(client->rut);
    char file_path[MAX_PATH + 1];

    strcpy(file_path, client_path);
    strcat(file_path, "client-info.txt");
    remove(file_path);

    strcpy(file_path, client_path);
    strcat(file_path, "notices.txt");
    remove(file_path);

    if(client->rut_account != NULL)
        removeAccFiles(client->rut, RUT_ACC);

    if(client->saving_account != NULL)
        removeAccFiles(client->rut, SAVING_ACC);

    rmdir(client_path);
    free(client_path);
}

static void removeAccFiles(char rut[], char type_account)
{
    char *acc_path = setAccPath(rut, type_account);
    char file_path[MAX_PATH + 1];

    strcpy(file_path, acc_path);
    strcat(file_path, "acc-info.txt");
    remove(file_path);

    strcpy(file_path, acc_path);
    strcat(file_path, "addressees-file.txt");
    remove(file_path);

    strcpy(file_path, acc_path);
    strcat(file_path, "history-file.txt");
    remove(file_path);

    rmdir(acc_path);
    free(acc_path);
}

/** Funcion que crea una pass aleatoria en el nuevo perfil */
static void createPass(typeProfile *profile)
{
    srand(time(NULL));      //se inicializa la nueva semilla

    profile->pass[0] = (rand() % 26) + 65;      //Letra mayuscula
    profile->pass[1] = (rand() % 10) + 48;      //numero
    profile->pass[2] = (rand() % 26) + 97;      //letra minuscula
    profile->pass[3] = (rand() % 10) + 48;      //numero
    profile->pass[4] = '\0';                    //fin de cadena
}

static typeClient *createClient(char new_rut[])
{
    typeClient *new_client = (typeClient *) calloc(1, sizeof(typeClient));
    strcpy(new_client->rut, new_rut);

    printf("Ingrese el nombre del nuevo cliente: ");
    scanf("%[^\n]s", new_client->name);

    new_client->notices = 1;

    return new_client;
}

static void createClientFiles(typeClient *new_client)
{
    char client_path[MAX_PATH + 1] = "Data//Users//";
    strcat(client_path, new_client->rut);

    mkdir(client_path, 0777);                           //se crea la carpeta del nuevo cliente
    strcat(client_path, "//");

    char file_path[MAX_PATH + 1];
    FILE *new_file;

    strcpy(file_path, client_path);
    strcat(file_path, "client-info.txt");

    new_file = fopen(file_path, "w");                //se crea el archivo de la informacion del cliente
    fprintf(new_file, "%s;%s;false;false;%i\n", new_client->rut, new_client->name, new_client->notices);
    fclose(new_file);

    strcpy(file_path, client_path);
    strcat(file_path, "notices.txt");

    char new_notice[MAX_NOTICES] = "Bienvenido a BankApp!, una aplicacion bancaria experimental creada para simular ";
    strcat(new_notice, "lo mismo que haria una aplicacion bancaria cualquiera.");

    new_file = fopen(file_path, "w");               //se crea el archivo de avisos
    fprintf(new_file, "%s\n", new_notice);
    fclose(new_file);
}
