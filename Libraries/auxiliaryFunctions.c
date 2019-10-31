#include <stdio.h>

#include "auxiliaryFunctions.h"

void _pause(void)
{
    _cleanBuffer();

    printf("\nPulse una tecla para continuar");
    getchar();
}

void _cleanBuffer(void)
{
    int ch;
    while(((ch = fgetc(stdin)) != EOF) && (ch != '\n')){}
}
