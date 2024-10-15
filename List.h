#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

#include <stdio.h>
#include <stdlib.h>

typedef struct ListObj* List;

//Constructor
List newList(void);

//Destructor
void freeList(List* pL);

//Access Function (Getter)
int length(List L);
int index(List L);
long front(List L);
long back(List L);
long get(List L);
//int equals(List A, List B);

//Manipulation procedures (Setter)
void clear(List L);
void set(List L, long x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, long data);
void append(List L, long data);
void insertBefore(List L, long data);
void insertAfter(List L, long data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other operations 
void printList(FILE* out, List L);
List copyList(List L);

#endif 
