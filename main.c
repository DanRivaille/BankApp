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
    Map *profiles_admi = loadProfiles("admins.txt");

    adminLogin(profiles_admi);

    //saveProfiles(profiles_admi, "admins.txt");

    return 0;
}
