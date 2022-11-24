#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

static Node* getNode(LinkedList *this, int nodeIndex);
static int addNode(LinkedList *this, int nodeIndex, void *pElement);

/**
 * \brief Crea una nueva LinkedList pidiendo espacio en la memoria dinamica.
 * \return Retorna -1 si hubo error y el elemento si funciono correctamente.
 */
LinkedList* ll_newLinkedList(void)
{
	LinkedList *this = (LinkedList*) malloc(sizeof(LinkedList));
	if (this != NULL)
	{
		this->pFirstNode = NULL;
		this->size = 0;
	}
	return this;
}

/**
 * \brief Es la cantidad de elementos que existen en la LinkedList
 * \ param this Puntero de tipo Linked List.
 * \return Retorna el tamaño de la LinkedList
 */
int ll_len(LinkedList *this)
{
	int retorno = -1;
	if (this != NULL)
	{
		retorno = this->size;
	}
	return retorno;
}

/**
 * \brief Obtiene un nodo de la LinkedList
 * \ param this Puntero de tipo Linked List.
 * \ param nodeIndex Indice del nodo a obtener
 * \return Retorna null si hubo error y el puntero al nodo en caso de encontrarlo en la LinkedList.
 */
static Node* getNode(LinkedList *this, int nodeIndex)
{
	Node *auxNode = NULL;
	if (this != NULL)
	{
		if (nodeIndex >= 0 && nodeIndex < ll_len(this))
		{
			auxNode = this->pFirstNode;
			if (auxNode != NULL)
			{
				for (int i = 0; i < nodeIndex; i++)
				{
					auxNode = auxNode->pNextNode;
				}
			}
		}
	}
	return auxNode;
}

/**
 * \brief Agrega y enlaza un nodo nuevo a la LinkedList
 * \ param this Puntero de tipo Linked List.
 * \ param nodeIndex posicion donde ira el nuevo nodo.
 * \ param pElement Puntero a void, contenedor del nuevo nodo.
 * \return Retorna -1 si hubo error y el elemento si funciono correctamente.
 */
static int addNode(LinkedList *this, int nodeIndex, void *pElement)
{
	int returnAux = -1;
	Node *auxNode = (Node*) malloc(sizeof(Node*));
	Node *auxPrevNode = NULL;
	if (this != NULL && auxNode != NULL)
	{
		if (nodeIndex >= 0 && nodeIndex <= ll_len(this))
		{
			auxNode->pElement = pElement;
			if (nodeIndex == 0)
			{
				auxNode->pNextNode = this->pFirstNode;
				this->pFirstNode = auxNode;
				this->size++;
				returnAux = 0;
			}
			else
			{
				auxPrevNode = getNode(this, nodeIndex - 1);
				if (auxPrevNode != NULL)
				{
					auxNode->pNextNode = auxPrevNode->pNextNode;
					auxPrevNode->pNextNode = auxNode;
					this->size++;
					returnAux = 0;
				}
			}
		}
	}
	return returnAux;
}

/**
 * \brief Agrega un elemento a la LinkedList
 * \ param this Puntero de tipo Linked List.
 * \ param pElement Puntero a void.
 * \return Retorna -1 si hubo error y el elemento si funciono correctamente.
 */
int ll_add(LinkedList *this, void *pElement)
{
	int returnAux = -1;

	if (this != NULL)
	{
		if (addNode(this, ll_len(this), pElement) == 0)
		{
			returnAux = 0;
		}
	}
	return returnAux;
}

/**
 * \brief Obtiene un elemento de un indice especifico
 * \ param this Puntero de tipo Linked List.
 * \ param index Indice de la posicion del elemento.
 * \return Retorna -1 si hubo error y el elemento si funciono correctamente.
 */
void* ll_get(LinkedList *this, int index)
{
	void *returnAux = NULL;

	if (this != NULL && index >= 0 && index < ll_len(this))
	{
		Node *auxNode = getNode(this, index);
		if (auxNode != NULL)
		{
			returnAux = auxNode->pElement;
		}
	}
	return returnAux;
}

