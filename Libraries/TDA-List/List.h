#ifndef LIST_H
#define LIST_H

typedef struct List List;

List *createList(void);
/**
 * Funcion que retorna la lista vacia recien creada (head = NULL)
 * Complejidad O(1)
 *
 * @return puntero a la lista recien creada
 */

void *firstList(List *list);
/**
 * Retorna el primer dato de la lista (head->data), si la lista esta vacia retorna NULL
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return puntero al primer dato de la lista
 */

void *nextList(List *list);
/**
 * Retorna el siguiente dato, tomando como referencia el nodo actual (current), si la lista esta vacia, 
 * el current esta en tail o el current es NULL, retorna NULL
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return puntero al siguiente dato de la lista
 */

void *lastList(List *list);
/**
 * Retorna el ultimo dato de la lista, si la lista esta vacia retorna NULL
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return puntero al dato del ultimo nodo de la lista
 */

void *prevList(List *list);
/**
 * Retorna el dato del nodo anterior, tomando como referencia el nodo actual (current), si la lista
 * esta vacia, el current esta en head o el current es NULL, retorna NULL
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return puntero al dato anterior del current
 */

void *currentList(List *list);
/**
 * Retorna el dato del nodo actual (current), si la lista esta vacia o el current es NULL retorna NULL
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return puntero al dato del current
 */

void pushFront(List *list, const void *data);
/**
 * Crea un nuevo nodo con "data" como dato, y lo ingresa en la cabecera de la lista
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @param data - puntero al dato a ingresar a la lista 
 */

void pushBack(List *list, const void *data);
/**
 * Crea un nuevo nodo con "data" como dato, y lo ingresa al final de la lista
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @param data - puntero al dato a ingresar a la lista
 */

void pushCurrent(List *list, const void *data);
/**
 * Crea un nuevo nodo con "data" como dato, y lo ingresa luego del current de la lista
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @param data - puntero al dato a ingresar a la lista
 */

void *popFront(List *list);
/**
 * Elimina el primer nodo de la lista y retorna su dato, si la lista esta vacia retorna NULL
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return puntero al dato del nodo eliminado
 */

void *popBack(List *list);
/**
 * Elimina el primer nodo de la lista y retorna su dato, si la lista esta vacia retorna NULL
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return puntero al dato del nodo eliminado
 */

void *popCurrent(List *list);
/**
 * Elimina el primer nodo de la lista y retorna su dato, si la lista esta vacia retorna NULL
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return puntero al dato del nodo eliminado
 */

int emptyList(List *list);
/**
 * Coprueba si la lista esta vacia, si lo esta retorna 1, sino retorna 0
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return 1 (true) si y solo si la lista esta vacia, en caso contrario 0 (false)
 */

int listCount(List *list);
/**
 * Retorna la cantidad de elementos de la lista
 * Complejidad O(1)
 *
 * @param list - puntero a la lista
 * @return cantidad de elementos de la lista
 */

#endif /* LIST_H */