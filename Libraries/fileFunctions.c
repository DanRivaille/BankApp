#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "typesData.h"
#include "TDA-List/List.h"
#include "TDA-Map/Map.h"
#include "fileFunctions.h"

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

void validFileOpening(FILE *file)
{
    if(file == NULL)
    {
        printf("\n**ERROR, NO SE PUDO ABRIR EL ARCHIVO**\n");
        exit(EXIT_FAILURE);
    }
}
