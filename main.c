/**
 * Author: Dan Santos
 * Repository: https://github.com/DanSantosAA/BankApp
 */

#include "stdio.h"

#include "Libraries/TDA-List/List.h"
#include "Libraries/TDA-Map/Map.h"

#include "Libraries/typesData.h"
#include "Libraries/fileFunctions.h"
#include "Libraries/adminOptions.h"
#include "Libraries/login.h"

int main()
{
    //Map *profiles_admins = loadProfiles("admins.txt");
    Map *profiles_clients = loadProfiles("clients.txt");

    //adminLogin(profiles_admins);

    addClient(profiles_clients);

    saveProfiles(profiles_clients, "clients.txt");

    return 0;
}
