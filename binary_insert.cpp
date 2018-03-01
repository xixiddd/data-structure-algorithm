#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<cstring>
#include<iostream>
#include<sstream>
#include<vector>
#include<set>
#include<map>
#include<stack>
#include<queue>
#include<bitset>
#include<algorithm>
#include<iterator>
#include<string>
#include<tuple>
#include<random>

using namespace std;



const int maxn = 1000000 + 5;
int a[maxn];

void pa(int* a, int n) {
	for (int i=0; i<n; i++)
		printf(" %d ", a[i]);
	printf("\n");
}

bool check_arr(int* a, int n) {
	for (int i=1; i<n; i++)
		if (a[i-1] > a[i])
			return false;
	return true;
}

int binary_insert(int* a, int n, int val) {
	if (n >= maxn)
		return n;
	
	int i = 0, j = n - 1;
	int mid;
	while (i <= j) {
		mid = i + (j - i) / 2;
		if (val == a[mid]) {
			for (int k=n; k>mid; k--)
				a[k] = a[k-1];
			return n + 1;
		} else if (val < a[mid]) {
			j = mid - 1;
		} else {
			i = mid + 1;
		}
	}
	
	/*  The details of codes below can be surprisingly tricky
		I work on it almost the whole night but failed */
	if (val < a[mid]) {
		while (val < a[mid]) {
			mid--;
			if (-1 == mid)
				break;
		}
		mid++;
	} else {
		while (val > a[mid]) {
			mid++;
			if (n == mid)
				break;
		}
		// mid--;
	}
	for (int k=n; k>mid; k--)
		a[k] = a[k-1];
	a[mid] = val;
	
	return n + 1;
}

int main() {
	int n = 20;
	for (int i=0; i<n; i++)
		a[i] = rand() % 20;
	sort(a, a+n);
	n = binary_insert(a, n, 3);
	printf("(%d)\n", check_arr(a, n));
	pa(a, n);
	
	return 0;
}