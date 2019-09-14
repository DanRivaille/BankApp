#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

#define MAX_PATH 100

/**
 * Funcion que carga los perfiles en el archivo con nombre "file_name", y retorna un mapa co nlos perfiles cargados, usando como
 * key el rut del perfil, y como data un typeProfile que guarda la info del perfil.
 *
 * @param file_name: nombre del archivo donde se sacaran los perfiles (admins.txt o clients.txt).
 * @return puntero al mapa recien creado con los perfiles cargados.
 */
Map *loadProfiles(char file_name[]);

/**
  * Funcion que valida si el archivo "file" fue abierto correctamente, en caso contrario, imprime una advertencia y aborta
  * la ejecucion del programa
  *
  * @param file: puntero al archivo a analizar
  */
void validFileOpening(FILE *file);

#endif // FILE_FUNCTIONS_H
