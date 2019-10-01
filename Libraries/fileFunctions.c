#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "typesData.h"
#include "TDA-List/List.h"
#include "TDA-Map/Map.h"
#include "fileFunctions.h"

/** Prototipos */
static typeAddressee *createAddresse(char line[]);

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
    char client_path[MAX_PATH + 1] = "Data//Users//";
    strcat(client_path, rut);
    strcat(client_path, "//client-info.txt");

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

    return client;
}

void saveClientInfo(typeClient *client)
{
    char file_path[MAX_PATH + 1] = "Data//Users//";
    strcat(file_path, client->rut);
    strcat(file_path, "//client-info.txt");

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

    return acc_numbers;
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

void validFileOpening(FILE *file)
{
    if(file == NULL)
    {
        printf("\n**ERROR, NO SE PUDO ABRIR EL ARCHIVO**\n");
        exit(EXIT_FAILURE);
    }
}
