#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

typedef enum {
    OK,
    NO_MEMORY,
    ILLEGAL_NODE
} dllError;

typedef struct dllNode {
    int data;
    struct dllNode* prev;
    struct dllNode* next;
} dllNode;

typedef struct {
    dllNode* head;
    dllNode* tail;
    dllNode* current;
} DoubleLinkedList;

/* ccreation / destruction */
DoubleLinkedList* createDoubleLinkedList(void);
void              deleteDoubleLinkedList(DoubleLinkedList* list);

/* navigation */
dllError gotoHead(DoubleLinkedList* list);
dllError gotoTail(DoubleLinkedList* list);
dllError gotoNextNode(DoubleLinkedList* list);
dllError gotoPreviousNode(DoubleLinkedList* list);

/* Access */
int getData(DoubleLinkedList* list);/* returns data of current, or undefined if at head/tail */

/* the modification */
dllError insertAfter(DoubleLinkedList* list, int newdata);
dllError insertBefore(DoubleLinkedList* list, int newdata);
dllError deleteCurrent(DoubleLinkedList* list);

#endif
