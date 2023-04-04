#include <iostream>

#include <algorithm>
#include <set>
#include <queue>
#include <cmath>
#include <map>
#include <cassert>
#include <stack>

using namespace std;

int len, sumLen;

long long mininit(vector<long long> &arr, vector<long long> &tree, int node, int start, int end) {
    if (start == end)    // 노드가 리프 노드인 경우
        return tree[node] = start;    // 배열의 그 원소를 가져야 함

    int mid = (start + end) / 2;
//    cout << start << " " << mid << " " << end << endl;

    // 구간 합을 구하는 경우
//    return tree[node] = mininit(arr, tree, node * 2, start, mid) + mininit(arr, tree, node * 2 + 1, mid + 1, end);

    // 구간의 최솟값을 구하는 경우도 비슷하게 해줄 수 있다.
    long long a = mininit(arr, tree, node * 2, start, mid);
    long long b = mininit(arr, tree, node * 2 + 1, mid + 1, end);
    if (arr[a] <= arr[b]) {
        return tree[node] = a;
    } else {
        return tree[node] = b;
    }

}


long long minsum(vector<long long> &arr, vector<long long> &tree, int node, int start, int end, int left, int right) {
    // case 1: [start, end] 앞 뒤에 [left, right]가 있는 경우,
    // 겹치지 않기 때문에 탐색을 더 이상 할 필요가 없다.
    if (left > end || right < start) return 0;

    // case 2: [start, end]가 [left, right]에 포함
    if (left <= start && end <= right) return tree[node];

    // case 3, 4: 왼쪽 자식과 오른쪽 자식을 루트로 하는 트리에서 다시 탐색 시작
    int mid = (start + end) / 2;
    long long a = minsum(arr, tree, node * 2, start, mid, left, right);
    long long b = minsum(arr, tree, node * 2 + 1, mid + 1, end, left, right);
    if (arr[a] <= arr[b]) {
        return a;
    } else {
        return b;
    }
}


long long
update(vector<long long> &arr, vector<long long> &tree, int node, int start, int end, int index, long long val) {
    if (index > end || index < start) return tree[node];
    if (start == end) return tree[node] = val;
    int mid = start + (end - start) / 2;

    long long a = update(arr, tree, node * 2, start, mid, index, val);
    long long b = update(arr, tree, node * 2 + 1, mid + 1, end, index, val);
    if (arr[a] <= arr[b]) {
        return tree[node] = a;
    } else {
        return tree[node] = b;
    }


}


// 1000000000000000000
// 1초: 1억번
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);


    cin >> len;

    vector<long long> vec;

    vec.push_back(1000000001);
    for (int i = 0; i < len; ++i) {
        long long n;
        cin >> n;
        vec.push_back(n);
    }


    vector<long long> minSegTree(4 * len);

    mininit(vec, minSegTree, 1, 1, len);


//    for (long long n: minSegTree) {
//        cout << n << " ";
//    }
//    cout << endl;

//    long long minS = minsum(vec, minSegTree, 1, 0, len-1, 0, 4);
//    cout << minS << '\n';

    cin >> sumLen;

    for (int i = 0; i < sumLen; ++i) {
        int M, a, b;
        cin >> M >> a >> b;
        if (M == 1) {
// 업데이트
            int val = a;
            int index = a - 1;
            vec[a] = b;
            update(vec, minSegTree, 1, 0, len - 1, index, val);
        } else {
            int left = a - 1;
            int right = b - 1;
            long long minS = minsum(vec, minSegTree, 1, 0, len - 1, left, right);
//        long long maxS = maxsum(maxSegTree, 1, 0, len - 1, left, right);

            cout << minS << '\n';
        }

    }


}
