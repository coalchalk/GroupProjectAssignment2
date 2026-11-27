/**
 * @file doublelinkedlist.h
 * Header file for double linked list implementation
 *
 * @author	Chloe
 * @date	26.10.2013
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
  * Defines the error codes for double linked list
  */
typedef enum {
    OK,
    IllegalNode,
    NoMemory,
    NullNode
} llError;

/**
 * Defines the structure for data to be stored in double linked list
 */
typedef struct {
    int id;
    char name[50];
    char description[255];
} data;

/**
 * Defines structure for a node of double linked list
 */
typedef struct llnode {
    data d;
    struct llnode *successor;
    struct llnode *predecessor;
} llnode;

/**
 * Defines the type for double linked list
 */
typedef struct {
    llnode *head;
    llnode *tail;
    llnode *current;
} llist;

// Function declarations
llist* listCreate(void);
llError listDelete(llist *list);
data* getData(llist *list);
llError gotoHead(llist *list);
llError gotoTail(llist *list);
llError gotoNextNode(llist *list);
llError gotoPreviousNode(llist *list);
llError insertAfter(data *d, llist *list);
llError insertBefore(data *d, llist *list);
llError deleteCurrent(llist *list);

#endif
