/**
 * @file doublelinkedlist.c
 * Implementing a double linked list
 *
 * author:	
 * date:	26.10.2013
 */
#include <stdio.h>
#include <stdlib.h>
#include "doublelinkedlist.h"

/**
 * @brief Creates an empty double linked list
 * Head points to the tail, which is implemented as NULL
 * @return Pointer to newly created list, or NULL on failure.
 */
llist* listCreate() {
    llist* list;
    list = (llist*)malloc(sizeof(llist));

    if (list != NULL) {
        list->head = (llnode*)malloc(sizeof(llnode));

       if (list->head != NULL) {
    		list->head->d.id = 0;
			list->head->d.name[0] = '\0';
			list->head->d.description[0] = '\0';
    		list->head->successor = NULL;
   		 	list->head->predecessor = NULL;

    		list->current = list->head;
    		list->tail = list->head;
        } else {
            free(list);
            list = NULL;
        }
    }
    return list;
}

/**
 * @brief Deletes the list 
 *
 * @param list pointer to valid list
 */
llError listDelete(llist *list) {
    llError result = NullNode;

    if (list != NULL)
    {
        llnode *current = list->head;
        llnode *next;

        while (current != NULL)
        {
            next = current->successor;
            free(current);
            current = next;
        }

        free(list);
        result = OK;
    }

    return result;
}

/**
 * @brief Returns the data of current node.
 *
 * @param list List to access.
 * @return Pointer to current node's data, or NULL if
 *      the current node is the head node or invalid.
 */
data* getData(llist *list)
{
    if (list != NULL &&
        list->current != NULL &&
        list->current != list->head) {
        return &(list->current->d);
    }
    return NULL;
}

/**
 * @brief Moves the current node by forward.
 *
 * @param list List to traverse.
 * @return OK on success, IllegalNode if the current node is
 *         the last node in the list, or NullNode if list is NULL.
 */
llError gotoNextNode(llist* list) {
    llError result = NullNode;
    if (list != NULL) {
        result = OK;
        // is successor of current tail?
        if (list->current->successor != NULL) {
            // no -> move forward
            list->current = list->current->successor;
        } else {
            // reached end of list, cannot move any further
            result = IllegalNode;
        }
    }
	return result;
}

/**
 * @brief Moves the current node to its predecessor.
 *
 * @param list List to traverse.
 * @return OK on success, IllegalNode if the current node has
 * no predecessor, or NullNode if list is NULL.
 */
llError gotoPreviousNode(llist* list) {
    llError result = NullNode;

    if (list != NULL && list->current != NULL)
    {
        if (list->current->predecessor != NULL)
        {
            list->current = list->current->predecessor;
            result = OK;
        } else {
            result = IllegalNode;
        }
    }
    return result;
}

/**
 * @brief Sets current node of list to head.
 *
 * @param list list to be reset
 */
llError gotoHead(llist* list) {
    llError result = NullNode;
    if (list != NULL) {
        result = OK;
        // reset current to head
        list->current = list->head;
    }
    return result;
}

/**
 * @brief Sets current node of list to tail.
 *
 * @param list list to be reset
 */
llError gotoTail(llist* list) {
    llError result = NullNode;
    if (list != NULL) {
        result = OK;
        // reset current to head
        list->current = list->tail;
    }
    return result;
}

/**
 * Creates a new node newnode, associates data d with
 * newnode and inserts newnode in list as successor of
 * current node
 *
 * @param d data to be associated with newnode
 * @param list list into which to insert d
 * @return ok if insertion successful or
 *         noMemory if no memory available to create newnode
 */
llError insertAfter(data* d, llist* list) {
    llError result = NullNode;
    llnode *newnode;

    if (list != NULL && list->current != NULL) {
        newnode = (llnode*)malloc(sizeof(llnode));

        if (newnode == NULL) {
            result = NoMemory;
        } else {
            newnode->d = *d;

            newnode->successor = list->current->successor;
            newnode->predecessor = list->current;

            if (list->current->successor != NULL) {
                list->current->successor->predecessor = newnode;
            }

            list->current->successor = newnode;

            if (list->tail == list->current) {
                list->tail = newnode;
            }

            result = OK;
        }
    }

    return result;
}

/**
 * @brief Inserts a new node before the current node.
 * Creates a new node, associates the data pointed to by d
 * with the new node, and inserts the new node immediately
 * before the current node in list.
 *
 * @param d Data to be stored in the new node.
 * @param list List into which the new node is inserted.
 * @return OK if insertion is successful,
 *         NoMemory if memory allocation fails,
 *         IllegalNode if insertion before the current node
 *         is not permitted.
 */
llError insertBefore(data *d, llist *list) {
    llError result = NullNode;
    llnode *newnode;

	if (list == NULL ||
    list->current == NULL ||
    list->current == list->head) {
    return IllegalNode;
}

    if (list != NULL && list->current != NULL) {
        newnode = (llnode *)malloc(sizeof(llnode));

        if (newnode == NULL) {
            result = NoMemory;
        } else {
            newnode->d = *d;

            newnode->successor = list->current;
            newnode->predecessor = list->current->predecessor;

            if (list->current->predecessor != NULL) {
                list->current->predecessor->successor = newnode;
            }

            list->current->predecessor = newnode;

            result = OK;
        }
    }
    return result;
}

/**
 * @brief Removes current node from double linked list.
 * New current node will be predecessor of current node (best option as in this
 * implementation current cannot be tail).
 *
 * @param list pointer to list from which node is
 *             to be removed
 * @return ok if current node has been removed or
 *         illegalNode if current node cannot be removed
 *             as it is head or its predecessor cannot be found
 */
llError deleteCurrent(llist* list) {
    llError result = NullNode;

    if (list != NULL && list->current != NULL)
    {
        if (list->current == list->head) {
            result = IllegalNode;
        }  else {
            llnode *pred = list->current->predecessor;
            llnode *succ = list->current->successor;

            pred->successor = succ;

            if (succ != NULL) {
                succ->predecessor = pred;
            }

            if (list->current == list->tail) {
                list->tail = pred;
            }

            free(list->current);

            list->current = pred;

            result = OK;
        }
    }
    return result;
}
