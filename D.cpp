#include <bits/stdc++.h>
#define MAXN 200000
using namespace std;

vector<int> A(MAXN);
vector<int> B(MAXN);
vector<long long> C(MAXN);
int N;
int X;

long long costOfTaking(int K) {
    for (int i = 0; i < N; ++i)
        C[i] = A[i] + (long long)K * B[i];
    nth_element(C.begin(), C.begin() + K, C.begin() + N);
    return accumulate(C.begin(), C.begin() + K, 0LL);
}

int main() {
    scanf("%d %d", &N, &X);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    for (int i = 0; i < N; ++i)
        scanf("%d", &B[i]);
    int lo = 0;
    int hi = N;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (costOfTaking(mid) <= X)
            lo = mid;
        else
            hi = mid - 1;
    }
    printf("%d %lld\n", lo, costOfTaking(lo));
}
