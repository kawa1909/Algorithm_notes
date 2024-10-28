#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 1;

//堆结构(将子树中最大的值放到顶点)
//父亲节点：（i - 1） / 2
//左孩子节点：i * 2 + 1
//右孩子节点：i * 2 + 2

void swap(vector<int>arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}


//比较头节点,向上调整大根堆
void heapinsert(vector<int>arr, int i) {
    while (arr[i] > arr[(i - 1) / 2]) {
        swap(arr, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

//比较左右孩子节点，向下调整大根堆
void heapify(vector<int>arr, int i, int size) {
    int l = i * 2 + 1;
    while (l < size) {
        //有右孩子，l + 1
        //左孩子，l
        //最强的孩子是哪个下标
        int best = l + 1 < size && arr[l + 1] > arr[l] ? l + 1 : l;
        //最强的下标是谁
        best = arr[best] > arr[i] ? best : i;
        if (best == i) {
            break;
        }
        swap(arr, best, i);
        i = best;
        l = i * 2 + 1;
    }
}


//从顶到底建立大根堆O(N * logN)
//依次弹出堆内最大值并排序O(N * logN)
void heapsort1(vector<int>arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        heapinsert(arr, i);
    }
    int size = n;
    while (size > 1) {
        swap(arr, 0, --size);
        heapify(arr, 0, size);
    }
}


//从底到顶建立大根堆O（N）
//依次弹出堆内最大值排序O(N * logN)
void heapsort2(vector<int>arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        heapify(arr, i, n);
    }
    int size = n;
    while (size > 1) {
        swap(arr, 0, --size);
        heapify(arr, 0, size);
    }
}

int main() {

}