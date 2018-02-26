#include "sort_utility.cpp"

void sift_up(int* a, int begin, int end) {
	int child = end, parent;
	while (child > begin) {
		parent = (child - 1) / 2;
		if (a[child] > a[parent]) {
			swap(a[child], a[parent]);
			child = parent;
		} else {
			break;
		}
	}
}

void sift_down(int* a, int begin, int end) {
	int parent = begin, child;
	while (true) {
		child = 2 * parent + 1;
		if (child > end)
			break;
		if (child + 1 <= end) {
			child = (a[child] > a[child+1]) ? child : (child + 1);
		}
		if (a[parent] < a[child]) {
			swap(a[parent], a[child]);
			parent = child;
		} else {
			break;
		}
	}
}

void heapify(int* a, int begin, int end) {
	/*  O(nlogn) */
	int child = begin + 1, parent;
	while (child <= end) {
		sift_up(a, begin, child);
		child++;
	}
}

void opt_heapify(int* a, int begin, int end) {
	/*  O(n) */
	int parent = (end - 1) / 2;
	while (parent >= begin) {
		sift_down(a, parent, end);
		parent--;
	}
}

void heap_sort(int* a, int begin, int end) {
	if (NULL == a || begin >= end)
		return;
	
	// heapify(a, begin, end);
	opt_heapify(a, begin, end);
	
	while (end > begin) {
		swap(a[begin], a[end]);
		end--;
		sift_down(a, begin, end);
	}
}

int main() {
	
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	
	// int a[] = {1, 234, 5634, 2, 1, 3, 3412, 4, 1234, 312};
	// int n = sizeof(a) / sizeof(a[0]);
	int n = 1000000;
	int* a = (int*)malloc(sizeof(int)*n);
	srand(111);
	for (int i=0; i<n; i++)
		a[i] = rand();
	
	clock_t t;
	t = clock();
	
	heap_sort(a, 0, n-1);
	
	t = clock() - t;
	
	printf("(%d)\n", check(a, n));
	printf("%f seconds\n", ((float)t)/CLOCKS_PER_SEC);
	
	return 0;
}