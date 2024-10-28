#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 1;

ll help[N], a[N];
void merge(ll l, ll r){
    //1、将数组排序
    if(l >= r) return;

    ll mid = l + ((r - l) >> 1);
    ll i = l, j = mid + 1, t = l;
    while(i <= mid && j <= r){
        help[t++] = a[i] <= a[j] ? a[i++] : a[j++];
    }
    //2、将左半区域剩余元素排序
    while(i <= mid){
        help[t++] = a[i++];
    }
    //3、将右半区域剩余元素排序
    while(j <= r){
        help[t++] = a[j++];
    }
    //4、复制数组
    for(int i = l; i <= r; i++){
        a[i] = help[i];
    }
    return;
}

void mergeSort(ll l, ll r){
    if(l < r){
        ll mid = l + ((r - l) >> 1);
        //左边区域
        mergeSort(l, mid);
        //右边区域
        mergeSort(mid + 1, r);
        //合并左右区域
        merge(l, r);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin.tie(0),cout.tie(0);

    ll n;
    cin >> n;

    for(int i = 0; i < n; i++){
        cin >> a[i];
    }

    mergeSort(0, n - 1);
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }

    return 0;
}