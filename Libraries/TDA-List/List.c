/**
 * Autor: Dan Santos
 */

#include <stdlib.h>
#include <assert.h>

#include "List.h"

typedef struct Node node;

struct Node{
	const void *data;		//puntero al dato que guarda
	node *prev;				//puntero al nodo anterior
	node *next;				//puntero al nodo siguiente

};

struct List{
	node *head;				//puntero a la cabecera de la lista
	node *tail;				//puntero a la cola de la lista
	node *current;			//puntero al nodo actual
	int list_count;			//cantidad de elementos de la lista

};

static node *createNode(const void *data);

List *createList(void)
{
	List *new_list = (List *) calloc(1, sizeof(List));

	return new_list;
}

node *createNode(const void *data)
{
	node *new_node = (node *) calloc(1, sizeof(node));
	new_node->data = data;

	return new_node;
}

void *firstList(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	if(list->head == NULL)
		return NULL;

	list->current = list->head;

	return (void *) list->head->data;
}

void *nextList(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	if((list->head == NULL) || (list->current == NULL) || (list->current->next == NULL))
		return NULL;

	list->current = list->current->next;

	return (void *) list->current->data;
}

void *lastList(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	if(list->tail == NULL)
		return NULL;

	list->current = list->tail;

	return (void *) list->tail->data;
}

void *prevList(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	if((list->tail == NULL) || (list->current == NULL) || (list->current->prev == NULL))
		return NULL;

	list->current = list->current->prev;

	return (void *) list->current->data;
}

void *currentList(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	if(list->current == NULL)
		return NULL;

	return (void *) list->current->data;
}

void pushFront(List *list, const void *data)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	node *new_node = createNode(data);

	if(list->head == NULL)
	{
		list->tail = new_node;
	}
	else
	{
		new_node->next = list->head;
		list->head->prev = new_node;
	}

	list->head = new_node;
	list->list_count++;
}

void pushBack(List *list, const void *data)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	node *new_node = createNode(data);

	if(list->head == NULL)
	{
		list->head = new_node;
	}
	else
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
	}

	list->tail = new_node;
	list->list_count++;
}

void pushCurrent(List *list, const void *data)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	if(list->current == NULL)	return ;

	node *new_node = createNode(data);

	new_node->next = list->current->next;
	new_node->prev = list->current;

	if(list->current->next != NULL)
		list->current->next->prev = new_node;

	list->current->next = new_node;

	if(list->current == list->tail)
		list->tail = new_node;

	list->list_count++;
}

void *popFront(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	if(list->head == NULL)
		return NULL;

	node *aux_node = list->head;
	void *aux_data = (void *) list->head->data;

	if(list->head == list->tail)
	{
		list->head = list->tail = NULL;
	}
	else
	{
		list->head = list->head->next;
		list->head->prev = NULL;
	}
	free(aux_node);
	list->list_count--;

	return aux_data;
}

void *popBack(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	if(list->head == NULL)
		return NULL;

	node *aux_node = list->tail;
	void *aux_data = (void *) list->tail->data;

	if(list->head == list->tail)
	{
		list->head = list->tail = NULL;
	}
	else
	{
		list->tail = list->tail->prev;
		list->tail->next = NULL;
	}
	free(aux_node);
	list->list_count--;

	return aux_data;
}

void *popCurrent(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	if((list->head == NULL) || (list->current == NULL))
		return NULL;

	node *aux_node = list->current;
	void *aux_data = (void *) list->current->data;
	list->current = list->current->next;

	if(list->list_count == 1)	
	{
		list->head = list->tail = list->current = NULL;
	}
	else
	{
		if(aux_node == list->head)
		{
			list->head = list->current;
			list->head->prev = NULL;
		}
		else
		{
			if(aux_node == list->tail)
			{
				aux_node->prev->next = NULL;
				list->tail = aux_node->prev;
			}
			else
			{
				aux_node->prev->next = aux_node->next;
				aux_node->next->prev = aux_node->prev;
			}
		}
	}
	
	free(aux_node);
	list->list_count--;

	return aux_data;
}

int emptyList(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	return (list->list_count == 0) ? 1 : 0;
}

int listCount(List *list)
{
	assert(list != NULL);		//si la lista es NULA, se aborta la ejecucion del programa

	return list->list_count;
}