/**
 * \brief Modifica un elemento de la LinkedList
 * \ param this Puntero de tipo Linked List.
 * \ param index Indice del elemento a modificar.
 * \ param pElement Puntero a void.
 * \return Retorna -1 si hubo error y 0 si funciono correctamente.
 */
int ll_set(LinkedList *this, int index, void *pElement)
{
	int returnAux = -1;

	if (this != NULL && index >= 0 && index < ll_len(this))
	{
		Node *auxNode = getNode(this, index);
		if (auxNode != NULL)
		{
			auxNode->pElement = pElement;
			returnAux = 0;
		}
	}
	return returnAux;
}

/**
 * \brief Limpia una LinkedList (borra sus elementos)
 * \ param this Puntero de tipo Linked List.
 * \return Retorna -1 si hubo error y 0 si funciono correctamente.
 */
int ll_remove(LinkedList *this, int index)
{
	int returnAux = -1;

	if (this != NULL && index >= 0 && index < ll_len(this))
	{
		Node *auxNode = getNode(this, index);
		if (auxNode != NULL)
		{
			if (index == 0)
			{
				this->pFirstNode = auxNode->pNextNode;
			}
			else
			{
				Node *auxPrevNode = getNode(this, index - 1);
				if (auxPrevNode != NULL)
				{
					auxPrevNode->pNextNode = auxNode->pNextNode;
				}
			}
			free(auxNode);
			this->size--;
			returnAux = 0;
		}

	}
	return returnAux;
}

/**
 * \brief Limpia una LinkedList (borra sus elementos)
 * \ param this Puntero de tipo Linked List.
 * \return Retorna -1 si la LinkedList es null o no tiene nada y 0 si funciono correctamente.
 */
int ll_clear(LinkedList *this)
{
	int returnAux = -1;
	int longitudLinkedList = ll_len(this);
	if (this != NULL && longitudLinkedList > 0)
	{
		for (int i = 0; i < longitudLinkedList; i++)
		{
			ll_remove(this, 0);
		}
		returnAux = 0;
	}

	return returnAux;
}
/**
 * \brief Borra una LinkedList
 * \ param this Puntero de tipo Linked List.
 * \return Retorna -1 si la LinkedList es null y 0 si funciono correctamente.
 */
int ll_deleteLinkedList(LinkedList *this)
{
	int returnAux = -1;
	if (this != NULL)
	{
		ll_clear(this);
		free(this);
		returnAux = 0;
	}
	return returnAux;
}
/**
 * \brief Se le pasa el indice del elemento en la LinkedList a encontrar
 * \ param this Puntero de tipo Linked List.
 * \ param pElement Puntero de tipo void.
 * \return Retorna -1 si es null, y sino la posicion de dicho elemento.
 */
int ll_indexOf(LinkedList *this, void *pElement)
{
	int returnAux = -1;
	int longitudLinkedlist = ll_len(this);
	Node *auxNode;
	if (this != NULL && longitudLinkedlist > 0)
	{
		for (int i = 0; i < longitudLinkedlist; i++)
		{
			auxNode = getNode(this, i);
			if (auxNode != NULL && auxNode->pElement == pElement)
			{
				returnAux = i;
				break;
			}
		}
	}
	return returnAux;
}

/**
 * \brief Verifica si la LinkedList esta vacia.
 * \ param this Puntero de tipo Linked List.
 * \return Retorna -1 si es null, 0 si no esta vacio, y 1 si si.
 */
int ll_isEmpty(LinkedList *this)
{
	int returnAux = -1;
	if (this != NULL)
	{
		if (ll_len(this) > 0)
		{
			returnAux = 0;
		}
		else
		{
			returnAux = 1;
		}
	}
	return returnAux;
}
/// @brief ll_push																	AGREGA UN NUEVO ELEMENTO A LA LINKEDLIST EN UNA POSICION ESPECIFICADA.
///
/// @param this																		PUNTERO TIPO LINKEDLIST.
/// @param index																	ENTERO. POSICION DONDE SE AGREGARA EL NUEVO ELEMENTO.
/// @param pElement																	PUNTERO VOID DE NUEVO ELEMENTO.
/// @return																			RETORNA -1, SI EL PUNTERO A LA LISTA ES NULL. RETORNA 0 SI FUNCIONA CORRECTAMENTE.
/**
 * \brief Elimina elemento de una posicion especificada.
 * \ param this Puntero de tipo Linked List.
 * \ param index Posicion del elemento a eliminar.
 * \return Retorna null si hubo un error, sino retorna el elemento eliminado.
 */
