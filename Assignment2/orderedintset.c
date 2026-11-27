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
intSet* createOrderedSet()
{
    intSet* s=(intSet*)malloc(sizeof(intSet));
    if (s!= NULL){
        s->list = listCreate();
        if (s->list != NULL){
            s -> count = 0;
        }else{
            free(s);
            s = NULL;
        }
    }
    return s;
}

/*remove order set form the memory
 * @param s pointer to callid set to be deleted*/

void deleteOrderedSet(intSet* s)
{
    if( s!= NULL) {
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

setError addElement(intSet* s, int elem)
{
    if (s == NULL || s->list == NULL) return ALLOCATION_ERROR;
    int currentData;

    gotoHead(s->list);
    while (gotoNextNode(s->list)== OK){
        if(getData(s->list, &currentData) == OK){
            if(currentData ==elem){
                return NUMBER_ALREADY_IN_SET;
            }
            //INSERT BEFORE The larger element
            if( currentData > elem){
                if (dllInsetBefre(s->list, elem) = OK){
                    s->count++;
                    return NUMBER_ADDED;
                }else{
                    return ALLOCATION_ERROR;
                }
            }
        }
    }


    // if larger than all elements the insert this to end:
    if(insertBefore(s->list, elem) == OK){
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

setError removeElement(intSet* s, int elem)
{
    if (s == NULL || s->list == NULL) return ALLOCATION_ERROR;
    int currentData;

    gotoHead(s->list);
    while (gotoNextNode(s->list)== OK){
        if(getData(s->list, &currentData) == OK){
            if(currentData ==elem){

                // delete current node here
                if(dllDeleteCurrent(s->list) == OK){
                    s->count--;
                    return NUMBER_REMOVED;

                }
            }
            //BREAK earlt if we pass the number since the set is ordered
            if (currentData > elem){
                break;
            }
        }
    }
    return NUMBER_NOT_IN_SET;
}


/** compute intersection of s1 and s2
 *  @param s1 first set
 *  @param s2 second set
 *  @return new set contating intersecton or NULL on failure*/

intSet* setIntersection(intSet* s1, intSet* s2)
{
    intSet* result = createOrderSet();
    if(result == NULL) return NULL;
    if(s1 ==NULL || s2==NULL) return result;
    int val1, val2;

    gotoHead(s1->list);
    while (gotoNextNode(s1->list) == OK) {
        if (getData(s1->list, &val1) == OK) {
            gotoHead(s2->list);
            while (gotoNextNode(s2->list) == OK) {
                if (getData(s2->list, &val2) == OK) {
                    if (val1 == val2) {
                        addElement(result, val1);
                        break;
                    }
                    if (val2 > val1) break;
                }
            }
        }
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
intSet* setUnion(intSet* s1, intSet* s2)
{
    intSet* result = createOrderedSet();
    if (result == NULL) return NULL;
    if (s1 == NULL || s2 == NULL) return result;

    int val;

    gotoHead(s1->list);
    while (gotoNextNode(s1->list) == ok) {
        if (getData(s1->list, &val) == ok) addElement(result, val);
    }

    gotoHead(s2->list);
    while (gotoNextNode(s2->list) == ok) {
        if (getData(s2->list, &val) == ok) addElement(result, val);
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
intSet* setDifference(intSet* s1, intSet* s2)
{
    intSet* result = createOrderedSet();
    if (result == NULL) return NULL;
    if (s1 == NULL) return result;

    int val1, val2;
    int foundInS2;

    gotoHead(s1->list);
    while (gotoNextNode(s1->list) == OK) {
        if (getData(s1->list, &val1) == OK) {
            foundInS2 = 0;


            if (s2 != NULL) {
                gotoHead(s2->list);
                while (gotoNextNode(s2->list) == OK) {
                    if (getData(s2->list, &val2) == OK) {
                        if (val1 == val2) {
                            foundInS2 = 1;
                            break;
                        }
                        if (val2 > val1) break;
                    }
                }
            }
            if (!foundInS2) addElement(result, val1);
        }
    }
    return result;

}
/**
 * compute union of s1 and s2
 * @param s1 first set
 * @param s2 second set
 * @return new set conatining union, NULL on failure
 */

intSet* setUnion(intSet* s1, intSet* s2){
    intSet* result = createOrderSet();
    if(result==NULL) return NULL;
    if( s1==NULL || s2==NULL)return result;
    int val;

    gotoHead(s1->list);
    while(gotoNextNode(s1->list)==OK) {
        if(getData(s1->list, &val) == OK) addElement(result, val);

    }
    gotoHead(s2->list);
    while(gotoNextNode(s2->list)== OK){
        if(getData(s2->list, &val) == OK) addElement(result, val);

    }
    return result;
}

/**
 *  compute difference of s1 and s2
 *  @param s1 first set
 *  @param s2 second set
 *  @return new set containg difference, null on failure*/
int*
    
    intSet* setDifference(intSet* s1, intSet* s2)
{
    intSet* result= createOrderedSet();
    if(result ==NULL) return NULL;
    if(s1 ==NULL) return result;
    int val1, val2;
    int foundIns2;

    gotoHead(s1->list);
    while(gotoNextNode(s1->list) ==ok){
        if(getData(s1->list, &val1) == ok){
            foundInS2 = 0;

            if(s2 !=NULL){
                gotoHead(s2->list);
                while (gotoNextNode (s2->list)==ok){
                    if(getData(s2->list, &val2) ==ok){
                        if(val1 == val2){
                            foundInS2 = 1;
                            break;

                        }
                        if(val2>val1) break;
                    }
                }
            }
            if( !foundInS2) addElement(result, val1);
        }
    }
    return result;
}
/**
 * pritns the set in format{Num1..} to stdout
 * empty set is denoted{}
 * @param s pointer to valid set*/
void printToStdout(intSet*s){
    printf("{");
    if(s!= NULL && s->list != NULL){
        int val;
        int isFirst = 1;

        gotoHead(s->list);
        while(gotoNextNode(s->list) == OK){
            if(getData(s->list, &val) == OK){
                if(!isFirst) printf(", ");
                printf("%d", val);
                isFirst = 0;
            }
        }
    }
    printf("}");
}
