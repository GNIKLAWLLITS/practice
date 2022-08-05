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

/**
 * 第10题：将一个带头结点的单链表A分解为两个带头结点的单链表A和B，使得A表中含有原表中序号为奇数的元素，
 *        而B表中含有原表中序号为偶数的元素，且保持其相对顺序不变
 * 
 * 思路：加计数器，遍历拆分，重点在于删除结点
 *      引入一个头结点LA，然后让LA也指向L的第一个元素，此时L和LA的所有结点都是公共的，我们只需要按序号拆分：
 *      - 如果序号为奇数，则将该元素保留在LA中，从L中删除该元素；
 *      - 如果序号为偶数，则将该元素保留在L中，从LA中删除该元素
 *      最后将L作为LB返回
 */

/**
 * @brief 将L按元素序号的奇偶性拆分成两个列表LA和LB，拆分后L本身将作为LB被返回
 * 
 * @param L 
 * @param LA 
 */
void splitList1(LinkedList &L, LinkedList &LA) {
    LNode *prev=L, *p=L->next, *pa=LA;
    int count = 1;
    while (p != NULL) {
        prev->next = p->next;
        if (count%2 == 1) {
            pa->next = p;
            pa = p;
        }
        prev = p;
        p = p->next;
        count++;
    }
}

void test10() {
    LinkedList L;
    L = tailInsert(L);
    printf("before: ");
    listPrint(L);

    LNode* LA = new LNode;
    LA->next = NULL;

    splitList1(L, LA);
    printf("after: ");
    listPrint(L);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(L);
}

/**
 * 第11题：设C={a1,b1,a2,b2,...,an,bn}为线性表，采用带头结点的单链表存放，设计一个原地算法，
 *        将其拆分为两个线性表，使得A={a1,a2,...,an}，B={bn,...,b2,b1}
 * 
 * 思路：参考第10题，可以先拆分为LA和LB，然后将LB逆置即可。也可以在拆分的过程中逆置
 *      TODO: 待补充
 */

void splitList2(LinkedList &L, LinkedList &LA, LinkedList &LB) {
    
}

void test11() {
    LinkedList L;
    L = tailInsert(L);
    printf("before: ");
    listPrint(L);

    LNode* LA = new LNode;
    LA->next = NULL;
    LNode* LB = new LNode;
    LB->next = NULL;

    splitList2(L, LA, LB);
    printf("after: ");
    listPrint(L);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(LB);
}

/**
 * 第12题：在一个递增有序的线性表中，有数值相同的元素存在。若存储方式为单链表，设计算法去掉数值相同的元素，
 *        使得表中不再有重复的元素，例如{7,10,10,21,30,42,42,42,51,70}将其变为{7,10,21,30,42,51,70}
 * 
 * 思路：和第7题比较，也是删除指定类型的元素
 */

void deleteDuplicate1(LinkedList &L) {
    LNode *p=L->next;
    L->next = NULL;
    LNode *r = L->next;
    while (p != NULL) {
        if (r == NULL) {
            r = p;
            L->next = r;
        }
        if (r->data != p->data) {
            r->next = p;
            r = p;
        }
        p = p->next;
    }
}

void test12() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    deleteDuplicate1(L);
    listPrint(L);
}

/**
 * 第13题：假设有两个按元素值递增次序排列的线性表，均以单链表形式存储，请编写算法将这两个单链表归并为
 *        一个按元素值递减次序排列的单链表，并要求利用原来的两个单链表的结点存放归并后的单链表
 * 
 * 思路：和第10题比较，第10题是将一个单链表拆分为两个单链表（且仍使用原来的结点），此题是将两个单链表合并为一个单链表（且仍使用原来的结点）
 *      要求合并后的链表递减排序，因此使用头插法
 */

/**
 * @brief 将LA和LB合并，仍使用原来的结点
 * 
 * @param LA 
 * @param LB 
 * @return LNode* 
 */
LNode* mergeList(LinkedList &LA, LinkedList &LB) {
    LNode *pa=LA->next, *pb=LB->next;
    LNode *result = new LNode;
    result->next = NULL;
    while (pa!=NULL && pb!=NULL) {
        if (pa->data < pb->data) {
            LA->next = pa->next;
            pa->next = result->next;
            result->next = pa;
            pa = LA->next;
        } else {
            LB->next = pb->next;
            pb->next = result->next;
            result->next = pb;
            pb = LB->next;
        }
    }

    while (pa != NULL) {
        LA->next = pa->next;
        pa->next = result->next;
        result->next = pa;
        pa = LA->next;
    }
    while (pb != NULL) {
        LB->next = pb->next;
        pb->next = result->next;
        result->next = pb;
        pb = LB->next;
    }

    return result;
}

