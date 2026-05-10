#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100000
#define INF 2000000000
using namespace std;

struct presentation
{
    int S;
    int E;
};

bool comparePresentations(presentation A, presentation B)
{
    return A.S < B.S;
}

vector<presentation> P(MAXN + 2);
int N;
int T;

int main()
{
    scanf("%d %d", &N, &T);

    for (int i = 0; i < N; ++i)
    {
        scanf("%d %d", &P[i].S, &P[i].E);
    }

    P[N] = { -INF, 0 };
    P[N + 1] = { T, INF };

    sort(P.begin(), P.begin() + N + 2, comparePresentations);

    int largestGap = 0;
    int maximumEndTime = P[0].E;

    for (int i = 1; i <= N + 1; ++i)
    {
        if (P[i].S != P[i - 1].S)
        {
            largestGap = max(largestGap, max(P[i].S - maximumEndTime,0));
        }
        
        maximumEndTime = max(maximumEndTime, P[i].E);
    }

    printf("%d\n", largestGap);
}
