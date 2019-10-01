#ifndef CLIENT_OPTIONS_H
#define CLIENT_OPTIONS_H

/**
 * Procedimiento que crea una nueva cuenta, crea los archivos de esa cuenta en la carpeta del cliente y guarda la informacion
 * de la nueva cuenta en el mapa de numeros de cuentas (acc_numbers).
 *
 * @param acc_numbers: mapa que contiene los numeros de cuentas guardados del sistema.
 * @param client: contiene la informacion del cliente.
 * @param type_account: indica que tipo de cuenta se va a crear (cuenta de ahorro o cuenta rut).
 */
void createAccount(Map *acc_numbers, typeClient *client, char account_type);

#endif // CLIENT_OPTIONS_H
