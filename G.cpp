#include <bits/stdc++.h>
using namespace std;

#define ll long long int

const int N = 2005;

static int mk[N][N];
struct seg
{
    int n;
    vector<int> t;

    seg(int _n) : n(_n), t(2 * n) {}

    void upd(int l, int r, int val)
    {
        for (l += n - 1, r += n - 1; l <= r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                t[l] = max(t[l], val), l++;
            if (!(r & 1))
                t[r] = max(t[r], val), r--;
        }
    }

    int q(int p)
    {
        int ans = 0;
        for (p += n - 1; p; p >>= 1)
            ans = max(ans, t[p]);
        return ans;
    }
};
struct seg2d
{
    int n;
    vector<seg> t;

    seg2d(int _n) : n(_n)
    {
        t.reserve(2 * n);
        for (int i = 0; i < 2 * n; i++)
            t.emplace_back(n);
    }

    void upd(int x1, int x2, int y1, int y2, int val)
    {
        for (x1 += n - 1, x2 += n - 1; x1 <= x2; x1 >>= 1, x2 >>= 1)
        {
            if (x1 & 1)
            {
                t[x1].upd(y1, y2, val);
                x1++;
            }
            if (!(x2 & 1))
            {
                t[x2].upd(y1, y2, val);
                x2--;
            }
        }
    }

    int q(int x, int y)
    {
        int ans = 0;
        for (x += n - 1; x; x >>= 1)
            ans = max(ans, t[x].q(y));
        return ans;
    }
};
void solve()
{
    int n;
    cin >> n;

    vector<array<int, 4>> w(n + 1);
    for (int i = 0; i < n; i++)
    {
        int x, y, xx, yy, z;
        cin >> x >> y >> xx >> yy >> z;

        w[z] = {x * 2 + 1, y * 2 + 1, xx * 2 + 1, yy * 2 + 1};
    }

    seg2d st2(N);
    for (int j = n; j >= 1; j--)
    {
        st2.upd(w[j][1], w[j][3], w[j][0], w[j][2], j);
    }

    int ans = 0;
    for (int i = 1; i <= 2001; i++)
    {
        int cur = 0;
        for (int j = 1; j <= 2001; j++)
        {

            int v = st2.q(i, j);

            if (i == w[v][1] || i == w[v][3])
                mk[i][j] |= 1;
            if (j == w[v][0] || j == w[v][2])
                mk[i][j] |= 2;
            if (mk[i][j] & 1)
            {
                cur++;
            }
            else
            {
                if (cur)
                    ans++;
                cur = 0;
            }
        }
        if (cur)
            ans++;
    }
    for (int j = 1; j <= 2001; j++)
    {
        int cur = 0;
        for (int i = 1; i <= 2001; i++)
        {
            if (mk[i][j] & 2)
            {
                cur++;
            }
            else
            {
                if (cur)
                    ans++;
                cur = 0;
            }
        }
        if (cur)
            ans++;
    }
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}