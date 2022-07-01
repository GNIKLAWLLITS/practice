/** 
 * File: LinkedList.h
 * ---------------------------------
 * Using array implements static sequential list.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>

/* Max size of linked list */
#define MaxSize 10

typedef int elemType;   // define element type

typedef struct {
    elemType data[MaxSize];
    int length;
} LinkedList;

/* Basic operation */
void initialize(LinkedList &L) {
    L.length = 0;
}

void destroy(LinkedList &L) {}

bool isEmpty(LinkedList L) {
    return L.length==0;
}

/**
 * @brief Get the Elem object by index
 * 
 * @param L 
 * @param i 
 * @param e 
 * @return 1 if element exists; 0 if element doesn't exist
 */
int getElem(LinkedList L, int i, elemType &e) {
    if (i<1 || i>L.length) {
        printf("Index is illegal!\n");
        return 0;
    } else {
        e = L.data[i-1];
        return 1;
    }
}

/**
 * @brief return the index of first element that equals e
 * 
 * @param L 
 * @param e 
 * @return return valid index if find the target element, otherwise return 0
 */
int locateElem(LinkedList L, elemType e) {
    for (int i=0;i<L.length;i++) {
        if (L.data[i] == e) return i+1;
    }
    return 0;
}

bool insertElem(LinkedList &L, int i, elemType e) {
    if (i<1 || i>L.length+1) {
        printf("Index is illegal!\n");
        return false;
    }
    if (L.length >= MaxSize) {
        printf("Out of space!\n");
        return false;
    }
    for (int j=L.length;j>=i;j--) {
        L.data[j] = L.data[j-1];
    }
    L.data[i-1] = e;
    L.length++;
    return true;
}

bool deleteElem(LinkedList &L, int i, elemType &e) {
    if (i<1 || i>L.length) {
        printf("Index is illegal!\n");
        return false;
    }
    e = L.data[i-1];
    for (int j=i;j<L.length;j++) {
        L.data[j-1] = L.data[j];
    }
    L.length--;
    return true;
}

void printList(LinkedList L) {
    printf("list: ");
    for (int i=0;i<L.length;i++) {
        printf("%d ", L.data[i]);
    }
    printf("\n");
}

#endif
