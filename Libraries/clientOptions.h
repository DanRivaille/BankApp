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

/**
 * Procedimiento que agrega un nuevo destinatario a la cuenta, para ello lee el numero de cuenta del nuevo destinatario,
 * valida que este en el sistema y no este agregado ya al mapa de destinatarios de la cuenta.
 *
 * @param acc_numbers: mapa que contiene los numeros de cuentas validos en el sistema.
 * @param account: puntero a typeAccount que contiene la informacion de la cuenta en donde se agregara el nuevo destinatario.
 */
void addAddressee(Map *acc_numbers, typeAccount *account);

/**
 * Procedimiento que muestra los destinatarios guardados de la cuenta.
 *
 * @param account: puntero a typeAccount de la cuenta que contiene los destinatarios que se quieren mostrar.
 */
void showAddressees(typeAccount *account);

/**
 * Procedimiento que muestra los destinatarios guardados como favoritos de la cuenta.
 *
 * @param account: puntero a typeAccount de la cuenta que contiene los destinatarios favoritos.
 */
void showFavAddressees(typeAccount *account);

#endif // CLIENT_OPTIONS_H
