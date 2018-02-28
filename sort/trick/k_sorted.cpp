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

/*  对一个 k-sorted 数组进行排序
	最简单的，使用插入排序，复杂度为 O(k*N)
	用 heap 来做，复杂度可降为 O(N*logk)
	用 AVL 来做，同样可以达到 O(N*logk) 的复杂度
	
	reference : https://www.geeksforgeeks.org/nearly-sorted-algorithm/
*/

void sift_down(int* heap, int begin, int end) {
	/*  for min heap */
	int parent = begin;
	int child = 2 * parent + 1;
	while (child <= end) {
		
		if (child < end)
			child = (heap[child] < heap[child+1]) ? child : (child+1);
		
		if (heap[parent] <= heap[child]) {
			break;
		} else {
			swap(heap[parent], heap[child]);
			parent = child;
			child = 2 * parent + 1;
		}
	}
}

void min_heapify(int* heap, int n) {
	
	/*  begin at the last parent node */
	int parent = (n - 1 - 1) / 2;
	while (parent >= 0) {
		sift_down(heap, parent, n-1);
		parent--;
	}
}

bool min_heap_verify(int* heap, int n) {
	int pn = (n - 1 - 1) / 2;
	int c1, c2;
	for (int i=0; i<=pn; i++) {
		c1 = 2 * i + 1;
		c2 = min(n-1, c1+1);
		if (heap[i] > heap[c1] || heap[i] > heap[c2])
			return false;
	}
	return true;
}

int main() {
	clock_t t = clock();
	int i, j;
	set<int> s;
	int n = 50;
	int* a = (int*)malloc(sizeof(int)*n);
	int* x = (int*)malloc(sizeof(int)*n);
	int r;
	srand(111);
	for (i=0; i<n; i++) {
		while (1) {
			r = rand() % (n * n);
			if (s.find(r) == s.end()) {
				a[i] = r;
				s.insert(r);
				break;
			}
		}
	}
	sort(a, a+n);
	assert(s.size() == n);
	
	memcpy(x, a, sizeof(int)*n);
	
	// brute force perturbation
	int k = n / 2;
	int flag;
	
	while (1) {
		A:
		random_shuffle(a, a+n);
		for (i=0; i<n; i++) {
			flag = 0;
			for (j=max(i-k, 0); j<=min(i+k, n-1); j++) {
				if (x[i] == a[j]) {
					flag = 1;
					break;
				}
			}
			if (!flag)
				goto A;
		}
		
		break;
	}
	
	/*  Using a fixed size min heap */
	int* heap = (int*)malloc(sizeof(int)*(k+1));
	memcpy(heap, a, sizeof(int)*(k+1));
	
	min_heapify(heap, k+1);
	printf("(%d)\n", min_heap_verify(heap, k+1));
	
	for (i=0; i<n-k-1; i++) {
		a[i] = heap[0];
		heap[0] = a[i+k+1];
		sift_down(heap, 0, k);
	}
	int kk = k;
	while (i < n) {
		a[i++] = heap[0];
		swap(heap[0], heap[kk--]);
		sift_down(heap, 0, kk);
	}
	assert(i == n);
	assert(-1 == kk);
	
	for (i=1; i<n; i++) {
		assert(a[i-1] <= a[i]);
		printf(" %d ", a[i]);
	}
	

	t = clock() - t;
	printf("\n%fs\n", ((float)t) / CLOCKS_PER_SEC);
	
	return 0;
}
