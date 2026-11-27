#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef enum {
    OK,          ///< No error
    IllegalNode, ///< attempt to access an illegal node
    NoMemory,    ///< system cannot allocate &rarr; out of memory
    NullNode     ///< received NULL in list parameter
} llError;

struct {
	int id;           ///< id number of item
	char name[50];    ///< name of item
	char description[255]; ///< description of item
} data;

typedef struct n {
	data d; ///< store some data in node
	struct n* successor; /**< store successor of node
				 as typedef is not yet completed
				 name llnode cannot be used*/
} llnode;

typedef struct {
    llnode* head; ///< pointer to head of list
	llnode* tail; ///< pointer to tail of list
    llnode* current; ///< current node of list
} llist;

typedef struct llnode {
    int data;
    struct llnode *successor;
    struct llnode *predecessor;
} llnode;

llist* listCreate();
llError listDelete(llist* list);
data* accessData(llist* list);
llError insertAfter(data* d, llist* list);
llError deleteNext(llist* list);
llError deleteCurrent(llist* list);
llError gotoHead(llist* list);
llError gotoNextNode(llist* list);

#endif

