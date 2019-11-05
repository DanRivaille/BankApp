#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "typesData.h"
#include "TDA-List/List.h"
#include "TDA-Map/Map.h"
#include "fileFunctions.h"

/** Prototipos de funciones estaticas */
static typeTransaction *createTransaction(char line[]);
static typeAddressee *createAddresse(char line[]);
static void loadAccHistory(typeAccount *account, char acc_path[]);
static void loadAccAddressees(typeAccount *account, char acc_path[]);
static void saveAccHistory(typeAccount *account, char acc_path[]);
static void saveAccAddressees(typeAccount *account, char acc_path[]);

Map *loadProfiles(char file_name[])
{
    char file_path[MAX_PATH + 1] = "Data//Profiles//";          //ruta del archivo a abrir
    strcat(file_path, file_name);

    FILE *profiles_file = fopen(file_path, "r");                //se abre el archivo
    validFileOpening(profiles_file);                            //se valida la apertura del archivo

    Map *profiles = createMap(stringHash, stringEqual);         //se crea el mapa de los perfiles

    typeProfile *new_profile;
    char line[MAX_NOTICES + 1];

    while(fscanf(profiles_file, "%s", line) != EOF)             //se lee linea por linea el archivo
    {
        new_profile = (typeProfile *) calloc(1, sizeof(typeProfile));

        strcpy(new_profile->rut, strtok(line, ";"));            //se separa el rut y se guarda en el nuevo perfil
        strcpy(new_profile->pass, strtok(NULL, "\n"));          //se separa la pass y se guarda en el nuevo perfil

        insertMap(profiles, new_profile->rut, new_profile);     //se inserta en el mapa
    }
    fclose(profiles_file);                                      //se cierra el archivo

    return profiles;
}

void saveProfiles(Map *profiles, char file_name[])
{
    char file_path[MAX_PATH + 1] = "Data//Profiles//";
    strcat(file_path, file_name);

    FILE *profiles_file = fopen(file_path, "w");
    validFileOpening(profiles_file);

    typeProfile *current_profile;
    current_profile = (typeProfile *) firstMap(profiles);

    while(current_profile != NULL)
    {
        fprintf(profiles_file, "%s;%s\n", current_profile->rut, current_profile->pass);

        current_profile = (typeProfile *) nextMap(profiles);
    }
    fclose(profiles_file);
}

typeClient *loadClientInfo(char rut[])
{
    char *client_path = setClientPath(rut);
    strcat(client_path, "client-info.txt");

    FILE *client_file = fopen(client_path, "r");
    validFileOpening(client_file);

    typeClient *client;
    client = (typeClient *) calloc(1, sizeof(typeClient));

    char line[MAX_NOTICES + 1];
    fscanf(client_file, "%[^\n]s", line);

    strcpy(client->rut, strtok(line, ";"));
    strcpy(client->name, strtok(NULL, ";"));

    if(strcmp(strtok(NULL, ";"), "true") == 0)
        client->rut_account = (typeAccount *) calloc(1, sizeof(typeAccount));

    if(strcmp(strtok(NULL, ";"), "true") == 0)
        client->saving_account = (typeAccount *) calloc(1, sizeof(typeAccount));

    client->notices = atoi(strtok(NULL, "\n"));

    fclose(client_file);
    free(client_path);

    return client;
}

void saveClientInfo(typeClient *client)
{
    char *file_path = setClientPath(client->rut);
    strcat(file_path, "client-info.txt");

    FILE *client_file = fopen(file_path, "w");
    validFileOpening(client_file);

    fprintf(client_file, "%s;%s;", client->rut, client->name);

    if(client->rut_account != NULL)
        fprintf(client_file, "true;");
    else
        fprintf(client_file, "false;");

    if(client->saving_account != NULL)
        fprintf(client_file, "true;");
    else
        fprintf(client_file, "false;");

    fprintf(client_file, "%i\n", client->notices);
    fclose(client_file);
    free(file_path);
}

Map *loadAccNumbers(void)
{
    Map *acc_numbers = createMap(stringHash, stringEqual);

    char file_path[MAX_PATH + 1] = "Data//Users//acc-numbs.txt";

    FILE *acc_file = fopen(file_path, "r");
    validFileOpening(acc_file);

    char line[MAX_NOTICES + 1];

    while(fscanf(acc_file, "%[^\n]s", line) != EOF)
    {
        fgetc(acc_file);        //se saca el \n del buffer

        typeAddressee *new_addressee;
        new_addressee = createAddresse(line);

        insertMap(acc_numbers, new_addressee->account_number, new_addressee);
    }

    fclose(acc_file);
    return acc_numbers;
}

