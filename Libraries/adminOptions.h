#ifndef ADMIN_OPTIONS_H
#define ADMIN_OPTIONS_H

/**
 * Procedimiento que añade un nuevo usuario, primero lee el nuevo rut, valida que no exista en el sistema, si existe muestra una
 * advertencia y vuelve a leer el rut, en caso que no exista, se crea el nuevo perfil, con una pass aleatoria, que se usara
 * por el cliente la primera vez que inicie sesion, luego se agregara al mapa perfiles.
 * Luego se lee la informacion del cliente y se crean sus archivos base en su directorio (que tendra de nombre su rut).
 *
 * @param profiles: mapa que contiene los perfiles de los clientes guardados en el sistema, se usara para saber si el rut
 * ingresado ya existe en el sistema.
 */
void addClient(Map *profiles);

/**
 * Procedimiento que lee un rut, lo busca en el sistema, si existe elimina toda su informacion, incluyendo sus archivos y directorios
 * asociados y por ultimo lo elimina del mapa de perfiles de clientes.
 *
 * @param profiles: mapa que contiene los perfiles de los clientes guardados en el sistema, se usara para saber si el rut
 * ingresado existe en el sistema.
 */
void removeClient(Map *profiles);

/**
 * Funcion que lee un rut, y lo busca en el mapa de clientes, si no lo encuentra imprime una advertencia y lo vuelve a
 * leer, si lo encuentra lo retorna.
 *
 * @param clients_profiles: mapa que contiene los perfiles de los clientes guardados en el sistema,
 * @return puntero al registro correspondiente al cliente buscado.
 */
typeClient *searchClientRut(Map *clients_profiles);

/**
 * Funcion que lee un rut, y lo busca en el mapa de clientes, si no lo encuentra imprime una advertencia y lo vuelve a
 * leer, si lo encuentra lo retorna.
 *
 * @param acc_numbers: mapa que contiene las cuentas guardadas en el sistema,
 * @return puntero al registro correspondiente a la cuenta buscada.
 */
typeAddressee *searchAccNumber(Map *acc_numbers);

/**
 * Procedimiento que lee un nuevo aviso, y lo guarda en el archivo "notices.txt" en la carpeta del cliente, ademas incrementa
 * en contador de la cantidad de avisos en "client-info.txt".
 *
 * @param client: registro de typeClient, que contiene la informacion del cliente.
 */
void addNotice(typeClient *client);

/**
 * Procedimiento que muestra la informacion basica de un cliente (nombre, rut, cuentas activas).
 *
 * @param client: registro de typeClient, que contiene la informacion del cliente.
 */
void showClient(typeClient *client);

#endif // ADMIN_OPTIONS_H
