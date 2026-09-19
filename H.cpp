#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAX_XOR = 15;
constexpr long long MOD = 1e9 + 7;

long long calculateDP(long long X)
{
	vector<int> D = {0};

	while (X > 0)
	{
		D.push_back(X % 10);

		X /= 10;
	}

	const int L = D.size() - 1;

	long long dp[D.size()][MAX_XOR + 1][2];

	dp[0][0][0] = dp[0][0][1] = 1;

	for (int x = 1; x <= MAX_XOR; ++x)
	{
		dp[0][x][0] = dp[0][x][1] = 0;
	}

	for (int i = 1; i <= L; ++i)
	{
		for (int x = 0; x <= MAX_XOR; ++x)
		{
			dp[i][x][0] = dp[i - 1][x ^ D[i]][0];

			for (int j = 0; j <= D[i] - 1; ++j)
			{
				dp[i][x][0] += dp[i - 1][x ^ j][1];
				dp[i][x][0] %= MOD;
			}

			dp[i][x][1] = 0;

			for (int j = 0; j <= 9; ++j)
			{
				dp[i][x][1] += dp[i - 1][x ^ j][1];
				dp[i][x][1] %= MOD;
			}
		}
	}

	long long ans_x = 0;

	for (int y = 0; y <= MAX_XOR; ++y)
	{
		long long ans_y = ((dp[L][y][0] % MOD) * y) % MOD;

		ans_x += ans_y;

		ans_x %= MOD;
	}

	return ans_x;
}

int main()
{
	int N;

	cin >> N;

	vector<int> A(N);

	for (int i = 0; i < N; ++i)
	{
		cin >> A[i];
	}

	sort(A.begin(), A.end());

	vector<pair<long long, long long>> B(N);

	for (int i = 0; i < N; ++i)
	{
		B[i] = make_pair(calculateDP(A[i]), calculateDP(A[i] - 1));
	}

	long long ans = 0;

	for (int i = 0; i < N; ++i)
	{
		long long termOne = (i * B[i].first) % MOD;

		long long termTwo = ((N - i - 1) * B[i].second) % MOD;

		long long ans_i = (termOne - termTwo + MOD) % MOD;

		ans += ans_i;

		ans %= MOD;
	}

	cout << ans << endl;
}