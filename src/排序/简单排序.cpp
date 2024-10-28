#include<bits/stdc++.h>
using namespace std;

// 插入排序函数
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    // 从第1个元素开始，逐个向右插入
    for (int i = 1; i < n; i++) {
        int key = arr[i];  // 记录当前要插入的元素
        int j = i - 1;
        // 向左遍历已排序的部分，找到合适的位置插入
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  // 将大于key的元素向右移动
            j--;
        }
        arr[j + 1] = key;  // 找到合适的位置，将key插入
    }
}

int main() {
    // 定义一个无序数组
    vector<int> arr = {12, 11, 13, 5, 6};

    cout << "未排序的数组: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // 调用插入排序
    insertionSort(arr);

    cout << "插入排序后的数组: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}








#include<bits/stdc++.h>
using namespace std;

// 选择排序函数
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;  // 假设当前元素为最小值
        // 在未排序部分中找到最小值
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;  // 记录最小值的索引
            }
        }
        // 将最小值与当前元素交换
        swap(arr[i], arr[minIndex]);
    }
}

int main() {
    // 定义一个无序数组
    vector<int> arr = {64, 25, 12, 22, 11};

    cout << "未排序的数组: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // 调用选择排序
    selectionSort(arr);

    cout << "选择排序后的数组: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}