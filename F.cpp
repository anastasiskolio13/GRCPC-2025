#include <bits/stdc++.h>
#define MAXN 100000
#define MAXQ 100000
using namespace std;

map<int, vector<pair<int, int>>> Q1;
map<int, vector<pair<int, int>>> Q2;
set<pair<int, int>> S;
vector<int> A(MAXN);
vector<int> TP(MAXN);
vector<int> AP(MAXN);
vector<array<int, 3>> B(MAXQ);
int N;
int Q;
int L1;
int L2;

class SegmentTree {
private:
    vector<int> T;
public:
    SegmentTree() {
        T.resize(4 * N, 0);
    }

    void Update(int lo, int hi, int v, int i, int x) {
        if (lo == hi) {
            T[v] = x;
            return;
        }
        int mid = (lo + hi) / 2;
        if (TP[i] <= mid)
            Update(lo, mid, 2 * v + 1, i, x);
        else
            Update(mid + 1, hi, 2 * v + 2, i, x);
        T[v] = T[2 * v + 1] + T[2 * v + 2];
    }

    int Kth(int lo, int hi, int v, int k) {
        if (lo == hi)
            return A[AP[lo]];
        int mid = (lo + hi) / 2;
        if (T[2 * v + 1] >= k)
            return Kth(lo, mid, 2 * v + 1, k);
        else
            return Kth(mid + 1, hi, 2 * v + 2, k - T[2 * v + 1]);
    }
};

int main() {
    scanf("%d %d %d %d", &N, &Q, &L1, &L2);
    for (int i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
        S.insert({A[i], i});
    }
    int i = 0;
    for (auto [_, index] : S) {
        TP[index] = i;
        AP[i] = index;
        ++i;
    }
    for (int i = 0; i < Q; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        a == 1 ? Q1[b + L1 - 2].push_back({c, i}) : Q2[b + L2 - 2].push_back({c, i});
    }
    SegmentTree T1;
    for (int i = 0; i < N; ++i) {
        if (i - L1 >= 0)
            T1.Update(0, N - 1, 0, i - L1, 0);
        T1.Update(0, N - 1, 0, i, 1);
        for (auto [k, index] : Q1[i]) {
            int minimumElement = T1.Kth(0, N - 1, 0, 1);
            int kthElement = T1.Kth(0, N - 1, 0, k);
            int maximumElement = T1.Kth(0, N - 1, 0, L1);
            B[index] = {minimumElement, kthElement, maximumElement};
        }
    }
    SegmentTree T2;
    for (int i = 0; i < N; ++i) {
        if (i - L2 >= 0)
            T2.Update(0, N - 1, 0, i - L2, 0);
        T2.Update(0, N - 1, 0, i, 1);
        for (auto [k, index] : Q2[i]) {
            int minimumElement = T2.Kth(0, N - 1, 0, 1);
            int kthElement = T2.Kth(0, N - 1, 0, k);
            int maximumElement = T2.Kth(0, N - 1, 0, L2);
            B[index] = {minimumElement, kthElement, maximumElement};
        }
    }
    for (int i = 0; i < Q; ++i)
        printf("%d %d %d\n", B[i][0], B[i][1], B[i][2]);
}
