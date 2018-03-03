#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<cstring>
#include<cassert>
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

int naive(int* a, int n) {
	int inv = 0;
	for (int i=0; i<n; i++)
		for (int j=i+1; j<n; j++)
			if (a[j] < a[i])
				inv++;
	return inv;
}

int u[10000];/*  auxiliary array */

void merge(int* a, int begin, int mid, int end, int* inv) {
	int i, j, k = 0;
	i = begin;
	j = mid;
	while (i <= mid - 1 && j <= end) {
		// u[k++] = (a[i] < a[j]) ? a[i++] : a[j++];
		if (a[i] <= a[j]) {
			u[k++] = a[i++];
		} else {
			u[k++] = a[j++];
			*inv += (mid - i);
		}
	}
	while (i <= mid - 1)
		u[k++] = a[i++];
	while (j <= end)
		u[k++] = a[j++];
	
	memcpy(a+begin, u, sizeof(int)*k);
}

int get_inv(int* a, int begin, int end) {
	if (a != NULL && begin <= end) {
		
		int c = end - begin + 1;/*  the no. of sorted subarray */
		int base = 2;
		int inv = 0;
		
		while (c > 1) {
			for (int x=begin; x<=end; x+=base) {
				
				merge(a, x, min(x+base/2, end), min(x+base-1, end), &inv);
			}
			
			c = c / 2 + c % 2;
			base *= 2;
		}
		
		return inv;
	}
}

int main() {
	
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	
	int n = 10000;
	scanf("%d", &n);
	int inv = 0;
	int i;
	int* a = (int*)malloc(sizeof(int)*n);
	for (i=0; i<n; i++) {
		a[i] = rand() % 1000;
		scanf("%d", &a[i]);
	}
	int answer = naive(a, n);
	
	inv = get_inv(a, 0,  n-1);
	
	for (i=1; i<n; i++)
		assert(a[i-1] <= a[i]);
	
	
	printf("\n%d %d\n", inv, answer);
	assert(inv == answer);
	
	return 0;
}

/*  Count inversions in an array (Using Self-Balancing BST)
	reference : https://www.geeksforgeeks.org/counting-inversions/
	
	其实就是做了一遍 mergesort ，但是在 merge 的时候，维护了 inv 计数
	复杂度为 O(nlogn)
 */