int ll_push(LinkedList *this, int index, void *pElement)
{
	int returnAux = -1;
	if (this != NULL && index >= 0 && index <= ll_len(this))
	{
		addNode(this, index, pElement);
		returnAux = 0;
	}
	return returnAux;
}

/**
 * \brief Elimina elemento de una posicion especificada.
 * \ param this Puntero de tipo Linked List.
 * \ param index Posicion del elemento a eliminar.
 * \return Retorna null si hubo un error, sino retorna el elemento eliminado.
 */
void* ll_pop(LinkedList *this, int index)
{
	void *returnAux = NULL;
	void *auxPElement;
	if (this != NULL && index >= 0 && index < ll_len(this))
	{
		auxPElement = ll_get(this, index);
		if (auxPElement != NULL)
		{
			returnAux = auxPElement;
			ll_remove(this, index);
		}
	}
	return returnAux;
}

/**
 * \brief Verifica si la LinkedList contiene el elemento recibido por parametro.
 * \ param this Puntero de tipo Linked List.
 * \ param pElement Puntero  void del elemento a verificar.
 * \return Retorna -1 si es null, 1 si lo contiene y 0 si no.
 */
int ll_contains(LinkedList *this, void *pElement)
{
	int returnAux = -1;
	if (this != NULL)
	{
		if (ll_indexOf(this, pElement) != -1)
		{
			returnAux = 1;
		}
		else
		{
			returnAux = 0;
		}
	}
	return returnAux;
}

/**
 * \brief Verifica si todos los elementos de la segunda LinkedList existen en la primera.
 * \ param this Puntero de tipo Linked List.
 * \ param this2 Puntero de tipo Linked List.
 * \return Retorna 1 si los contiene, 0 si no.
 */
int ll_containsAll(LinkedList *this, LinkedList *this2)
{
	int returnAux = -1;
	int len;
	if (this != NULL && this2 != NULL)
	{
		len = ll_len(this2);
		if (len == 0)
		{
			returnAux = 0;
		}
		else
		{
			for (int i = 0; i < len; i++)
			{
				if (ll_contains(this, ll_get(this2, i)) == 0)
				{
					returnAux = 0;
					break;
				}
				else
				{
					returnAux = 1;
				}
			}
		}
	}
	return returnAux;
}

/**
 * \brief Crea una nueva LinkedList con los elementos indicados.
 * \ param this Puntero de tipo Linked List.
 * \ param from Indice desde donde se copian los elementos a la nueva LinkedList.
 * \ param to Indice hasta donde se copian los elementos a la nueva LinkedList.
 * \ param order Ordena la LinkedList (1 Ascendete, 0 Descendente).
 * \return Retorna NULL si hubo error, y sino la nueva lista.
 */
LinkedList* ll_subList(LinkedList *this, int from, int to)
{
	LinkedList *cloneArray = NULL;
	void *auxPElement;
	if (this != NULL && to > from && to <= ll_len(this) && from >= 0 && from < ll_len(this))
	{
		cloneArray = ll_newLinkedList();
		if (cloneArray != NULL)
		{
			for (int i = from; i < to; i++)
			{
				auxPElement = ll_get(this, i);
				if (auxPElement != NULL)
				{
					ll_add(cloneArray, auxPElement);
				}
			}
		}
	}
	return cloneArray;
}

/**
 * \brief Replica una LinkedList existente con todos sus elementos.
 * \ param this Puntero de tipo Linked List.
 * \ param pFunc Puntero a funcion criterio
 * \ param order Ordena la LinkedList (1 Ascendete, 0 Descendente).
 * \return Retorna NULL si el puntero a LinkedList es null (hubo error), y sino la nueva lista.
 */
