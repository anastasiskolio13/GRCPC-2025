#include <iostream>
#include <vector>
#include <array>
#define MAXN 100000
#define MAXQ 100000
#define MAXVAL 1000000000
using namespace std;

vector<int> A(MAXN);
vector<vector<pair<int, int>>> Q1(MAXN);
vector<vector<pair<int, int>>> Q2(MAXN);
vector<array<int, 3>> B(MAXN);
int N;
int Q;
int L1;
int L2;

struct Node
{
	int value;
	Node* left;
	Node* right;
};

Node* root = new Node();

void Update(const int i, const int x, Node*& current = root, int lo = 0, int hi = MAXVAL)
{
	if (current == nullptr)
	{
		current = new Node();
	}

	current->value += x;

	if (lo == hi)
	{
		return;
	}

	int mid = (lo + hi) / 2;

	if (i <= mid)
	{
		Update(i, x, current->left, lo, mid);
	}
	else
	{
		Update(i, x, current->right, mid + 1, hi);
	}
}

int Kth(const int k, Node* current = root, int lo = 0, int hi = MAXVAL)
{
	if (lo == hi)
	{
		return lo;
	}

	int mid = (lo + hi) / 2;

	if (current->left && current->left->value >= k)
	{
		return Kth(k, current->left, lo, mid);
	}
	else
	{
		return Kth(k - (current->left ? current->left->value : 0), current->right, mid + 1, hi);
	}
}

int main()
{
	scanf("%d %d %d %d", &N, &Q, &L1, &L2);

	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &A[i]);
	}

	for (int i = 0; i < Q; ++i)
	{
		int A;
		int B;
		int C;

		scanf("%d %d %d", &A, &B, &C);

		if (A == 1)
		{
			Q1[--B].push_back(make_pair(C, i));
		}
		else
		{
			Q2[--B].push_back(make_pair(C, i));
		}
	}

	for (int i = N - 1; i >= 0; --i)
	{
		if (N - 1 - L1 >= i)
		{
			Update(A[i + L1], -1);
		}
		
		Update(A[i], 1);

		for (auto [k, index] : Q1[i])
		{
			int smallest = Kth(1);
			int kth = Kth(k);
			int largest = Kth(L1);

			B[index] = { smallest, kth, largest };
		}
	}

	root = new Node();

	for (int i = N - 1; i >= 0; --i)
	{
		if (N - 1 - L2 >= i)
		{
			Update(A[i + L2], -1);
		}

		Update(A[i], 1);

		for (auto [k, index] : Q2[i])
		{
			int smallest = Kth(1);
			int kth = Kth(k);
			int largest = Kth(L2);

			B[index] = { smallest, kth, largest };
		}
	}

	for (int i = 0; i < Q; ++i)
	{
		printf("%d %d %d\n", B[i][0], B[i][1], B[i][2]);
	}
}