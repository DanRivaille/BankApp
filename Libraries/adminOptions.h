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
 * Procedimiento que lee un rut, y lo busca en el mapa de clientes, si no lo encuentra imprime una advertencia y lo vuelve a
 * leer, si lo encuentra muestra la infomacion del cliente asociado al rut ingresado.
 *
 * @param clients_profiles: mapa que contiene los perfiles de los clientes guardados en el sistema,
 */
void searchClientRut(Map *clients_profiles);

/**
 * Procedimiento que muestra la informacion basica de un cliente (nombre, rut, cuentas activas).
 *
 * @param client: registro de typeClient, que contiene la informacion del cliente.
 */
void showClient(typeClient *client);

#endif // ADMIN_OPTIONS_H