void test13() {
    LNode *LA;
    LA = tailInsert(LA);
    LNode *LB;
    LB = tailInsert(LB);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(LB);

    LNode *result = mergeList(LA, LB);
    printf("result: ");
    listPrint(result);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(LB);
}

/**
 * 第14题：设A和B是两个单链表(带头结点)，其中元素递增有序。设计一个算法从A和B中的公共元素产生单链表C，要求不破坏A,B的结点
 * 
 * 思路：双指针遍历
 */

LNode* generateCommonList1(LinkedList LA, LinkedList LB) {
    LNode *pa=LA->next, *pb=LB->next;
    LNode *res = new LNode;
    res->next = NULL;
    while (pa!=NULL && pb!=NULL) {
        if (pa->data < pb->data) {
            pa = pa->next;
        } else if (pb->data < pa->data) {
            pb = pb->next;
        } else {
            LNode *n = new LNode;
            n->data = pa->data;
            n->next = res->next;
            res->next = n;
            pa = pa->next;
            pb = pb->next;
        }
    }
    return res;
}

void test14() {
    LNode *LA;
    LA = tailInsert(LA);
    LNode *LB;
    LB = tailInsert(LB);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(LB);

    LNode *result = generateCommonList1(LA, LB);
    printf("result: ");
    listPrint(result);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(LB);
}

/**
 * 第15题：已知两个链表A和B分别表示两个集合，其元素递增排列。编制函数，求A与B的交集，并存放于A链表中
 * 
 * 思路：和第14题比较，14题是返回新的结点和新链表，此题是使用原来的结点
 */

void generateCommonList2(LinkedList &LA, LinkedList &LB) {
    LNode *pa=LA->next, *pb=LB->next;
    LA->next = NULL;
    while (pa!=NULL && pb!=NULL) {
        if (pa->data < pb->data) {
            pa = pa->next;
        } else if (pb->data < pa->data) {
            pb = pb->next;
        } else {
            LNode *r = pa->next;
            pa->next = LA->next;
            LA->next = pa;
            pa = r;
            pb = pb->next;
        }
    }
}

void test15() {
    LNode *LA;
    LA = tailInsert(LA);
    LNode *LB;
    LB = tailInsert(LB);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(LB);

    generateCommonList2(LA, LB);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(LB);
}

/**
 * 第16题：两个整数序列A=a1,a2,...,am，B=b1,b2,...,bn。已经存入两个单链表中，设计一个算法，判断序列B是否是序列A的连续子序列
 * 
 * 思路：类比字符串的模式匹配，蛮力法
 */

bool isSubSeq1(LinkedList LA, LinkedList LB) {
    LNode *prev=LA->next, *pa=prev, *pb=LB->next;
    while (pa!=NULL && pb!=NULL) {
        if (pa->data == pb->data) {
            pa = pa->next;
            pb = pb->next;
        }
        else {
            prev = prev->next;
            pa = prev;
            pb = LB->next;
        }
    }
    if (pb == NULL) {
        return true;    
    }
    return false;
}

void test16() {
    LNode *LA;
    LA = tailInsert(LA);
    LNode *LB;
    LB = tailInsert(LB);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(LB);

    if (isSubSeq1(LA, LB)) {
        printf("LB is a sub-sequence of LA");
    } else {
        printf("LB is not a sub-sequence of LA");
    }
}


/**
 * 第17题：设计一个算法用于判断带头结点的循环双链表是否对称
 * 
 * 思路：（实现暂时跳过）
 *      循环双链表的结构如下图所示
 *              
 *                  head->prev
 *             -------------------|
 *             |                  v
 *      L -> head <-> 1 <-> 2 <-> 1  
 *             ^                  |
 *             |-------------------
 * 
 *      因此可以从head出发，一个指针向prev方向移动，一个指针向next方向移动，比较他们的元素值是否相等
 */      

