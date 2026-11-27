#include <stdio.h>
#include <stdlib.h>
#include "doublelinkedlist.h"

llist* listCreate()
{
    llist* list;
    list = (llist*)malloc(sizeof(llist));

    if (list != NULL)
    {
        list->head = (llnode*)malloc(sizeof(llnode));

       if (list->head != NULL) {
    		list->head->data = 0;
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

int* getData(llist *list)
{
    if (list != NULL &&
        list->current != NULL &&
        list->current != list->head)
    {
        return &(list->current->data);
    }

    return NULL;
}

llError gotoNextNode(llist* list)
{
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

llError gotoPreviousNode(llist* list)
{
    llError result = NullNode;

    if (list != NULL && list->current != NULL)
    {
        if (list->current->predecessor != NULL)
        {
            list->current = list->current->predecessor;
            result = OK;
        }
        else
        {
            result = IllegalNode;
        }
    }

    return result;
}

llError gotoHead(llist* list)
{
    llError result = NullNode;
    if (list != NULL) {
        result = OK;
        // reset current to head
        list->current = list->head;
    }
    return result;
}

llError gotoTail(llist* list)
{
    llError result = NullNode;
    if (list != NULL) {
        result = OK;
        // reset current to head
        list->current = list->tail;
    }
    return result;
}
