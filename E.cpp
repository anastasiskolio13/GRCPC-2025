#include <bits/stdc++.h>
#define MAXN 10000
#define INF 1e18
using namespace std;

struct target {
    int A;
    int B;
};

bool compareTargets(target A, target B) {
    return A.B > B.B;
}

vector<target> T(MAXN + 1);
vector<vector<long long>> dp(2, vector<long long>(MAXN + 1));
int N;
int X;

int main() {
    scanf("%d %d", &N, &X);
    for (int i = 1; i <= N; ++i)
        scanf("%d", &T[i].A);
    for (int i = 1; i <= N; ++i)
        scanf("%d", &T[i].B);
    sort(T.begin() + 1, T.begin() + N + 1, compareTargets);
    dp[0][0] = 0;
    for (int i = 1; i <= N; ++i)
        dp[0][i] = INF;
    for (int i = 1; i <= N; ++i) {
        dp[i % 2][0] = dp[(i - 1) % 2][0];
        for (int j = 1; j <= N; ++j)
            dp[i % 2][j] = min(dp[(i - 1) % 2][j], dp[(i - 1) % 2][j - 1] + T[i].A + T[i].B * (j - 1));
    }
    for (int i = N; i >= 0; --i) {
        if (dp[N % 2][i] <= X) {
            printf("%d %lld\n", i, dp[N % 2][i]);
            return 0;
        }
    }
}
