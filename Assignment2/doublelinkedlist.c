#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

llist* listCreate()
{
    llist* list;
    list = (llist*)malloc(sizeof(llist));

    if (list != NULL)
    {
        list->head = (llnode*)malloc(sizeof(llnode));

        if (list->head != NULL)
        {
            list->head->successor = NULL;
            list->head->predecessor = NULL;

            list->current = list->head;
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


