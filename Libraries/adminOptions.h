#ifndef ADMIN_OPTIONS_H
#define ADMIN_OPTIONS_H

/**
 * Funcion que añade un nuevo usuario, primero lee el nuevo rut, valida que no exista en el sistema, si existe muestra una
 * advertencia y vuelve a leer el rut, en caso que no exista, se crea el nuevo perfil, con una pass aleatoria, que se usara
 * por el cliente la primera vez que inicie sesion, luego se agregara al mapa perfiles.
 * Luego se lee la informacion del cliente y se crean sus archivos base en su directorio (que tendra de nombre su rut).
 *
 * @param profiles: mapa que contiene los perfiles de los clientes guardados en el sistema, se usara para saber si el rut
 * ingresado ya existe en el sistema.
 */
void addClient(Map *profiles);

#endif // ADMIN_OPTIONS_H
