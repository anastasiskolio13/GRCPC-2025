#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#define MAXN 100000
#define INF 2e9
using namespace std;

vector<int> A(MAXN);
vector<pair<int, int>> T(4 * MAXN);
vector<pair<int, int>> L(MAXN);
vector<pair<int, int>> R(MAXN);
int N;
int Q;

void Build(int lo = 0, int hi = N - 1, int v = 0)
{
	if (lo == hi)
	{
		T[v] = make_pair(A[lo], lo);

		return;
	}

	int mid = (lo + hi) / 2;
	
	Build(lo, mid, 2 * v + 1);
	
	Build(mid + 1, hi, 2 * v + 2);

	if (T[2 * v + 1].first > T[2 * v + 2].first)
	{
		T[v] = T[2 * v + 1];
	}
	else
	{
		T[v] = T[2 * v + 2];
	}
}

// Returns max{j < i : A[j] > x}.
int FirstLargerLeft(int i, int x, int lo = 0, int hi = N - 1, int v = 0)
{
	if (lo == hi)
	{
		return T[v].first > x && lo < i ? lo : -1;
	}

	int mid = (lo + hi) / 2;

	if (T[2 * v + 2].first > x && i > mid + 1)
	{
		int q = FirstLargerLeft(i, x, mid + 1, hi, 2 * v + 2);

		if (q != -1) { return q; }
	}

	return FirstLargerLeft(i, x, lo, mid, 2 * v + 1);
}

// Returns min{j > i : A[j] > x}.
int FirstLargerRight(int i, int x, int lo = 0, int hi = N - 1, int v = 0)
{
	if (lo == hi)
	{
		return T[v].first > x && lo > i ? lo : -1;
	}

	int mid = (lo + hi) / 2;

	if (T[2 * v + 1].first > x && i < mid)
	{
		int q = FirstLargerRight(i, x, lo, mid, 2 * v + 1);

		if (q != -1) { return q; }
	}
	
	return FirstLargerRight(i, x, mid + 1, hi, 2 * v + 2);
}

// Returns argmax{A[i] : qlo <= i <= qhi}. 
int ArgMax(int qlo, int qhi, int lo = 0, int hi = N - 1, int v = 0)
{
	if (qlo > hi || qhi < lo)
	{
		return -1;
	}

	if (qlo <= lo && hi <= qhi)
	{
		return T[v].second;
	}

	int mid = (lo + hi) / 2;

	int posLeft = ArgMax(qlo, qhi, lo, mid, 2 * v + 1);

	int posRight = ArgMax(qlo, qhi, mid + 1, hi, 2 * v + 2);

	if (posLeft == -1)
	{
		return posRight;
	}

	if (posRight == -1)
	{
		return posLeft;
	}

	if (A[posLeft] > A[posRight])
	{
		return posLeft;
	}
	else
	{
		return posRight;
	}
}

// Returns argmax{A[i] : qlo <= i <= qhi}, arg2max{A[i] : qlo <= i <= qhi}.
pair<int, int> TwoMaxes(int qlo, int qhi)
{
	int argmax = ArgMax(qlo, qhi);

	int argmaxLeft = ArgMax(qlo, argmax - 1);

	int argmaxRight = ArgMax(argmax + 1, qhi);

	if (argmaxLeft == -1)
	{
		return make_pair(argmax, argmaxRight);
	}

	if (argmaxRight == -1)
	{
		return make_pair(argmax, argmaxLeft);
	}

	if (A[argmaxLeft] > A[argmaxRight])
	{
		return make_pair(argmax, argmaxLeft);
	}
	else
	{
		return make_pair(argmax, argmaxRight);
	}
}

int main()
{
	cin >> N >> Q;

	for (int i = 0; i < N; ++i)
	{
		cin >> A[i];
	}

	Build();

	for (int i = 0; i < N; ++i)
	{
		L[i].first = FirstLargerLeft(i, A[i]);

		if (L[i].first != -1)
		{
			L[i].second = FirstLargerLeft(L[i].first, A[i]);
		}
		else
		{
			L[i].second = -1;
		}

		R[i].first = FirstLargerRight(i, A[i]);

		if (R[i].first != -1)
		{
			R[i].second = FirstLargerRight(R[i].first, A[i]);
		}
		else
		{
			R[i].second = -1;
		}
	}


	for (int i = 0; i < Q; ++i)
	{
		int K;

		cin >> K;

		vector<int> P(K);

		for (int j = 0; j < K; ++j)
		{
			cin >> P[j];

			--P[j];
		}

		unordered_set<int> S;

		for (int j = 0; j < K - 1; ++j)
		{
			auto twoMaxes = TwoMaxes(P[j], P[j + 1]);

			S.insert({ twoMaxes.first, twoMaxes.second });
		}

		long long ans = 0;

		for (auto idx : S)
		{
			int firstGreaterLeft = L[idx].first;   
			
			int secondGreaterLeft = L[idx].second;  

			int firstGreaterRight = R[idx].first;  
			
			int secondGreaterRight = R[idx].second; 

			if (firstGreaterLeft != -1)
			{
				auto iteratorOne = lower_bound(P.begin(), P.end(), secondGreaterLeft + 1);
				
				auto iteratorTwo = upper_bound(P.begin(), P.end(), firstGreaterLeft);

				long long leftCount = iteratorTwo - iteratorOne;

				auto iteratorThree = lower_bound(P.begin(), P.end(), idx);
				
				auto iteratorFour = firstGreaterRight == -1 ? P.end() : lower_bound(P.begin(), P.end(), firstGreaterRight);

				long long rightCount = iteratorFour - iteratorThree;

				ans += 1LL * A[idx] * leftCount * rightCount;
			}

			if (firstGreaterRight != -1)
			{
				auto iteratorOne = lower_bound(P.begin(), P.end(), firstGreaterLeft + 1);
				
				auto iteratorTwo = upper_bound(P.begin(), P.end(), idx);

				long long leftCount = iteratorTwo - iteratorOne;

				auto iteratorThree = lower_bound(P.begin(), P.end(), firstGreaterRight);
				
				auto iteratorFour = secondGreaterRight == -1 ? P.end() : lower_bound(P.begin(), P.end(), secondGreaterRight);

				long long rightCount = iteratorFour - iteratorThree;

				ans += 1LL * A[idx] * leftCount * rightCount;
			}
		}

		cout << ans << "\n";
	}
}