#include <bits/stdc++.h>
#define MAXN 1000000
#define INF 2e9
using namespace std;

vector<int> A(MAXN);
int N;

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &A[i]);
    int minimumEvenNumber = INF;
    for (int i = 0; i < N; ++i)
        if (abs(A[i]) % 2 == 0 && abs(A[i]) < minimumEvenNumber)
            minimumEvenNumber = abs(A[i]);
    printf("%d\n", minimumEvenNumber != INF ? minimumEvenNumber / 2 : -1);
}
