/**
 * Author: Dan Santos
 * Repository: https://github.com/DanSantosAA/BankApp
 */

#include <stdio.h>
#include <stdlib.h>

#include "Libraries/TDA-List/List.h"
#include "Libraries/TDA-Map/Map.h"

#include "Libraries/typesData.h"
#include "Libraries/fileFunctions.h"
#include "Libraries/adminOptions.h"
#include "Libraries/clientOptions.h"
#include "Libraries/login.h"

#define ADMIN_PROFILE 1
#define CLIENT_PROFILE 2

int mainMenu(void);                             //menu en donde se eligira el tipo de perfil (administrador o cliente)
void mainMenuAdmin(Map *acc_numbers);           //menu con opciones del administrador
void mainMenuClient(Map *acc_numbers);          //menu con opciones del cliente
void optionsInfoClient(void);                   //mostrara la informacion del cliente y la opcion de actualizar dicha info
void accessAccount(void);                       //menu que mostrara las cuentas del cliente
void menuAccount(void);                         //menu que mostrara informacion de la cuenta y la opcion de ver opciones
void optionsAccount(void);                      //menu que mostrara las opciones disponible de la cuenta
void optionsAddressees(void);                   //menu que mostrara las opciones disponible de los destinatarios de la cuenta
void optionSearchClient(Map *clients_profiles);                  //mostrara la informacion del usuario buscado y la opcion de agregarle un aviso
void optionSearchAccount(Map *acc_numbers);                 //mostrara la informacion de la cuenta buscada y la opcion de depositarle

int main()
{
    Map *acc_numbers = loadAccNumbers();

    int option = mainMenu();

    if(option == ADMIN_PROFILE)
        mainMenuAdmin(acc_numbers);
    else
        mainMenuClient(acc_numbers);

    saveAccNumbers(acc_numbers);

    return 0;
}

int mainMenu(void)
{
    int option;

    do
    {
        printf("Bienvenido a BankApp\n\n");
        printf("1 - administrador   2 - cliente\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        if((option != 1) && (option != 2))
            printf("Opcion ingresada no valida\n");

    }while((option != 1) && (option != 2));

    return option;
}

void mainMenuAdmin(Map *acc_numbers)
{
    Map *admins_profiles = loadProfiles("admins.txt");
    login(admins_profiles);
    system("clear");

    Map *clients_profiles = loadProfiles("clients.txt");

    int option;
    do
    {
        printf("Menu Administrador\n\n");
        printf("1 - Buscar cliente por rut\n");
        printf("2 - Buscar cuenta por numero de cuenta\n");
        printf("3 - Agregar cliente\n");
        printf("4 - Eliminar cliente\n");
        printf("5 - Salir\n\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        switch(option)
        {
            case 1  : optionSearchClient(clients_profiles);            break;
            case 2  : optionSearchAccount(acc_numbers);           break;
            case 3  : addClient(clients_profiles);     break;
            case 4  : printf("eliminar cliente\n");    break;
            case 5  : printf("Sesion finalizada\n");   break;
            default : printf("Opcion ingresada no valida\n");
        }
    }while(option != 5);

    saveProfiles(admins_profiles, "admins.txt");
    saveProfiles(clients_profiles, "clients.txt");
}

void optionSearchClient(Map *clients_profiles)
{
    typeClient *client = searchClientRut(clients_profiles);     //se busca el cliente por el rut
    system("clear");

    int option;
    do
    {
        printf("Nombre: %s      Rut: %s\n\n", client->name, client->rut);
        printf("1 - agregar aviso\n");
        printf("2 - Volver\n\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        getchar();
        system("clear");

        switch(option)
        {
            case 1  : addNotice(client);              break;
            case 2  : system("clear");                break;
            default : printf("Opcion ingresada no valida\n");
        }
    }while(option != 2);

    saveClientInfo(client);
}

void optionSearchAccount(Map *acc_numbers)
{
    int option;
    do
    {
        printf("Buscar cuenta\n\n");
        printf("1 - Depositar\n");
        printf("2 - Volver\n\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        switch(option)
        {
            case 1  : printf("despositar\n");                    break;
            case 2  : system("clear");                           break;
            default : printf("Opcion ingresada no valida\n");
        }
    }while(option != 2);
}

void mainMenuClient(Map *acc_numbers)
{
    int option;

    do
    {
        printf("Menu Cliente\n\n");
        printf("1 - Ver mi informacion\n");
        printf("2 - Acceder a cuentas\n");
        printf("3 - Ver avisos\n");
        printf("4 - Salir\n\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        switch(option)
        {
            case 1  : optionsInfoClient();                break;
            case 2  : accessAccount();                    break;
            case 3  : printf("ver avisos\n");             break;
            case 4  : printf("Sesion finalizada\n");      break;
            default : printf("Opcion ingresada no valida\n");
        }
    }while(option != 4);
}

void optionsInfoClient(void)
{
    int option;

    do
    {
        printf("Mi Informacion\n\n");
        printf("1 - Actualizar info\n");
        printf("2 - Volver\n\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        switch(option)
        {
            case 1  : printf("Actualizar informacion cliente\n");      break;
            case 2  : system("clear");                                 break;
            default : printf("Opcion ingresada no valida\n");
        }
    }while(option != 2);
}

void accessAccount(void)
{
    int option;

    do
    {
        printf("Mis cuentas\n\n");
        printf("1 - Cuenta Rut\n");
        printf("2 - Cuenta de Ahorro\n");
        printf("3 - Volver\n\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        switch(option)
        {
            case 1  : printf("cuenta rut\n");       menuAccount();     break;
            case 2  : printf("cuenta de ahorro\n"); menuAccount();     break;
            case 3  : system("clear");              break;
            default : printf("Opcion ingresada no valida\n");
        }
    }while((option < 1) || (option > 3));
}

void menuAccount(void)
{
    int option;

    do
    {
        printf("Cuenta ---\n\n");
        printf("1 - Ver opciones\n");
        printf("2 - Volver\n\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        switch(option)
        {
            case 1  : optionsAccount();              break;
            case 2  : system("clear");               break;
            default : printf("Opcion ingresada no valida\n");
        }
    }while(option != 2);
}

void optionsAccount(void)
{
    int option;

    do
    {
        printf("Opciones de la cuenta\n\n");
        printf("1 - Ver historial\n");
        printf("2 - Realizar transaccion\n");
        printf("3 - Administrar destinatarios\n");
        printf("4 - Volver\n\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        switch(option)
        {
            case 1  : printf("ver historial\n");                break;
            case 2  : printf("realizar transaccion\n");         break;
            case 3  : optionsAddressees();                      break;
            case 4  : system("clear");                          break;
            default : printf("Opcion ingresada no valida\n");
        }
    }while(option != 4);
}

void optionsAddressees(void)
{
    int option;

    do
    {
        printf("Administrar destintarios\n\n");
        printf("1 - Mostrar destinatarios\n");
        printf("2 - Mostrar destinatarios favoritos\n");
        printf("3 - Agregar destinario\n");
        printf("4 - Eliminar destinario\n");
        printf("5 - Volver\n\n");

        printf("Ingrese una opcion: ");
        scanf("%i", &option);
        system("clear");

        switch(option)
        {
            case 1  : printf("mostrar destinatarios\n");             break;
            case 2  : printf("mostrar destinatarios favoritos\n");   break;
            case 3  : printf("agregar destinatarios\n");             break;
            case 4  : printf("eliminar destinatario\n");             break;
            case 5  : system("clear");                               break;
            default : printf("Opcion ingresada no valida\n");
        }
    }while(option != 5);
}
