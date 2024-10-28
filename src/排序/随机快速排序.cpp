#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 1;

ll arr[5] = {9,7,5,4,2};
int first, last;
//交换数值
void swap(int i, int j) {
    ll tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

//荷兰国旗问题(优化随机快排)
//优化点：选出一个x，在划分的时候搞定所有值是x的数字
void pattion2(int l, int r, int x) {
    first = l;
    last = r;
    int i = l;
    while (i <= last) {
        if (arr[i] < x) {
            swap(first, i);
            first++;
            i++;
        }
        else if (arr[i] == x) {
            i++;
        }
        else{
            swap(last, i);
            last--;
        }
    }
}


void QuickSort2(int l, int r) {
    if (l < r) {
        int QIndex = rand() % (r - l + 1) + l;//随机下标
        int pvit = arr[QIndex];//基准值
        pattion2(l, r, pvit);
        //采用临时变量记录
        int left = first;
        int right = last;
        QuickSort1(l, left - 1);
        QuickSort1(right + 1, r);
    }
}

int main() {
    int n = 5;
    //cin >> n;
    //
    //for (int i = 0; i < n; i++) {
    //	cin >> arr[i];
    //}

    srand(time(nullptr));
    QuickSort2(0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}