/** 
 * @file orderSet.c
 * implementing order int set using double linked list
 *
 * @author	Sania & Daithi
 * @date	26.10.2013
 * */
#include <stdio.h>
#include <stdlib.h>
#include "orderedintset.h"

/* create an empty order set
 * @return pointer ot see if successful, NULL allocation failure
 * */
intSet* createOrderedSet(void)
{
    intSet *s = malloc(sizeof(intSet));

    if (s == NULL)
        return NULL;

    s->list = listCreate();

    if (s->list == NULL)
    {
        free(s);
        return NULL;
    }

    s->count = 0;

    return s;
}

/*remove order set form the memory
 * @param s pointer to callid set to be deleted*/

void deleteOrderedSet(intSet *s)
{
    if (s != NULL)
    {
        listDelete(s->list);
        free(s);
    }
}

/**
 * add new element into right location into ordered set s
 * make sure the element is not already there
 * @param s pointer to valid set
 * @param elem int to be added
 * @return NUMBER_ADDED if addedd, NUMBER_ALREADY_IN_SET if suplicate,
 * ALLOCATION_ERROR if memory allocation fails*/

//start at header and traverse the list

setError addElement(intSet *s, int elem) {
    data *current;
    data newData;

    if (s == NULL || s->list == NULL)
        return ALLOCATION_ERROR;

    newData.id = elem;
    newData.name[0] = '\0';
    newData.description[0] = '\0';

    gotoHead(s->list);

    current = getData(s->list);

    while (current != NULL)
    {
        if (current->id == elem)
            return NUMBER_ALREADY_IN_SET;

        if (current->id > elem) {
            if (insertBefore(&newData, s->list) == OK) {
                s->count++;
                return NUMBER_ADDED;
            }
            return ALLOCATION_ERROR;
        }

        if (gotoNextNode(s->list) != OK)
            break;

        current = getData(s->list);
    }

    if (insertAfter(&newData, s->list) == OK) {
        s->count++;
        return NUMBER_ADDED;
    }

    return ALLOCATION_ERROR;
}

/** remove the number of elem from set s
 *  @param spointer to calid set
 *  @param elm int to be removed
 *  @return NUMBER_REMOVED id removed,
 *  NUMBER_NOT_IN_SET if not foun */

setError removeElement(intSet *s, int elem)
{
    data *current;

    if (s == NULL || s->list == NULL)
        return ALLOCATION_ERROR;

    gotoHead(s->list);

    current = getData(s->list);

    while (current != NULL) {
        if (current->id == elem) {
            if (deleteCurrent(s->list) == OK) {
                s->count--;
                return NUMBER_REMOVED;
            }
        }

        if (current->id > elem)
            break;

        if (gotoNextNode(s->list) != OK)
            break;
        current = getData(s->list);
    }

    return NUMBER_NOT_IN_SET;
}


/** compute intersection of s1 and s2
 *  @param s1 first set
 *  @param s2 second set
 *  @return new set contating intersecton or NULL on failure*/

intSet* setIntersection(intSet *s1, intSet *s2) {
    intSet *result;
    data *d1;
    data *d2;

    result = createOrderedSet();

    if (result == NULL)
        return NULL;

    if (s1 == NULL || s2 == NULL)
        return result;

    gotoHead(s1->list);

    d1 = getData(s1->list);

    while (d1 != NULL)  {
        gotoHead(s2->list);

        d2 = getData(s2->list);

        while (d2 != NULL)
        {
            if (d1->id == d2->id)   {
                addElement(result, d1->id);
                break;
            }

            if (gotoNextNode(s2->list) != OK)
                break;

            d2 = getData(s2->list);
        }
        if (gotoNextNode(s1->list) != OK)
            break;
        d1 = getData(s1->list);
    }

    return result;
}


/**
 * computes union of s1 and s2
 *
 * @param s1 first set
 * @param s2 second set
 * @return new set containing union, NULL on failure
 */
intSet* setUnion(intSet *s1, intSet *s2)
{
    intSet *result;
    data *d;

    result = createOrderedSet();

    if (result == NULL)
        return NULL;

    if (s1 != NULL) {
        gotoHead(s1->list);

        d = getData(s1->list);

        while (d != NULL)
        {
            addElement(result, d->id);

            if (gotoNextNode(s1->list) != OK)
                break;

            d = getData(s1->list);
        }
    }

    if (s2 != NULL) {
        gotoHead(s2->list);

        d = getData(s2->list);

        while (d != NULL)  {
            addElement(result, d->id);

            if (gotoNextNode(s2->list) != OK)
                break;

            d = getData(s2->list);
        }
    }
    return result;
}
/**
 * computes difference of s1 and s2 (s1 - s2)
 *
 * @param s1 first set
 * @param s2 second set
 * @return new set containing difference, NULL on failure
 */
intSet* setDifference(intSet *s1, intSet *s2) {
    intSet *result;
    data *d1;
    data *d2;
    int found;

    result = createOrderedSet();

    if (result == NULL)
        return NULL;

    if (s1 == NULL)
        return result;

    gotoHead(s1->list);
    d1 = getData(s1->list);

    while (d1 != NULL){
        found = 0;

        if (s2 != NULL)  {
            gotoHead(s2->list);

            d2 = getData(s2->list);

            while (d2 != NULL)  {
                if (d1->id == d2->id) {
                    found = 1;
                    break;
                }

                if (gotoNextNode(s2->list) != OK)
                    break;

                d2 = getData(s2->list);
            }
        }

        if (!found)
            addElement(result, d1->id);

        if (gotoNextNode(s1->list) != OK)
            break;

        d1 = getData(s1->list);
    }
    return result;
}

void printToStdout(intSet *s) {
    data *d;
    int first = 1;

    printf("{");
    if (s != NULL && s->list != NULL) {
        gotoHead(s->list);

        d = getData(s->list);

        while (d != NULL)
        {
            if (!first)
                printf(", ");

            printf("%d", d->id);

            first = 0;

            if (gotoNextNode(s->list) != OK)
                break;

            d = getData(s->list);
        }
    }
    printf("}");
}