/**
 * 第18题：有两个循环单链表，链表头指针分别为h1和h2，编写一个函数将链表h2链接到链表h1之后，要求链接后的链表仍保持循环链表形式
 * 
 * 思路：图解如下
 *      
 *      h1 -> e1 -> e2 -|
 *      ^               |
 *      |----------------
 * 
 *      h2 -> e3 -> e4 -|
 *      ^               |
 *      |----------------
 * 
 *      首先遍历到h1的末尾，然后让e2->next = e3，然后遍历到h2的末尾，e4->next = h1
 */

void concat1(LinkedList &LA, LinkedList &LB) {
    LNode *ra=LA, *rb=LB;
    while (ra->next != NULL) {
        ra = ra->next;
    }
    while (rb->next != NULL) {
        rb = rb->next;
    }
    if (rb != LB) {
        rb->next = LA;
        ra->next = LB->next;
    }
}

void test18() {
    LNode *LA;
    LA = tailInsert(LA);
    LNode *LB;
    LB = tailInsert(LB);
    printf("LA: ");
    listPrint(LA);
    printf("LB: ");
    listPrint(LB);

    concat1(LA, LB);
    printf("LA: ");
    LNode *temp = LA->next;
    while (temp != LA) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

/**
 * 第19题：设有一个带头结点的循环单链表，其结点值均为正整数。设计一个算法，反复找出单链表中结点值最小的结点并输出，
 *        然后将该结点从中删除，直到单链表空为止，再删除表头结点
 * 
 * 思路：循环遍历
 */

void deleteMin3(LinkedList &L) {
    while (L->next != L) {
        LNode *prev=L, *p=L->next;
        LNode *minp = prev;
        int min = p->data;
        while (p != L) {
            prev = p;
            p = p->next;
            if (p!=L && p->data<min) {
                min = p->data;
                minp = prev;
            }
        }
        LNode *temp = minp->next;
        minp->next = temp->next;
        printf("%d ", temp->data);
        delete temp;
    }
    delete L;
}

void test19() {
    LinkedList L;
    L = tailInsert(L);
    LNode *temp = L->next;
    while (true) {
        printf("%d ", temp->data);
        if (temp->next == NULL) {
            temp->next = L;
            break;
        }
        temp = temp->next;
    }
    printf("\n");

    printf("delete min: ");
    deleteMin3(L);
}

/**
 * 第20题：设头指针为L的带有表头结点的非循环双向链表，其每个结点中除有pred(前驱指针)、data (数据)和next (后继指针)域外，
 *        还有一个访问频度域freq。在链表被启用前，其值均初始化为零。每当在链表中进行一-次Locate(L,x)运算时，令元素值为x
 *        的结点中freq域的值增1,并使此链表中结点保持按访问频度非增(递减)的顺序排列，同时最近访问的结点排在频度相同的结点
 *        前面，以便使频繁访问的结点总是靠近表头。试编写符合上述要求的Locate (L,x)运算的算法，该运算为函数过程，返回找到
 *        结点的地址，类型为指针型
 * 
 * 思路：TODO: 待补充
 */

/**
 * 第21题：单链表有环，是指单链表的最后一个结点的指针指向了链表中的某个结点(通常单链表的最后一个结点的指针域是空的)。
 *        试编写算法判断单链表是否存在环
 * 
 * 思路：快慢指针，快指针每次走两步，慢指针每次走一步，如果快指针不为NULL且等于慢指针，则说明有环
 * 
 *                        -------e5
 *                        |      ^ 
 *                        v      |
 *      L -> e1 -> e2 -> e3      | 
 *                        |      |
 *                        -----> e4     
 */

bool isLoop1(LinkedList L) {
    LNode *fast=L->next, *slow=L;
    while (fast!=NULL && fast->next!=NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) {
            return true;
        }
    }
    return false;
}

void test21() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);

    // 加环
    LNode *temp = L;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = L->next;

    if (isLoop1(L)) {
        printf("There is a loop in linked list\n");
    } else {
        printf("There is no loop in linked list\n");
    }

}

/**
 * 第22题：已知一个带有表头结点的单链表。假设该链表只给出了头指针list. 在不改变链表的前提下，请设计一个尽可能高效的算法，
 *        查找链表中倒数第k个位置上的结点(k为正整数)。若查找成功，算法输出该结点的data域的值，并返回1；否则，只返回0
 * 
 * 思路：定义两个指针变量p和q，初始时均指向头结点的下一结点，p指针沿着链表移动，当p指针移动到正数第k个结点时，q指针开始和
 *      p指针同步移动，当p指针移动到最后一个结点时，q指针就指向倒数第k个结点。
 *      
 *      以k=3为例：
 * 
 *           q           p                                                                   q                 p
 *           |           |                                                                   |                 |
 *           v           v                                                                   v                 v
 *      L -> e1 -> e2 -> e3 -> e4 -> ... -> e(n-1) -> en ======> L -> e1 -> e2 -> e3 -> ...e(n-2) -> e(n-1) -> en
 */

