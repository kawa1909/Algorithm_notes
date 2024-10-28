#include <iostream>
#include <vector>

using namespace std;

// 希尔排序函数
void shellSort(vector<int>& arr) {
    int n = arr.size();
    // 初始化增量
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // 对每个增量进行插入排序
        for (int i = gap; i < n; i++) {
            int temp = arr[i];  // 暂存当前元素
            int j;
            // 将当前元素插入到合适位置
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];  // 元素向右移动
            }
            arr[j] = temp;  // 插入元素
        }
    }
}

int main() {
    // 定义一个无序数组
    vector<int> arr = {12, 34, 54, 2, 3};

    cout << "未排序的数组: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    // 调用希尔排序
    shellSort(arr);

    cout << "希尔排序后的数组: ";
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}