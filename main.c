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

    Map *profiles = loadProfiles("clients.txt");

    typeProfile *profile = login(profiles);
    typeClient *client = loadClientInfo(profile->rut);

    createAccount(acc_numbers, client, RUT_ACC);

    saveClientInfo(client);
    saveProfiles(profiles, "clients.txt");
    saveAccNumbers(acc_numbers);

    return 0;
}
