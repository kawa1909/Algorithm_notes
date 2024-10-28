#include <iostream>
#include <vector>

using namespace std;

// 冒泡排序函数
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);  // 交换相邻元素
            }
        }
    }
}

int main() {
    // 定义一个无序数组
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    cout << "未排序的数组: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // 调用冒泡排序
    bubbleSort(arr);

    cout << "冒泡排序后的数组: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}