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

/*  输入一个无序数组，找出其中第 k 个元素 
	1. 排序 O(nlogn)
	2. O(n) 建（最小）堆，然后 pop k 次， O(n + klogn)
	3. 维护一个大小固定为 k 的最大堆（或者AVL树），存储当前最小的 k 个数，扫一遍数组， O(nlogk)
	4. quick_select，平均情况 O(n + n/2 + n/2^2 + ...) = O(n)，最坏情况 O(n^2)
	reference : https://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/
	
	5. T(n) <= T(ceil(n/5)) + T(7n/10+6) + O(n)
	该算法可以保证最坏情况下复杂度仍为 O(n)
	reference : https://www.geeksforgeeks.org/?p=132857
*/

int partition(int* a, int begin, int end) {
	int idx = rand() % (end - begin) + begin;
	int pivot = a[begin];
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

int find_kth(int* a, int begin, int end, int k) {
	if (begin == end) {
		assert(begin == k - 1);
		return a[begin];
	} else if (begin < end) {
		int p = partition(a, begin, end);
		if (p < k - 1)
			return find_kth(a, p+1, end, k);
		else
			return find_kth(a, begin, p, k);
	}
	return -1;
}



int main() {
	
	int n;
	scanf("%d", &n);
	int k = 5;
	int* a = (int*)malloc(sizeof(int)*n);
	int i, j;
	for (i=0; i<n; i++)
		a[i] = i + 1;
		// a[i] = rand() % 5;
	random_shuffle(a, a+n);
	
	int kth = find_kth(a, 0, n-1, k);
	printf("%d\n", kth);
	// assert(kth == k);
	
	
	return 0;
}