void saveAccNumbers(Map *acc_numbers)
{
    char file_path[MAX_PATH + 1] = "Data//Users//acc-numbs.txt";

    FILE *acc_file = fopen(file_path, "w");
    validFileOpening(acc_file);

    typeAddressee *addressee = (typeAddressee *) firstMap(acc_numbers);

    while(addressee != NULL)
    {
        fprintf(acc_file, "%s;%s;%s;", addressee->rut, addressee->name, addressee->account_number);

        if(addressee->account_type == RUT_ACC)
            fprintf(acc_file, "rut-acc;false\n");
        else
            fprintf(acc_file, "saving-acc;false\n");

        addressee = (typeAddressee *) nextMap(acc_numbers);
    }

    fclose(acc_file);
}

void loadAccount(typeAccount *account, char rut[], char account_type)
{
    char *acc_path = setAccPath(rut, account_type);
    account->account_type = account_type;

    loadAccInfo(account, acc_path);
    loadAccHistory(account, acc_path);
    loadAccAddressees(account, acc_path);

    free(acc_path);
}

void saveAccount(typeAccount *account, char rut[])
{
    char *acc_path = setAccPath(rut, account->account_type);

    saveAccInfo(account, acc_path);
    saveAccAddressees(account, acc_path);
    saveAccHistory(account, acc_path);

    free(acc_path);
}

void loadNotices(typeClient *client, List *list_notices)
{
    char *file_path = setClientPath(client->rut);
    strcat(file_path, "notices.txt");

    FILE *notices_file = fopen(file_path, "r");
    validFileOpening(notices_file);

    typeNotice *new_notice;
    char line[MAX_NOTICES + 1];

    while(fscanf(notices_file, "%[^\n]s", line) != EOF)
    {
        fgetc(notices_file);                            //se saca el \n del buffer

        new_notice = (typeNotice *) malloc(sizeof(typeNotice) * 1);

        strcpy(new_notice->notice, line);
        new_notice->readed = false;

        pushBack(list_notices, new_notice);
    }

    fclose(notices_file);
    free(file_path);
}

void saveNotices(typeClient *client, List *list_notices)
{
    char *file_path = setClientPath(client->rut);
    strcat(file_path, "notices.txt");

    FILE *notices_file = fopen(file_path, "w");
    validFileOpening(notices_file);

    typeNotice *notice = (typeNotice *) firstList(list_notices);

    while(notice != NULL)
    {
        if(notice->readed == false)                         //si el aviso no ha sido leido se guarda
            fprintf(notices_file, "%s\n", notice->notice);

        notice = (typeNotice *) nextList(list_notices);
    }

    fclose(notices_file);
    free(file_path);
}

void validFileOpening(FILE *file)
{
    if(file == NULL)
    {
        printf("\n**ERROR, NO SE PUDO ABRIR EL ARCHIVO**\n");
        exit(EXIT_FAILURE);
    }
}

static typeTransaction *createTransaction(char line[])
{
    typeTransaction *new_transaction;
    new_transaction = (typeTransaction *) calloc(1, sizeof(typeTransaction));
    new_transaction->date = (Date *) calloc(1, sizeof(Date));

    new_transaction->amount = atoi(strtok(line, ";"));
    new_transaction->date->day = atoi(strtok(NULL, ","));
    new_transaction->date->month = atoi(strtok(NULL, ","));
    new_transaction->date->year = atoi(strtok(NULL, ";"));

    new_transaction->associated_acount = createAddresse(strtok(NULL, "\n"));

    return new_transaction;
}

static typeAddressee *createAddresse(char line[])
{
    typeAddressee *new_addressee;
    new_addressee = (typeAddressee *) calloc(1, sizeof(typeAddressee));

    strcpy(new_addressee->rut, strtok(line, ";"));
    strcpy(new_addressee->name, strtok(NULL, ";"));
    strcpy(new_addressee->account_number, strtok(NULL, ";"));

    if(strcmp(strtok(NULL, ";"), "rut-acc") == 0)
        new_addressee->account_type = RUT_ACC;
    else
        new_addressee->account_type = SAVING_ACC;

    if(strcmp(strtok(NULL, "\n"), "true") == 0)
        new_addressee->favorite = true;
    else
        new_addressee->favorite = false;

    return new_addressee;
}

void loadAccInfo(typeAccount *account, char acc_path[])
{
    char file_path[MAX_PATH + 1];
    strcpy(file_path, acc_path);
    strcat(file_path, "acc-info.txt");

    FILE *info_file = fopen(file_path, "r");
    validFileOpening(info_file);

    char line[MAX_NOTICES + 1];
    fscanf(info_file, "%[^\n]s", line);

    account->balance = atoi(strtok(line, ";"));
    strcpy(account->account_number, strtok(NULL, ";"));

    fclose(info_file);
}

