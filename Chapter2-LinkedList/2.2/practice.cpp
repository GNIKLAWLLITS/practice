/** 
 * File: practice.cpp
 * ---------------------------------
 * Practice solution.
 */
#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList initTest() {
    LinkedList list;
    initialize(list);

    insertElem(list, 1, 13);
    insertElem(list, 1, 5);
    insertElem(list, 1, 7);
    insertElem(list, 1, 1);
    insertElem(list, 1, 2);
    
    printList(list);

    return list;
}

/**
 * 1.从顺序表中删除出具有最小值的元素（假设唯一），并由函数返回被删除元素的值，
 * 空出的位置由最后一个元素填补，若顺序表为空，则显示出错信息并退出运行
 */
bool deleteMin(LinkedList &L, elemType &e) {
    if (isEmpty(L)) {
        printf("Linked list is empty!\n");
        return false;
    }
    int min_pos = 0;
    for (int i=0;i<L.length;i++) {
        if (L.data[i] < L.data[min_pos]) {
            min_pos = i;
        }
    }
    e = L.data[min_pos];
    L.data[min_pos] = L.data[L.length-1];
    L.length--;
    return true;
}

void test1() {
    LinkedList list = initTest();
    elemType e;
    deleteMin(list, e);
    printList(list);
}

/**
 * 2.设计一个高效的算法，将顺序表L的所有元素逆置，要求算法空间复杂度为S(n)
 */
// S(n)
void reverseList(LinkedList &L) {
    LinkedList tempList;
    initialize(tempList);

    for (int i=0;i<L.length;i++) {
        insertElem(tempList, 1, L.data[i]);
    }
    L = tempList;
}

// S(1)
void reverseList1(LinkedList &L) {
    for (int i=0;i<L.length/2;i++) {
        elemType temp = L.data[i];
        L.data[i] = L.data[L.length-1-i];
        L.data[L.length-1-i] = temp;
    }
}

void test2() {
    LinkedList list = initTest();
    reverseList1(list);
    printList(list);
}

/**
 * 3.对长度为n的顺序表L，编写一个时间复杂度为O(n)，空间复杂度为S(1)的算法，
 * 该算法删除线性表种所有值为x的数据元素
 */
void deleteElem(LinkedList &L, elemType e) {
    int k = 0;
    for (int i=0;i<L.length;i++) {
        if (L.data[i] != e) {
            L.data[k++] = L.data[i];
        }
    }
    L.length = k;
}

void test3() {
    LinkedList list = initTest();
    deleteElem(list, 5);
    printList(list);
}

/**
 * 4.从有序顺序表中删除其值在给定值s与t之间（s<t) 的所有元素，
 * 若s或t不合理或者顺序表为空，则显示出错信息并退出运行
 */
bool deleteInterval(LinkedList &L, elemType s, elemType t) {
    if (isEmpty(L) || s>=t) {
        printf("List is empty or input is illegal!\n");
        return false;
    }
    int k = 0;
    for (int i=0;i<L.length;i++) {
        if (L.data[i]<s || L.data[i]>t) {
            L.data[k++] = L.data[i];
        }
    }
    L.length = k;
    return true;
}

void test4() {
    LinkedList list = initTest();
    if (deleteInterval(list, 4, 15)) {
        printList(list);
    }
}

/**
 * 5.从顺序表中删除其值在给定值s与t之间（包含s,t，要求s<t）的所有元素，
 * 若s或t不合理或者顺序表为空，则显示出错信息并退出运行
 */
// 参考第4题

/**
 * 6.从有序顺序表中删除所有其值重复的元素，使表中所有元素的值均不相同
 */
void deleteDuplicate(LinkedList &L) {
    if (isEmpty(L)) {
        return;
    }
    int k = 1;
    for (int i=1;i<L.length;i++) {
        if (L.data[i-1] == L.data[i]) {
            continue;
        } else {
            L.data[k++] = L.data[i];
        }
    }
    L.length = k;
}

void test6() {
    LinkedList list;
    initialize(list);
    insertElem(list, 1, 13);
    insertElem(list, 1, 7);
    insertElem(list, 1, 5);
    insertElem(list, 1, 2);
    insertElem(list, 1, 2);
    insertElem(list, 1, 2);
    insertElem(list, 1, 2);
    insertElem(list, 1, 1);
    printList(list);

    deleteDuplicate(list);
    printList(list);
}

int main() {
    test6();
}