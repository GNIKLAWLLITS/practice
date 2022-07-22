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
 * 思路：推荐使用头结点的方法
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

/**
 * 第5题：试着编写算法将带头结点的单链表就地逆置，所谓”就地”就是辅助空间复杂度为O(1)
 * 
 * 思路：和线性表的顺序实现对比，如果要将数组的元素逆置，则需要交换元素。但是链表是通过
 *      指针来描述元素间的逻辑关系的，所以我们只需要修改指针即可。
 *                               reverse   
 *      L -> 1 -> 2 -> 3 -> NULL =======> NULL <- 1 <- 2 <- 3 <- L
 */

/**
 * @brief 逆置带头结点的单链表
 * 翻转前L是头结点，翻转后L也应该是头结点，所以我们可以用L指向翻转列表的表头元素，
 * 用p指向待翻转的结点，用r指向p的后继结点。翻转后的结点应该被插入翻转列表的表头，即L所指向的位置。
 * 
 * @param L 
 */
void reverseList1(LinkedList &L) {
    LNode *p=L->next, *r;
    L->next = NULL; // 将L指向翻转列表（此时列表没有任何元素，所以为NULL）
    while (p != NULL) {
        r = p->next;
        p->next = L->next;  // 这一行和下一行代表将p插入翻转列表的表头
        L->next = p;
        p = r;
    }
}

void test5() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    reverseList1(L);
    listPrint(L);
}

/**
 * 第6题：有一个带头结点的单链表L，设计一个算法使其元素递增有序
 * 
 * 思路：和第5题比较
 *      链表的插入排序
 */

void insertionSort(LinkedList &L) {
    LNode *p=L->next, *r;
    L->next = NULL; // 重点是这一步，先让L指向一个空的有序列表
    while (p != NULL) {
        r = p->next;
        LNode *prev=L, *temp=prev->next;
        while (temp!=NULL && temp->data<p->data) {
            prev = temp;
            temp = temp->next;
        }
        p->next = prev->next;
        prev->next = p;
        p = r;
    }
}

void test6() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    insertionSort(L);
    listPrint(L);
}

/**
 * 第7题：设在一个带表头结点的单链表中所有元素结点的数据值无序，试编写一个函数，
 *       删除表中所有介于给定的两个值(作为函数参数给出)之间的元素的元素(若存在)
 * 
 * 思路：和第5题比较，和顺序表的删除思想类似
 *      同样的想法，用L重新指向一个空的过滤列表，将满足条件的元素插入即可
 */

void deleteByInterval1(LinkedList &L, int min, int max) {
    LNode *p = L->next, *r;
    L->next = NULL;
    while (p != NULL) {
        r = p->next;
        if (p->data<min || max<p->data) {
            p->next = L->next;
            L->next = p;
        }
        p = r;
    }
}

void test7() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    deleteByInterval1(L, 5, 10);
    listPrint(L);
}

/**
 * 第8题：给定两个单链表，编写算法找出两个链表的公共结点
 *  
 * 思路：首先要区分公共结点和元素值相等的结点。每个结点都包含两部分：数据域和指针域
 *      - 公共结点是指两个链表都包含该结点，而这个结点只有一个指针域，因此从公共结点之后，
 *        两个链表是重合的
 *      - 元素值相等的结点就和好理解了，只要数据域相同，两个结点就是元素值相等的
 * 
 *      通过上述分析可知包含公共结点的链表应该具有重合部分：
 *      L1: * -> * -> * -> * -> * -> * -> * -> * -> * -> *
 *                          /
 *      L2:      * -> * -> * 
 *      
 *      通过上图还可以发现，不管两个链表长度是否一致，只要他们包含公共结点，那么他们从第一个
 *      公共结点到尾部一定是一致的。所以我们可以先从较长的列表开始遍历，直到它的剩余长度和较短
 *      的链表一致，再同时遍历两个链表，查找是否有公共结点。
 */     

LNode *findCommonNode(LinkedList L1, LinkedList L2) {
    int len1=length(L1), len2=length(L2);
    LNode *p1=L1->next, *p2=L2->next;

    // 统一长度
    int diff = len1-len2;
    while (diff < 0) {
        p2 = p2->next;
        diff++;
    }
    while (diff > 0) {
        p1 = p1->next;
        diff--;
    }

    while (p1!=NULL && p1!=p2) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p1;
}

void test8() {
    LNode *n1 = new LNode;
    n1->data = 1;
    LNode *n2 = new LNode;
    n2->data = 2;
    LNode *n3 = new LNode;
    n3->data = 3;
    LNode *n4 = new LNode;
    n4->data = 3;
    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;
    n4->next = NULL;

    LinkedList L1 = new LNode;
    L1->next = n1;
    listPrint(L1);

    LinkedList L2 = new LNode;
    L2->next = n4;
    listPrint(L2);

    LNode *commonNode=findCommonNode(L1, L2), *temp=commonNode;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/**
 * 第9题：给定一个带表头结点的单链表，设head为头指针，结点结构为(data, next)，data为整型元素，
 *       next为指针，试着写出算法：按递增次序输出单链表中各个结点的数据元素，并且释放结点所占的
 *       存储空间(要求：不允许使用数组作为辅助空间)
 * 
 * 思路：和第4题比较，实际是链表的选择排序，每次找到最小值结点，输出并删除
 *      也可以和第6题比较，先用插入排序使得链表有序，再依次删除
 */

/**
 * @brief 选择排序并删除
 * 依次输出链表的最小值元素并删除
 * 
 * @param L 
 */
void printInOrderASC(LinkedList &L) {
    LNode *prev, *p, *minp, *min;
    while (L->next!=NULL) {
        prev = minp = L;
        p = min = prev->next;
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
    delete L;
}

void test9() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    printInOrderASC(L);
    listPrint(L);
}



/* test */
int main() {
    test9();
}