static void loadAccHistory(typeAccount *account, char acc_path[])
{
    char file_path[MAX_PATH + 1];
    strcpy(file_path, acc_path);
    strcat(file_path, "history-file.txt");

    FILE *history_file = fopen(file_path, "r");
    validFileOpening(history_file);

    account->transactions_history = createList();

    char line[MAX_NOTICES + 1];

    while(fscanf(history_file, "%[^\n]s", line) != EOF)
    {
        fgetc(history_file);                             //se saca el \n del buffer

        typeTransaction *new_transaction;
        new_transaction = createTransaction(line);

        pushBack(account->transactions_history, new_transaction);
    }

    fclose(history_file);
}

static void loadAccAddressees(typeAccount *account, char acc_path[])
{
    char file_path[MAX_PATH + 1];
    strcpy(file_path, acc_path);
    strcat(file_path, "addressees-file.txt");

    FILE *addressees_file = fopen(file_path, "r");
    validFileOpening(addressees_file);

    account->addressees = createMap(stringHash, stringEqual);

    char line[MAX_NOTICES + 1];

    while(fscanf(addressees_file, "%[^\n]s", line) != EOF)
    {
        fgetc(addressees_file);                             //se saca el \n del buffer

        typeAddressee *new_addressee;
        new_addressee = createAddresse(line);

        insertMap(account->addressees, new_addressee->account_number, new_addressee);
    }

    fclose(addressees_file);
}

void saveAccInfo(typeAccount *account, char acc_path[])
{
    char file_path[MAX_PATH + 1];
    strcpy(file_path, acc_path);
    strcat(file_path, "acc-info.txt");

    FILE *info_file = fopen(file_path, "w");
    validFileOpening(info_file);

    fprintf(info_file, "%li;%s\n", account->balance, account->account_number);

    fclose(info_file);
}

static void saveAccHistory(typeAccount *account, char acc_path[])
{
    char file_path[MAX_PATH + 1];
    strcpy(file_path, acc_path);
    strcat(file_path, "history-file.txt");

    FILE *history_file = fopen(file_path, "w");
    validFileOpening(history_file);

    typeTransaction *transaction = (typeTransaction *) firstList(account->transactions_history);

    while(transaction != NULL)
    {
        typeAddressee *asociated_account = transaction->associated_acount;

        fprintf(history_file, "%li;%i,%i,%i;", transaction->amount, transaction->date->day, transaction->date->month, transaction->date->year);
        fprintf(history_file, "%s;%s;%s;", asociated_account->rut, asociated_account->name, asociated_account->account_number);

        if(asociated_account->account_type == RUT_ACC)
            fprintf(history_file, "rut-acc;");
        else
            fprintf(history_file, "saving-acc;");

        if(asociated_account->favorite == true)
            fprintf(history_file, "true\n");
        else
            fprintf(history_file, "false\n");

        transaction = (typeTransaction *) nextList(account->transactions_history);
    }

    fclose(history_file);
}

static void saveAccAddressees(typeAccount *account, char acc_path[])
{
    char file_path[MAX_PATH + 1];
    strcpy(file_path, acc_path);
    strcat(file_path, "addressees-file.txt");

    FILE *addressees_file = fopen(file_path, "w");
    validFileOpening(addressees_file);

    typeAddressee *addressee = (typeAddressee *) firstMap(account->addressees);

    while(addressee != NULL)
    {
        fprintf(addressees_file, "%s;%s;%s;", addressee->rut, addressee->name, addressee->account_number);

        if(addressee->account_type == RUT_ACC)
            fprintf(addressees_file, "rut-acc;");
        else
            fprintf(addressees_file, "saving-acc;");

        if(addressee->favorite == true)
            fprintf(addressees_file, "true\n");
        else
            fprintf(addressees_file, "false\n");

        addressee = (typeAddressee *) nextMap(account->addressees);
    }

    fclose(addressees_file);
}

char *setClientPath(char rut[])
{
    char *client_path = (char *) calloc(MAX_PATH, sizeof(char));

    strcpy(client_path, "Data//Users//");
    strcat(client_path, rut);
    strcat(client_path, "//");

    return client_path;
}

char *setAccPath(char rut[], char account_type)
{
    char *acc_path = setClientPath(rut);

    if(account_type == RUT_ACC)
        strcat(acc_path, "rut-acc//");
    else
        strcat(acc_path, "saving-acc//");

    return acc_path;
}
