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
    Map *acc_numbers = loadAccNumbers();

    typeAddressee *adrese = firstMap(acc_numbers);

    while(adrese != NULL)
    {
        printf("-%s %s %s ", adrese->rut, adrese->name, adrese->account_number);
        printf("%i-\n", adrese->account_type);

        adrese = nextMap(acc_numbers);
    }

    return 0;
}
