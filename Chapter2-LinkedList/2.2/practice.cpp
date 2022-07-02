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

/* tool function */
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

void reverse(elemType arr[], int left, int size) {
    for (int i=0;i<size/2;i++) {
        elemType temp = arr[i+left];
        arr[i+left] = arr[size-i-1+left];
        arr[size-i-1+left] = temp;
    }
}

/* practice */
/**
 * 题目1：从顺序表中删除出具有最小值的元素(假设唯一)，并由函数返回被删除元素的值，
 *       空出的位置由最后一个元素填补，若顺序表为空，则显示出错信息并退出运行
 * 
 * 思路：遍历顺序表找出最小值即可(删除后不要忘记更新顺序表长度)
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
 * 题目2：设计一个高效的算法，将顺序表L的所有元素逆置，要求算法空间复杂度为S(1)
 * 
 * 思路：遍历前半个顺序表，将根据顺序表中心对称的两个元素交换位置
 */
void reverseList(LinkedList &L) {
    for (int i=0;i<L.length/2;i++) {
        elemType temp = L.data[i];
        L.data[i] = L.data[L.length-1-i];
        L.data[L.length-1-i] = temp;
    }
}

void test2() {
    LinkedList list = initTest();
    reverseList(list);
    printList(list);
}

/**
 * 题目3：对长度为n的顺序表L，编写一个时间复杂度为O(n)，空间复杂度为S(1)的算法，
 *       该算法删除线性表种所有值为x的数据元素
 * 
 * 思路：基本思想是只统计有效下标，并将指定元素都交换到表尾，更新顺序表长度来实现"删除"
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
 * 题目4：从有序顺序表中删除其值在给定值s与t之间(s<t)的所有元素，
 *       若s或t不合理或者顺序表为空，则显示出错信息并退出运行
 * 
 * 思路：基本思路参考第3题
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
 * 题目5：从顺序表中删除其值在给定值s与t之间(包含s,t，要求s<t)的所有元素，
 *       若s或t不合理或者顺序表为空，则显示出错信息并退出运行
 * 
 * 思路：基本思路参考第3题，解决方法和第4题相同
 */

/**
 * 题目6：从有序顺序表中删除所有其值重复的元素，使表中所有元素的值均不相同
 * 
 * 思路：基本思路参考第3题
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

/**
 * 题目7：将两个有序顺序表合并为一个新的有序顺序表，并由函数返回结果顺序表 
 * 
 * 思路：常见的合并思路，使用两个指针分别从头遍历两个顺序表，挑选较小的元素加入结果顺序表中，
 *      一旦其中一个顺序表已经结束遍历，将另一顺序表中的所有元素全部加入结果顺序表
 */
void mergeList(LinkedList L1, LinkedList L2, LinkedList &L3) {
    initialize(L3);
    int i = 0;
    int j = 0;
    while (i<L1.length && j<L2.length) {
        elemType e;
        if (L1.data[i] < L2.data[j]) {
            e = L1.data[i];
            i++;
        } else {
            e = L2.data[j];
            j++;
        }
        insertElem(L3, L3.length+1, e);
    }
    if (i < L1.length) {
        while (i < L1.length) {
            insertElem(L3, L3.length+1, L1.data[i++]);
        }
    }
    if (j < L2.length) {
        while (j < L2.length) {
            insertElem(L3, L3.length+1, L2.data[j++]);
        }
    }
}

void test7() {
    LinkedList L1;
    initialize(L1);
    insertElem(L1, 1, 7);
    insertElem(L1, 1, 3);
    insertElem(L1, 1, 1);
    printList(L1);

    LinkedList L2;
    initialize(L2);
    insertElem(L2, 1, 9);
    insertElem(L2, 1, 5);
    insertElem(L2, 1, 4);
    insertElem(L2, 1, 2);
    printList(L2);

    LinkedList L3;
    mergeList(L1, L2, L3);
    printList(L3);
    printf("length of L3: %d\n", L3.length);
}

/**
 * 题目8：已知在一维数组A[m+n]中依次存放两个线性表(a1,a2,a3~am)和(b1,b2,b3~bn)。
 *       编写一个函数，将数组中两个顺序表的位置互换，即将(b1,b2,b3~bn)放在(a1,a2,a3~an)前面
 * 
 * 思路：基本思路是逆置。两个子表需要交换位置时，可以依次将子表的元素逆置，然后将数组逆置
 */
void reverseList2(elemType arr[], int m, int n) {
    reverse(arr, 0, m);     // 逆置线性表(a1,a2,a3~am)
    reverse(arr, m, n);     // 逆置线性表(b1,b2,b3~bn)
    reverse(arr, 0, m+n);   // 逆置数组A[m+n]
}

