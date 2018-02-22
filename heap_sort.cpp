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

void heapify(int* a, int n) {
	// O(nlogn), not optimal
	int cur;
	for (int i=1; i<n; i++) {
		cur = i;
		while (a[cur] > a[(cur-1)/2]) {
			swap(a[cur], a[(cur-1)/2]);
			cur = (cur - 1) / 2;
		}
	}
}

void sift(int* a, int end) {
	int cur = 0;
	while (true) {
		if (2 * cur + 2 <= end) {
			// left && right exist
			if (a[cur] < max(a[2*cur+1], a[2*cur+2])) {
				if (a[2*cur+1] > a[2*cur+2]) {
					swap(a[cur], a[2*cur+1]);
					cur = 2 * cur + 1;
				} else {
					swap(a[cur], a[2*cur+2]);
					cur = 2 * cur + 2;
				}
			} else {
				break;
			}
		} else if (2 * cur + 1 <= end) {
			// only left exist
			if (a[cur] < a[2*cur+1]) {
				swap(a[cur], a[2*cur+1]);
				cur = 2 * cur + 1;
			} else {
				break;
			}
		} else {
			// leaf node
			break;
		}
	}
}

void heap_sort(int* a, int n) {
	heapify(a, n);
	int end = n - 1;
	while (end > 0) {
		swap(a[0], a[end]);
		end--;
		sift(a, end);
		
	}
}

void pa(int* a, int n) {
	for (int i=0; i<n; i++)
		printf(" %d ", a[i]);
	printf("\n");
}

int main() {
	
	int a[] = {12, 324, 42, 42, 5, 74, 534, 543, 9};
	// int a[] = {-12, 1};
	int n = sizeof(a) / sizeof(a[0]);
	heap_sort(a, n);
	
	pa(a, n);

	return 0;
}
