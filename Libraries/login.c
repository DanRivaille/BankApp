#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "TDA-Map/Map.h"
#include "typesData.h"
#include "fileFunctions.h"
#include "clientOptions.h"
#include "login.h"

/** Prototipos de funciones estaticas */
static void firstClientLogin(typeClient *client, typeProfile *profile, Map *acc_numbers);
static bool validatePass(char pass[]);

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

typeClient *clientLogin(Map *clients_profiles, Map *acc_numbers)
{
    typeProfile *profile = login(clients_profiles);
    typeClient *client = loadClientInfo(profile->rut);

    if(client->rut_account == NULL)
        firstClientLogin(client, profile, acc_numbers);
    else
        loadAccount(client->rut_account, client->rut, RUT_ACC);

    if(client->saving_account != NULL)
        loadAccount(client->saving_account, client->rut, SAVING_ACC);

    return client;
}

/** Procedimiento que la pide al usuario una nueva contraseña, y le crea su cuenta rut */
static void firstClientLogin(typeClient *client, typeProfile *profile, Map *acc_numbers)
{
    printf("Ingrese su nueva password: ");
    scanf("%[^\n]s", profile->pass);
    getchar();

    while(validatePass(profile->pass) == false)
    {
        printf("Intentelo nuevamente: ");
        scanf("%[^\n]s", profile->pass);
        getchar();
    }
    createAccount(acc_numbers, client, RUT_ACC);
}

/** Funcion que valida que la clave ingresada como parametro, cumpla con los requisitos minimos de seguridad */
static bool validatePass(char pass[])
{
    int length = strlen(pass);

    if(length < 4)
    {
        printf("Su password debe tener almenos 4 caracteres (letras y numeros)\n");
        return false;
    }

    int cant_letters = 0;
    int cant_digits = 0;
    int i;

    for(i = 0; i < length; i++)
    {
        if(isalnum(pass[i]) == 0)
        {
            printf("Solo puede tener letras o numeros\n");
            return false;
        }

        if(isdigit(pass[i]))
            cant_digits++;
        else
            cant_letters++;
    }

    if(cant_digits < 1)
    {
        printf("Su password debe tener almenos un numero\n");
        return false;
    }

    if(cant_letters < 1)
    {
        printf("Su password debe tener almenos una letra\n");
        return false;
    }

    return true;
}
