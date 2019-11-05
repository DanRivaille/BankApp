#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "typesData.h"
#include "auxiliaryFunctions.h"

void _pause(void)
{
    _cleanBuffer();

    printf("\nPulse una tecla para continuar");
    getchar();
    system("clear");
}

void _cleanBuffer(void)
{
    int ch;
    while(((ch = fgetc(stdin)) != EOF) && (ch != '\n')){}
}

Date *getCurrentDate(void)
{
    time_t t = time(NULL);
    struct tm *tm;
    tm = localtime(&t);

    Date *current_date = (Date *) malloc(sizeof(Date) * 1);
    current_date->day = tm->tm_mday;
    current_date->month = tm->tm_mon;
    current_date->year = 1900 + (tm->tm_year);

    return current_date;
}
