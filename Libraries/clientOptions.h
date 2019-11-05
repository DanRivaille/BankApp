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
 * Procedimiento que muestra los avisos que tiene pendiente el cliente ingresado, para cada aviso, le pregutara al usuario
 * deja marcado como no leido el aviso, en ese caso se borra de la lista.
 *
 * @param client: puntero a typeClient que contiene la informacion del cliente.
 * @param list_notices: lista que contiene los avisos a mostrar.
 */
void showNotices(typeClient *client, List *list_notices);

/**
 * Procedimiento que muestra la opciones que tiene el cliente para elegir el destinatario de la transferencia y lee el monto
 * a tranferir, luego realiza la transaccion entre las cuentas y guarda el detalle en el historial de transacciones de cada
 * cuenta.
 *
 * @param acc_numbers: mapa que contendra los numeros de cuenta validos, se usara si el cliente quiere transferir a terceros.
 * @param account: informacion de la cuenta que va a transferir.
 */
void menuTransaction(Map *acc_numbers, typeAccount *account);

/**
 * Procedimiento que muestra el historial de movimientos (transacciones y depositos) de la cuenta.
 *
 * @param account: puntero a typeAccount de la cuenta que se quiere visualizar el historial.
 */
void showHistory(typeAccount *account);

/**
 * Procedimiento que agrega un nuevo destinatario a la cuenta, para ello lee el numero de cuenta del nuevo destinatario,
 * valida que este en el sistema y no este agregado ya al mapa de destinatarios de la cuenta.
 *
 * @param acc_numbers: mapa que contiene los numeros de cuentas validos en el sistema.
 * @param account: puntero a typeAccount que contiene la informacion de la cuenta en donde se agregara el nuevo destinatario.
 */
void addAddressee(Map *acc_numbers, typeAccount *account);

/**
 * Procedimiento que elimina un destinatario de la cuenta, para ello lee el numero de cuenta del destinatario,
 * valida que este agregado ya al mapa de destinatarios de la cuenta.
 *
 * @param account: puntero a typeAccount que contiene la informacion de la cuenta en donde se agregara el nuevo destinatario.
 */
void deleteAddressee(typeAccount *account);

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
