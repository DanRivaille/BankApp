#include <stdio.h>
#include <string.h>

#include "TDA-Map/Map.h"
#include "typesData.h"
#include "fileFunctions.h"
#include "login.h"

typeProfile *login(Map *profiles)
{
    char rut[MAX_CARACT + 1];
    typeProfile *profile;

    printf("Ingrese su rut (sin digito verificador): ");
    scanf("%s", rut);
    getchar();

    while((profile = (typeProfile *) searchMap(profiles, rut)) == NULL)
    {
        printf("No se encontro un perfil con el rut ingresado\n");
        printf("Intente nuevamente: ");
        scanf("%s", rut);
        getchar();
    }

    char pass[MAX_CARACT + 1];
    bool success_login = false;

    while(success_login != true)
    {
        printf("Ingrese su password: ");
        scanf("%s", pass);
        getchar();

        if(strcmp(pass, profile->pass) != 0)
        {
            printf("No coincide la password ingresada\n");
            printf("Intente nuevamente: ");
            scanf("%s", pass);
            getchar();
        }
        else
        {
            success_login = true;
        }
    }

    return profile;
}