void test8() {
    elemType arr[] = {1,2,3,4,5,6,7,8};
    reverseList2(arr, 5, 3);
    for (elemType e : arr) {
        printf("%d ", e);
    }
}

/**
 * 题目9：线性表(a1,a2,a3~an)中的元素递增有序且按顺序存储与计算机内，
 *       要求设计一个算法，完成用最少时间在表中查找数值为x的元素，并将其与后继元素位置交换
 * 
 * 思路：线性表有序，查找可使用二分查找
 */
bool findAndExchange(LinkedList &L, elemType x) {
    if (x < L.data[0] || x > L.data[L.length-1]) {
        return false;
    }
    int left = 0;
    int right = L.length-1;
    int mid;
    while (left <= right) {
        mid = (right-left)/2+left;
        if (L.data[mid] == x) {
            if (mid < L.length-1) {
                elemType temp = L.data[mid];
                L.data[mid] = L.data[mid+1];
                L.data[mid+1] = temp;
            }
            return true;
        }
        if (L.data[mid] < x) {
            left = mid+1;
        }
        if (L.data[mid] > x) {
            right = mid-1;
        }
    }
    return false;
}

void test9() {
    LinkedList L;
    initialize(L);
    insertElem(L, 1, 7);
    insertElem(L, 1, 5);
    insertElem(L, 1, 3);
    insertElem(L, 1, 2);
    insertElem(L, 1, 1);

    if (findAndExchange(L, 7)) {
        printf("successed\n");   
        printList(L);
    } else {
        printf("failed\n");
    }
}

/**
 * 题目10：设将n(n>1)个整数存到一维数组R中。设计一个在时间和空间两方面都尽可能高效的算法。
 *        将R中保存的序列循环左移p(0<p<n)个位置，即将R中的数据由(X0,X1,~,Xn-1)变换为
 *        (Xp,Xp+1,~,Xn-1,X0,X1,~,Xp-1)
 * 
 * 思路：本题其实和第八题是同一个问题，解法同第8题，循环移动可看成是将两个独立的子表交换位置
 *      原数组: [[X(0)~X(p-1)], [X(p)~X(n-1)]] -> 交换后数组: [[X(p)~X(n-1)], [X(0)~X(p-1)]]
 */

/**
 * 题目11：一个长度为L(L>=1)的升序序列S，处在第(L/2)(向上取整)个位置的数称为S的中位数，
 *        两个序列的中位数是含它们所有元素的升序序列的中位数。现在有两个等长升序序列A和B，
 *        试设计一个在时间和空间两方面都尽可能高效的算法，找出两个序列A和B的中位数
 * 
 * 思路：知道两个序列的长度，就知道了中位数的位置(下标)。使用两个指针分别从头遍历两个升序序列，
 *      每移动一次都对计数器加一，当计数器等于中位数下标时，两个指针指向的元素中更小的那个就是中位数。
 *      假设列表的长度都是n，时间复杂度为O(n)，空间复杂度为O(1)
 */
int findMedian(LinkedList L1, LinkedList L2) {
    int target = (L1.length+L2.length)/2-1;   // 获取中位数的下标
    int count = 0;
    int i = 0;
    int j = 0;
    while (count < target) {
        if (L1.data[i] < L2.data[j]) {
            i++;
        } else {
            j++;
        }
        count++;
    }
    return L1.data[i]<L2.data[j] ? L1.data[i] : L2.data[j];
}

void test11() {
    LinkedList L1;
    initialize(L1);
    insertElem(L1, 1, 7);
    insertElem(L1, 1, 5);
    insertElem(L1, 1, 2);

    LinkedList L2;
    initialize(L2);
    insertElem(L2, 1, 9);
    insertElem(L2, 1, 4);
    insertElem(L2, 1, 1);

    int median = findMedian(L1, L2);
    printf("median is %d\n", median);
}

/**
 * 题目12：已知一个整数序列A=(a0,a1,...,a(n-1))，其中0<=ai<n(0<=i<n)。
 *        若存在a(p1)=a(p2)=...=a(pm)=x且m>n/2(0<=pk<n, 1<=k<=m)，
 *        则称x为A的主元素，如果没有满足的数，则A没有主元素。假设A中的n个元素
 *        保存在一个一维数组中，请设计一个尽可能高效的算法，找出A的主元素。
 *        若存在主元素，则输出该元素；否则输出-1
 * 
 * 思路：需要注意该整数序列的值都小于其长度，这是计数排序的典型特征——数组元素的值都在固定范围内，且元素必须为整数。
 *      该问题本质上就是查找数组中是否有出现次数超过数组长度一半的元素。可新建一个长度等于A的计数数组，
 *      将其每个元素初始化为0。遍历序列A，A中的元素每出现一次，都对计数数组中下标等于该元素的元素加一。
 *      (计数数组中的下标对应A中的元素，而位于该下标的元素对应A中元素的出现次数)
 *      时间复杂度为O(n)，空间复杂度为S(n)
 */
