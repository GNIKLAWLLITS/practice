/** 
 * File: practice.cpp
 * ---------------------------------
 * Practice solution.
 */
#include "LinkedList.h"
#include <iostream>
#include <cmath>
#include <climits>
using namespace std;


/* practice */
/**
 * 第1题：设计一个递归算法，删除不带头结点的单链表L中所有值为x的结点
 * 
 * 思路：不带头结点的单链表不需要单独处理头结点，因此适合用递归。重点在递归时传入正确的指针
 */

void deleteByValue1(LinkedList &L, elemType x) {
    LNode* temp = L;
    if (temp == NULL) {
        return;
    }
    if (temp->data == x) {
        L = L->next;
        delete temp;
        deleteByValue1(L, x);
    } else {
        deleteByValue1(L->next, x);
    }
}

void test1() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    deleteByValue1(L, 1);
    listPrint(L);
}

/**
 * 第2题：在带头结点的单链表L中，删除所有值为x的结点，并释放其空间，假设值为x的结点不唯一
 * 
 * 思路：和第1题比较。
 *      带头结点，所以需要单独处理头结点，剩下的结点用循环处理
 */

void deleteByValue2(LinkedList &L, elemType x) {
    LNode* temp = L;
    while (temp->next != NULL) {
        LNode *n = temp->next;
        if (n->data == x) {
            temp->next = n->next;
            delete n;
        } else {
            temp = n;
        }
    }
}

void test2() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    deleteByValue2(L, 1);
    listPrint(L);
}

/**
 * 第3题：设L为带头结点的单链表，编写算法实现从尾到头反向输出每个结点的值
 * 
 * 思路：和第1题比较。
 *      借用递归的特点，先将元素依次入栈遍历到表尾，然后依次出栈输出即可。
 *      但是第一题中提到递归不好处理带头结点的链表，因此可以特殊处理一下，将L->next输入递归函数
 */

void reversePrint1(LinkedList L) {
    if (L->next != NULL) reversePrint1(L->next);
    printf("%d ", L->data);
}

void reversePrintIgnoreHead1(LinkedList L) {
    if (L != NULL) reversePrint1(L->next);
}

void test3() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    reversePrintIgnoreHead1(L);
    printf("\n");
}

/**
 * 第4题：编写在带头结点的单链表L中删除一个最小值结点的高效算法（假设最小值结点是唯一的）
 * 
 * 思路：
 */

/**
 * 不使用头结点
 * 用min指向最小值结点，删除时将后继结点的值赋予min，然后删除后继结点
 * 
 * 缺点是需要单独处理没有结点和只有1个结点的情况
 */
void deleteMin1(LinkedList &L) {
    LNode *temp=L->next, *min=temp;
    
    // 没有结点
    if (temp == NULL) { 
        return;
    }
    // 只有1个结点
    if (temp->next == NULL) {   
        L->next = NULL;
        delete temp;
        return;
    }
    // 大于等于2个结点
    while (temp->next != NULL) {
        if (temp->data < min->data) {
            min = temp;
        }
        temp = temp->next;
    }
    temp = min->next;   // 重复利用temp，让temp指向min的后继结点
    min->data = temp->data;
    min->next = temp->next;
    delete temp;
}

/**
 * 使用头结点
 * 用minp指向最小值结点的前驱结点，min指向最小值结点
 * 
 * 缺点是需要使用较多的指针，但是可以让逻辑更清晰，并且使用上头结点可以少判断一些特殊情况
 */
void deleteMin2(LinkedList &L) {
    LNode *prev=L, *p=prev->next;
    LNode *minp=prev, *min=p;
    while (p != NULL) {
        if (p->data < min->data) {
            min = p;
            minp = prev;
        }
        prev = p;
        p = p->next;
    }
    if (min != NULL) {
        minp->next = min->next;
    }
    delete min;
}

void test4() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    deleteMin2(L);
    listPrint(L);
}

/* test */
int main() {
    test4();
}