int findKthLastElem1(LinkedList L, int k) {
    LNode *p=L->next, *q=p;
    int count = 1;
    while (p!=NULL && p->next!=NULL) {
        p = p->next;
        if (count > k) {
            q = q->next;
        }
        count++;
    }
    if (count < k) {
        return 0;
    }
    printf("%d ", q->data);
    return 1;
}

void test22() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    int k = 4;
    if (findKthLastElem1(L, k)) {
        printf("is the %dth last element\n", k);
    } else {
        printf("can't find the %dth last element", k);
    }
}

/**
 * 第23题：假定采用带头结点的单链表保存单词，当两个单词有相同的后缀时，可共享相同的后缀存储空间，例如，"loading" 和"being" 的存储映像如下图所示
 *        
 *        str1 -> l -> o -> a -> d -\
 *                                   -------> i -> n -> g
 *        str2 -> b -> e -----------/
 *        
 *        设str1和str2分别指向两个单词所在单链表的头结点，链表结点结构为data，next。请设计一个时间上尽可能高效的算法，
 *        找出由str1和str2所指向两个链表共同后的起始位置（如图中字符i所在结点）
 * 
 * 思路：和第8题一致
 */

/**
 * 第24题：用单链表保存m个整数，结点的结构为[data][link], 且|data|<n（n为正整数）。现要求设计一个时间复杂度尽可能高效的算法，
 *        对于链表中data的绝对值相等的结点，仅保留第一次出现的结点而删除其余绝对值相等的结点
 * 
 * 思路：和第12题比较，最主要的区别是此题并不保证元素有序
 *      注意到|data|一定会小于n，因此可以使用长度为n的数组来记录值是否存在（计数排序）
 */

void deleteSameAbsValue(LinkedList &L, int n) {
    int count[n] = {0};
    LNode *prev=L, *p=L->next;
    while (p != NULL) {
        if (count[abs(p->data)] == 0) {
            count[abs(p->data)] = 1;
            prev = p;
            p = p->next;
        } else {
            prev->next = p->next;
            LNode *temp = p;
            p = p->next;
            delete temp;
        }
    }
}

void test24() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    deleteSameAbsValue(L, 6);
    listPrint(L);
}

/**
 * 第25题：设线性表L=(a1,a2,a3,...,an-2,an-1,an)，采用带头结点的单链表保存。设计算法，重新排列L中的结点，得到线性表L'=(a1,an,a2,an-1,a3,an-2,...)
 * 
 * 思路：逆置+穿插
 *      分析可发现
 *                                                                          重排列
 *      L -> a1 -> a2 -> ... -> a(n/2) -> a(n/2+1) -> ... -> a(n-1) -> an =========> L -> a1 -> an -> a2 -> a(n-1) -> ... -> a(n/2+1)
 *      
 *      1.重排列的过程实际上就是先取队首元素，再取队尾元素
 *      2.重排列后队尾元素一定是a(n/2+1)
 *      
 *      因此可以先使用快慢指针找到中间结点，再将重排列过程看作是将a(n/2+1)之后的元素先逆置，再穿插
 * 
 *      TODO: 错误，待修改
 */

void rearrange1(LinkedList &L) {

    // 1.快慢指针找中间结点
    LNode *fast=L->next, *slow=fast;
    while (fast!=NULL && fast->next!=NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }
    if (slow==NULL || slow->next==NULL) {
        return;
    }

    // 2.逆置后半段链表
    LNode *prev=slow, *p=prev->next, *r;
    while (p != NULL) {
        r = p->next;
        p->next = prev;
        prev = p;
        p = r;
    }
    slow->next->next = NULL;
    slow->next = prev;

    // 3.穿插
    fast = L->next; // 重新利用fast
    while (p != NULL) {
        p = slow->next;
        slow->next = p->next;
        p->next = fast->next;
        fast->next = p;
    }
}

void test25() {
    LinkedList L;
    L = tailInsert(L);
    listPrint(L);
    rearrange1(L);
    listPrint(L);
}

/* test */
int main() {
    test25();
}