LinkedList* ll_clone(LinkedList *this)
{
	LinkedList *cloneArray = NULL;
	if (this != NULL)
	{
		cloneArray = ll_subList(this, 0, ll_len(this));
	}
	return cloneArray;
}

/**
 * \brief Ordena los elementos de la LinkedList segun un criterio especifico.
 * \ param this Puntero de tipo Linked List.
 * \ param pFunc Puntero a funcion criterio
 * \ param order Ordena la LinkedList (1 Ascendete, 0 Descendente).
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int ll_sort(LinkedList *this, int (*pFunc)(void*, void*), int order)
{
	int returnAux = -1;
	int estaOrdenado;
	int len;
	void *auxElement = NULL;
	void *auxElementDos = NULL;
	int retornoPFunc;

	if (this != NULL && pFunc != NULL && (order == 0 || order == 1))
	{
		len = ll_len(this);
		do
		{
			estaOrdenado = 1;
			len--;
			for (int i = 0; i < len; i++)
			{
				auxElement = ll_get(this, i);
				auxElementDos = ll_get(this, i + 1);
				retornoPFunc = pFunc(auxElement, auxElementDos);
				if ((retornoPFunc > 0 && order == 1) || (retornoPFunc < 0 && order == 0))
				{
					ll_set(this, i, auxElementDos);
					ll_set(this, i + 1, auxElement);
					estaOrdenado = 0;
				}
			}
		} while (estaOrdenado == 0);
		returnAux = 0;
	}
	return returnAux;
}
/**
 * \brief Crea una nueva LinkedList con los elementos que coincidan en algun criterio de otra LinkedList
 * \ param this Puntero de tipo Linked List.
 * \ param pFunc Puntero a funcion criterio
 * \return Retorna NULL si el puntero a LinkedList es null (hubo error), y sino la nueva lista.
 */
LinkedList* ll_filter(LinkedList *this, int (*pFunc)(void*))
{
	LinkedList *filterList = NULL;
	int lenList;
	void *auxElement;
	if (this != NULL && pFunc != NULL)
	{
		filterList = ll_newLinkedList();

		lenList = ll_len(this);
		if (filterList != NULL && lenList > 0)
		{
			for (int i = 0; i < lenList; i++)
			{
				auxElement = ll_get(this, i);

				if (auxElement != NULL && pFunc(auxElement) == 1)
				{
					ll_add(filterList, auxElement);
				}
			}
		}
	}
	return filterList;
}

/**
 * \brief Modifica alguno de los campos del elemento en caso de necesitarlo.
 * \ param this Puntero de tipo Linked List.
 * \ param pFunc Puntero a funcion criterio
 * \return Retorna un puntero LinkedList con la nueva lista y null si fallo
 */
LinkedList* ll_map(LinkedList *this, void (*pFunc)(void*))
{
	int lenList;
	void *auxElement;
	if (this != NULL && pFunc != NULL)
	{
		lenList = ll_len(this);
		if (lenList > 0)
		{
			for (int i = 0; i < lenList; i++)
			{
				auxElement = ll_get(this, i);
				if (auxElement != NULL)
				{
					pFunc(auxElement);
				}
			}
		}
	}
	return this;
}

/**
 * \brief Cuenta los elementos de la lista segun un criterio especifico.
 * \ param this Puntero de tipo Linked List.
 * \ param pFunc Puntero a funcion criterio
 * \return Retorna 1 si conto, y 0 si no. // Retorna el acumulador de los elementos.
 */
int ll_count(LinkedList *this, int (*pFunc)(void*))
{
	int returnLl_count = 0;
	int lenList;
	void *auxElement;
	if (this != NULL && pFunc != NULL)
	{
		lenList = ll_len(this);
		if (lenList > 0)
		{
			for (int i = 0; i < lenList; i++)
			{
				auxElement = ll_get(this, i);

				if (auxElement != NULL)
				{
					returnLl_count += pFunc(auxElement);
				}
			}
		}
	}
	return returnLl_count;
}

