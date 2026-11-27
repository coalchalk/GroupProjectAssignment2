/**
 * @file orderSet.h
 * header file for ordered int set implementation
 * using double linked list
 *
 * @author	Sania & Aisling
 * @date	26.10.2013
 */
#ifndef ORDERSET_H
#define ORDERSET_H
#include "doublelinkedlist.h"

/**
 * define error codes for ordered set operations
 */
typedef enum {
    NUMBER_ADDED,           //element added
    NUMBER_ALREADY_IN_SET,  //element is already in the set
    NUMBER_REMOVED,         //element removed
    NUMBER_NOT_IN_SET,      //element not found in the set
    ALLOCATION_ERROR        //dynamic memory allocation failed
} setError;

/*define struct for ordered int set
 * */
typedef struct {
    llist* list; //
    int count; // number of element are stored in the set
} intSet;

/* function declarations*/
intSet* createOrderedSet(void);
void deleteOrderedSet(intSet* s);
setError addElement(intSet* s, int elem);
intSet* setIntersection(intSet* s1, intSet* s2);
intSet* setUnion(intSet* s1, intSet* s2);
intSet* setDifference(intSet* s1, intSet* s2);
void printToStdout(intSet* s);

#endif // ORDERSET_H
