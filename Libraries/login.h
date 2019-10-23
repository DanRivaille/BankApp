#ifndef LOGIN_H
#define LOGIN_H

/**
 * Funcion que lee un rut ingresado, lo busca en la BD del sistema, si no lo encuentra lo vuelve a pedir, si lo encuentra lee
 * la clave y valida que sea correcta, en caso de ser invalida, la vuelve a leer hasta que sea valida
 *
 * @param profiles: mapa que contiene los perfiles de los usuarios guardados en el sistema.
 * @return puntero al registro typeProfile del perfil del usuario que inicio sesion.
 */
typeProfile *login(Map *profiles);

/**
 * Funcion que llama a login, usando el mapa de perfiles de los clientes, y carga la informacion del cliente que inicio sesion,
 * la funcion verifica si es la primera vez que el cliente inicio sesion, si es el caso, le pide que ingrese una nueva contraseña
 * y se crea su cuenta rut, si no es el caso, carga la informacion de las cuentas que tenga activas.
 *
 * @param clients_profiles: mapa que contiene los perfiles de los clientes guardados en el sistema.
 * @param acc_numbers: mapa que contiene los numeros de cuenta validos (char number_acc -> key, typeAddressee * ->data).
 * @return puntero al registro typeClient del cliente que inicio sesion.
 */
typeClient *clientLogin(Map *clients_profiles, Map *acc_numbers);

#endif // LOGIN_H
