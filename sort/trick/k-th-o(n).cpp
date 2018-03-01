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

/*  T(n) <= T(ceil(n/5)) + T(7n/10+6) + O(n)
	该算法可以保证最坏情况下复杂度仍为 O(n) ，但由于前面的常数系数一般很大，
	实际的运行效率并不如 random quick select 
	reference : https://www.geeksforgeeks.org/?p=132857
 */

int partition(int* a, int begin, int end, int pivot) {
	int i = begin - 1, j = end + 1;
	while (1) {
		do {
			i++;
		} while (a[i] < pivot);
		
		do {
			j--;
		} while (a[j] > pivot);
		
		if (i >= j)
			return j;
		
		swap(a[i], a[j]);
	}
}

int find_medium(int* x, int n) {
	/*  O(1) */
	sort(x, x+n);
	return x[(n+1)/2-1];
}

int find_kth(int* a, int begin, int end, int k) {
	/*  k is guaranteed to be less than the size of array 
		k is relative position in a[begin:end]
		k >= 1
	 */
	
	if (begin == end) {
		assert(0 == k - 1);
		return a[begin];
	} else if (begin < end) {
		// printf("%d %d - [%d, %d]\n", begin, end, a[begin], a[end]);
		int nn = end - begin + 1;
		int ms = (nn + 4) / 5;/* trick for ceil(nn/5.0f) */
		int* m = (int*)malloc(sizeof(int)*ms);
		int i, j = 0;
		for (i=0; i<nn; i+=5)
			m[j++] = find_medium(a+begin+i, min(nn-i, 5));
		assert(j == ms);
		int pivot = find_kth(m, 0, ms-1, (ms+1)/2);
		// printf("pivot: %d\n", pivot);
		int p = partition(a, begin, end, pivot);
		// printf("p: %d\n", p);
		// printf("k: %d\n", k);
		if (p - begin < k - 1)
			return find_kth(a, p+1, end, k-(p-begin+1));
		else
			return find_kth(a, begin, p, k);
	}
}



int main() {
	
	int n;
	int k;
	int c = 1;
	while (c--) {
		// scanf("%d %d", &n, &k);
		n = rand() % 100000 + 1;
		k = rand() % n + 1;
		n = k = 100;
		int* a = (int*)malloc(sizeof(int)*n);
		int i, j;
		for (i=0; i<n; i++)
			a[i] = i + 1;
			// a[i] = rand() % 5;
		random_shuffle(a, a+n);
		
		int kth = find_kth(a, 0, n-1, k);
		// printf("%d\n", kth);
		assert(kth == k);
	}
	
	return 0;
}

/*  对于元素个数为偶数的有序序列，中位数取前一个，
	例如，假设有6个元素，则中位数取第3个；
 */