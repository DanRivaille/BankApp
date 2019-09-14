#ifndef LOGIN_H
#define LOGIN_H

/**
 * Funcion que lee un rut ingresado, lo busca en la BD del sistema, si no lo encuentra lo vuelve a pedir, si lo encuentra lee
 * la clave y valida que sea correcta, en caso de ser invalida, la vuelve a leer hasta que sea valida
 *
 * @param profiles_admin: mapa que contiene los perfiles de admins guardados en el sistema.
 */
void adminLogin(Map *profiles_admin);

#endif // LOGIN_H
