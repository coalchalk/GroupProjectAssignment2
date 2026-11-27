#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef enum {
    OK,
    IllegalNode,
    NoMemory,
    NullNode
} llError;

typedef struct {
    int id;
    char name[50];
    char description[255];
} data;

typedef struct llnode {
    data data;
    struct llnode *successor;
    struct llnode *predecessor;
} llnode;

typedef struct {
    llnode *head;
    llnode *tail;
    llnode *current;
} llist;

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
