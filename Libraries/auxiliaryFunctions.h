#ifndef AUXILIARY_FUNCTIONS_H
#define AUXILIARY_FUNCTIONS_H

/**
 * Procedimiento que simula la funcion system("pause") de windos y limpia el buffer del teclado.
 */
void _pause(void);

/**
 * Procedimiento que limpia el buffer del teclado.
 */
void _cleanBuffer(void);

/**
 * Funcion obtiene la fecha actual del computador.
 *
 * @return puntero al registro Date con la fecha actual.
 */
Date *getCurrentDate(void);

#endif // AUXILIARY_FUNCTIONS_H
