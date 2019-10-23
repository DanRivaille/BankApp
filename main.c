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
#include "Libraries/clientOptions.h"
#include "Libraries/login.h"

int main()
{
    Map *acc_numbers = loadAccNumbers();
    Map *admins_profiles = loadProfiles("admins.txt");
    Map *clients_profiles = loadProfiles("clients.txt");

    typeClient *client = clientLogin(clients_profiles, acc_numbers);


    saveAccount(client, RUT_ACC);
    saveClientInfo(client);
    saveProfiles(clients_profiles, "clients.txt");
    saveAccNumbers(acc_numbers);

    return 0;
}
