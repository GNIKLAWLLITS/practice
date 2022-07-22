/** 
 * File: LinkedList.cpp
 * ---------------------------------
 * Using linked list implements sequential list.
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>

typedef int elemType;   // define element type

typedef struct LNode {
    elemType data;
    struct LNode *next;
} LNode, *LinkedList;

/* Basic operation */

/**
 * @brief 头插法建立单链表
 */
LinkedList headInsert(LinkedList &L) {
    LNode *n;       // 结点指针n，指向将来生成的新结点
    elemType e;

    L = new LNode;  // 头结点
    L->next = NULL;

    scanf("%d", &e);
    while (e != -1) {
        n = new LNode;
        n->data = e;
        
        n->next = L->next;
        L->next = n;

        scanf("%d", &e);
    }
    return L;
}

/**
 * @brief 尾插法建立单链表
 */
LinkedList tailInsert(LinkedList &L) {
    LNode *n;       // 结点指针n，指向将来生成的新结点
    elemType e;

    L = new LNode;  // 头结点
    L->next = NULL;

    LNode *tail;    // 尾指针，指向最后一个元素
    tail = L;

    scanf("%d", &e);
    while (e != -1) {
        n = new LNode;
        n->data = e;

        tail->next = n;
        tail = n;

        scanf("%d", &e);
    }
    tail->next = NULL;
    return L;
}

/**
 * @brief 判空操作
 */
bool isEmpty(LinkedList L) {
    return L->next==NULL;
}

/**
 * @brief 求表长操作，不包括头结点
 */
int length(LinkedList L) {
    int count = 0;
    LNode *temp = L;

    while (temp->next != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

/**
 * @brief 按位查找结点
 * 从第一个结点出发，查找链表中的第i个结点
 * 
 * @param L 
 * @param i i>=1
 * @return LNode* 如果找到则返回指向第i个结点的指针，否则返回NULL
 */
LNode *getElem(LinkedList L, int i) {
    LNode *temp = L;
    int count = 0;
    while (temp->next!=NULL && count<i-1) {
        temp = temp->next;
        count++;
    }
    return temp->next;
}

/**
 * @brief 按值查找结点
 * 从第一个结点出发，查找链表中值等于e的第一个结点
 * 
 * @param L 
 * @param e 目标值
 * @param count 查找次数
 * @return LNode* 如果找到则返回指向值等于e的第一个结点的指针，否则返回NULL
 */
LNode *locateElem(LinkedList L, elemType e, int &count) {
    LNode *temp = L->next;
    count = 1;
    while (temp!=NULL && temp->data!=e) {
        temp = temp->next;
        count++;
    }
    return temp;
}

/**
 * @brief 向后插入操作，在第i个位置插入元素
 * 可借用getElem()方法化简步骤
 * 
 * @param L 
 * @param e 
 * @param i 
 * @return LNode* 
 */
LNode* listInsert(LinkedList &L, elemType e, int i) {
    LNode *temp = getElem(L, i-1);  // 找到前驱结点
    if (temp != NULL) {
        LNode *n = new LNode;
        n->data = e;

        n->next = temp->next;
        temp->next = n;
    }
    return temp;
}

/**
 * @brief 删除第i个结点
 * 同样可以使用getElem()简化操作
 * 
 * @param L 
 * @param i i>=1
 * @return elemType 如果删除成功则返回被删除元素的值；如果删除失败则返回-1
 */
elemType listDelete(LinkedList &L, int i) {
    LNode *temp = getElem(L, i-1);  // 找到前驱结点
    elemType e;
    if (temp != NULL) {
        LNode *n = temp->next;      // 用n指向待删除元素
        if (n == NULL) {
            e = -1;
        } else {
            e = n->data;
        }
        temp->next = n->next;
        delete n;                   // 释放空间
    }
    return e;
}

/**
 * @brief 打印链表
 * 
 * @param L 
 */
void listPrint(LinkedList L) {
    if (isEmpty(L)) printf("List is empty!\n");
    LNode *temp = L->next;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

#endif
