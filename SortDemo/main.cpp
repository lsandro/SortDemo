//
//  main.cpp
//  SortDemo
//
//  Created by YI on 16/11/7.
//  Copyright © 2016年 Sandro. All rights reserved.
//

#include <iostream>
using namespace std;

#pragma mark - 直接插入排序
void InsertSort(int a[],int n){//直接插入排序，稳定，时间复杂度为O(n²)；
//    int j;
//    for(int i=1;i<n;i++)//循环从第2个元素开始
//    {
//        if(a[i]<a[i-1])
//        {
//            int temp=a[i];
//            for(j=i-1;j>=0 && a[j]>temp;j--)
//            {
//                a[j+1]=a[j];
//            }
//            a[j+1]=temp;//此处就是a[j+1]=temp;
//        }
//    }
    for(int i= 1; i<n; i++){
        if(a[i] < a[i-1]){               //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
            int j= i-1;
            int x = a[i];        //复制为哨兵，即存储待排序元素
            a[i] = a[i-1];           //先后移一个元素
            while(x < a[j]){  //查找在有序表的插入位置
                a[j+1] = a[j];
                j--;         //元素后移
            }
            a[j+1] = x;      //插入到正确位置
        }
    }
}

#pragma mark - 希尔排序

void ShellInsertSort(int a[], int n, int dk)//希尔排序2
{
    for(int i= dk; i<n; ++i){
        if(a[i] < a[i-dk]){          //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
            int j = i-dk;
            int x = a[i];           //复制为哨兵，即存储待排序元素
            a[i] = a[i-dk];         //首先后移一个元素
            while(x < a[j]){     //查找在有序表的插入位置
                a[j+dk] = a[j];
                j -= dk;             //元素后移
            }
            a[j+dk] = x;            //插入到正确位置
        }
    }
    
}

/**
 * 先按增量d（n/2,n为要排序数的个数进行希尔排序
 *
 */
void shellSort(int a[], int n){//希尔排序1
    
    int dk = n/2;
    while( dk >= 1  ){
        ShellInsertSort(a, n, dk);
        dk = dk/2;
    }
}

#pragma mark - 简单选择排序
/**
 * 数组的最小值
 *
 * @return int 数组的键值
 */
int SelectMinKey(int a[], int n, int i)
{
    int k = i;
    for(int j=i+1 ;j< n; ++j) {
        if(a[k] > a[j]) k = j;
    }
    return k;
}

/**
 * 选择排序
 *
 */
void selectSort(int a[], int n){
    int key, tmp;
    for(int i = 0; i< n; ++i) {
        key = SelectMinKey(a, n,i);           //选择最小的元素
        if(key != i){
            tmp = a[i];  a[i] = a[key]; a[key] = tmp; //最小元素与第i位置元素互换
        }
    }
}

#pragma mark - 堆排序
/**
 * 已知H[s…m]除了H[s] 外均满足堆的定义
 * 调整H[s],使其成为大顶堆.即将对第s个结点为根的子树筛选,
 *
 * param H是待调整的堆数组
 * param s是待调整的数组元素的位置
 * param length是数组的长度
 *
 */
void HeapAdjust(int H[],int s, int length)
{
    int tmp  = H[s];
    int child = 2*s+1; //左孩子结点的位置。(i+1 为当前调整结点的右孩子结点的位置)
    while (child < length) {
        if(child+1 <length && H[child]<H[child+1]) { // 如果右孩子大于左孩子(找到比当前待调整结点大的孩子结点)
            ++child ;
        }
        if(H[s]<H[child]) {  // 如果较大的子结点大于父结点
            H[s] = H[child]; // 那么把较大的子结点往上移动，替换它的父结点
            s = child;       // 重新设置s ,即待调整的下一个结点的位置
            child = 2*s+1;
        }  else {            // 如果当前待调整结点大于它的左右孩子，则不需要调整，直接退出
            break;
        }
        H[s] = tmp;         // 当前待调整的结点放到比其大的孩子结点位置上
    }
}


/**
 * 初始堆进行调整
 * 将H[0..length-1]建成堆
 * 调整完之后第一个元素是序列的最小的元素
 */
void BuildingHeap(int H[], int length)
{
    //最后一个有孩子的节点的位置 i=  (length -1) / 2
    for (int i = (length -1) / 2 ; i >= 0; --i)
        HeapAdjust(H,i,length);
}
/**
 * 堆排序算法
 */
void HeapSort(int H[],int length)
{
    //初始堆
    BuildingHeap(H, length);
    //从最后一个元素开始对序列进行调整
    for (int i = length - 1; i > 0; --i)
    {
        //交换堆顶元素H[0]和堆中最后一个元素
        int temp = H[i]; H[i] = H[0]; H[0] = temp;
        //每次交换堆顶元素和堆中最后一个元素之后，都要对堆进行调整
        HeapAdjust(H,0,i);
    }
}

#pragma mark - 冒泡排序
void BubbleSort(int a[], int n)
{
    int j;
    bool flag;
    
    //k = n;
    flag = true;
    while (flag)
    {
        flag = false;
        for (j = 1; j < n; j++){
            if (a[j - 1] > a[j])
            {
                swap(a[j - 1], a[j]);
                flag = true;
            }
        }
        n--;
    }
}

#pragma mark - 快速排序
int partition(int a[], int low, int high)
{
    int privotKey = a[low];                             //基准元素
    while(low < high){                                   //从表的两端交替地向中间扫描
        while(low < high  && a[high] >= privotKey) --high;  //从high 所指位置向前搜索，至多到low+1 位置。将比基准元素小的交换到低端
        swap(a[low], a[high]);
        while(low < high  && a[low] <= privotKey ) ++low;
        swap(a[low], a[high]);
    }
    return low;
}


void quickSort(int a[], int low, int high){
    if(low < high){
        int privotLoc = partition(a,  low,  high);  //将表一分为二
        quickSort(a,  low,  privotLoc -1);          //递归对低子表递归排序
        quickSort(a,   privotLoc + 1, high);        //递归对高子表递归排序
    }
}

#pragma mark - 二分查找

int binarySearch(int a[],int x,int y,int k)
{
    int m=x+(y-x)/2;
    if(x>y){//查找完毕没有找到答案，返回-1
        cout<<"没有该值"<<endl;
        return -1;
    }else
    {
        if(a[m]==k)
            return m;//找到!返回位置.
        else if(a[m]>k)
            return binarySearch(a,x,m-1,k);//找左边
        else
            return binarySearch(a,m+1,y,k);//找右边
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    
    int a[] = {29,5,4,7,12,6,8,45,23,74,24,2,7};
    int n = sizeof(a)/sizeof(a[0]);
    
    //InsertSort(a, n);//直接插入排序
    //shellSort(a, n);//希尔排序
    //selectSort(a,n);//简单选择排序
    //HeapSort(a,n);//堆排序
    BubbleSort(a, n);//冒泡排序
    //quickSort(a, 0, n-1);//快速排序
    
    for (int i = 0; i<n ; i++) {
        cout<<a[i]<<" ";
    }
    cout<<"查找结果："<<binarySearch(a, 0, n-1, 74)<<endl;
    return 0;
}
