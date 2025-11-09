#include <bits/stdc++.h>
#define MAXN 100000
#define INF 2e9
using namespace std;

deque<int> Q;
vector<vector<pair<int, int>>> Adj(MAXN);
vector<int> D(MAXN);
int N;
int M;

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; ++i) {
        int v, u, w;
        scanf("%d %d %d", &v, &u, &w);
        Adj[--v].push_back({--u, w});
    }
    fill(D.begin(), D.begin() + N, INF);
    D[0] = 0;
    Q.push_back(0);
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop_front();
        for (auto [u, w] : Adj[v]) {
            if (D[v] + w < D[u]) {
                D[u] = D[v] + w;
                w ? Q.push_back(u) : Q.push_front(u);
            }
        }
    }
    printf("%d\n", D[N - 1] != INF ? D[N - 1] : -1);
}
