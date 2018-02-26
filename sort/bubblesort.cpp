#include "sort_utility.cpp"

void bubble_sort(int* a, int begin, int end) {
	/*  the OPT. version in wiki
		A very important fact is :
		after every pass, all elements after the last swap are sorted. */
	if (NULL == a || begin >= end)
		return;
	
	int i = begin, j = end, nj;
	do {
		nj = begin;
		for (i=begin; i<j; i++) {
			if (a[i] > a[i+1]) {
				swap(a[i], a[i+1]);
				nj = i;
			}
		}
		j = nj;
	} while (j > begin);
}


int main() {
	
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	
	// int a[] = {1, 234, 5634, 2, 1, 3, 3412, 4, 1234, 312};
	// int n = sizeof(a) / sizeof(a[0]);
	int n = 100000;
	int* a = (int*)malloc(sizeof(int)*n);
	srand(111);
	for (int i=0; i<n; i++)
		a[i] = rand();
	
	clock_t t;
	t = clock();
	
	bubble_sort(a, 0, n-1);
	
	t = clock() - t;
	
	printf("(%d)\n", check(a, n));
	printf("%f seconds\n", ((float)t)/CLOCKS_PER_SEC);
	
	return 0;
}