int findPivot(LinkedList L) {
    if (isEmpty(L)) return -1;
    int arr[L.length];
    for (int i=0;i<L.length;i++) {
        arr[i] = 0; // 将数组元素初始化为0
    }
    for (int i=0;i<L.length;i++) {
        arr[L.data[i]]++;   // 计数
    }
    int pivot = -1;
    for (int i=0;i<L.length;i++) {
        if (arr[i] > L.length/2) pivot = i;
    }
    return pivot;
}

void test12() {
    LinkedList list;
    initialize(list);
    insertElem(list, 1, 1);
    insertElem(list, 1, 1);
    insertElem(list, 1, 2);
    insertElem(list, 1, 3);
    insertElem(list, 1, 2);
    printList(list);

    int pivot = findPivot(list);
    if (pivot == -1) {
        printf("pivot doesn't exist!\n");
    } else {
        printf("pivot is %d\n", pivot);
    }
}

/**
 * 题目13：给定一个含n(n>=1)个整数的数组，请设计一个在时间上尽可能高效的算法，找出数组中未出现的最小正整数。
 * 
 * 思路：对于含n个整数的数组来说，未出现的最小正整数的值的范围只能是[1, n+1]。因此很明显可使用计数排序。
 *      时间复杂度为O(n)，空间复杂度为S(n)
 *      
 */
int findMissMin(LinkedList L) {
    int arr[L.length+1];
    for (int i=0;i<L.length+1;i++) {
        arr[i] = 0; // 初始化计数数组
    }
    for (int i=0;i<L.length;i++) {
        if (0<L.data[i] && L.data[i]<=L.length) {
            arr[L.data[i]]++;   // 当元素处于[0, n]之间才计数
        }
    }
    for (int i=1;i<L.length+1;i++) {
        if (arr[i] == 0) return i;
    }
    return L.length+1;
}

void test13() {
    LinkedList list;
    initialize(list);
    insertElem(list, 1, -1);
    insertElem(list, 1, 1);
    insertElem(list, 1, 2);
    insertElem(list, 1, 3);
    insertElem(list, 1, 9);
    printList(list);

    int miss_min = findMissMin(list);
    printf("the missed min is %d\n", miss_min);
}

/**
 * 题目14：定义三元组(a,b,c)(a、b、c均为正数)的距离D=|a-b|+|b-c|+|c-a|。给定3个非空整数集合S1、S2和S3，
 *        按升序分别存储在3个数组中。请设计一个尽可能高效的算法，计算并输出所有可能的三元组(a,b,c)中的最小距离。
 * 
 * 思路：由D的计算公式知，当a<=b<=c时，D实际上只和a与c的值有关。
 *          |<-          l3         ->|
 *          ---------------------------    
 *          |<-   l1   ->|<-   l2   ->|
 *          a            b            c
 *      D = l1+l2+l3 = 2*l3 = 2*|a-c|
 *      因此，将最小值(此处用a表示)增大，就可以缩小D。换句话说，每一次都寻找最小值所在的集合，然后用该集合的下一位
 *      元素代替这个最小值即可。
 *      假设n=|S1|+|S2|+|S3|, 时间复杂度O(n)，空间复杂度为S(1)
 */
int findMinDist(LinkedList L1, LinkedList L2, LinkedList L3) {
    int i=0, j=0, k=0, d_min=INT_MAX, d;
    while (i<L1.length && j<L2.length && k<L3.length) {
        // 计算距离
        int a=L1.data[i], b=L2.data[j], c=L3.data[k];
        d = abs(a-b) + abs(b-c) + abs(c-a);
        if (d < d_min) d_min = d;

        // 找到最小值所在的集合，并用下一位元素代替该最小值
        if (a<=b && a<=c) i++;
        else if (b<=a && b<=c) j++;
        else if (c<=a && c<=b) k++;
    }
    return d_min;
}

void test14() {
    LinkedList L1;
    initialize(L1);
    insertElem(L1, 1, 9);
    insertElem(L1, 1, 0);
    insertElem(L1, 1, -1);
    printList(L1);

    LinkedList L2;
    initialize(L2);
    insertElem(L2, 1, 11);
    insertElem(L2, 1, 10);
    insertElem(L2, 1, -10);
    insertElem(L2, 1, -25);
    printList(L2);

    LinkedList L3;
    initialize(L3);
    insertElem(L3, 1, 41);
    insertElem(L3, 1, 30);
    insertElem(L3, 1, 17);
    insertElem(L3, 1, 9);
    insertElem(L3, 1, 2);
    printList(L3);

    int d_min = findMinDist(L1, L2, L3);
    printf("min distance is %d\n", d_min);
}

/* test */
int main() {
    test14();
}