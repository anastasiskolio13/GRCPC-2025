#include <iostream>
#include <vector>
#define MAXN 100000
#define INF 2e9
using namespace std;

struct Node
{
	int firstMax;
	int secondMax;
	int firstMaxIdx;
	int secondMaxIdx;
};

vector<int> A(MAXN);
vector<Node> T(4 * MAXN);
vector<pair<int, int>> L(MAXN);
vector<pair<int, int>> R(MAXN);
int N;
int Q;

void Build(int lo = 0, int hi = N - 1, int v = 0)
{
	if (lo == hi)
	{
		T[v] = { A[lo], -INF, lo, -1 };
		return;
	}

	int mid = (lo + hi) / 2;
	
	Build(lo, mid, 2 * v + 1);
	
	Build(mid + 1, hi, 2 * v + 2);

	if (T[2 * v + 1])
	
	//T[v] = max(T[2 * v + 1], T[2 * v + 2]);
}

// Returns max{j < i : A[j] > x}.
int FirstLargerLeft(int i, int x, int lo = 0, int hi = N - 1, int v = 0)
{
	if (lo == hi)
	{
		return T[v] > x ? lo : -1;
	}

	int mid = (lo + hi) / 2;

	if (T[2 * v + 2] > x && i > mid + 1)
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
		return T[v] > x ? lo : -1;
	}

	int mid = (lo + hi) / 2;

	if (T[2 * v + 1] > x && i < mid)
	{
		int q = FirstLargerRight(i, x, lo, mid, 2 * v + 1);

		if (q != -1) { return q; }
	}
	
	return FirstLargerRight(i, x, mid + 1, hi, 2 * v + 2);
}

int Max(int qlo, int qhi, int lo = 0, int hi = N - 1, int v = 0)
{
	if (qlo > hi || qhi < lo)
	{
		return -1;
	}

	if (qlo <= lo && hi <= qhi)
	{
		return T[v];
	}

	int mid = (lo + hi) / 2;

	return max(Max(qlo, qhi, lo, mid, 2 * v + 1), Max(qlo, qhi, mid + 1, hi, 2 * v + 2));
}

int main()
{
	cin >> N >> Q;

	for (int i = 0; i < N; ++i)
	{
		cin >> A[i];
	}

	Build();

	//for (int i = 0; i < N; ++i)
	//{
	//	L[i].first = FirstLargerLeft(i - 1, A[i] + 1);

	//	L[i].second = FirstLargerLeft(L[i].first - 1, A[i] + 1);

	//	R[i].first = FirstLargerRight(i + 1, A[i] + 1);

	//	R[i].second = FirstLargerRight(R[i].first + 1, A[i] + 1);
	//}

	//cout << FirstLargerLeft(-7, A[5] + 1) << endl;

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


	}
}