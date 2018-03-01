#include "sort_utility.cpp"

void count_sort(int* a, int begin, int end) {
	if (a != NULL && begin < end) {
		int* b = (int*)malloc(sizeof(int)*(end-begin+1));
		memcpy(b, a, sizeof(int)*(end-begin+1));
		
		int i, j;
		int mmax = b[begin], mmin = b[begin];
		for (i=begin+1; i<=end; i++) {
			if (b[i] > mmax) mmax = b[i];
			if (b[i] < mmin) mmin = b[i];
		}
		
		int range = mmax - mmin + 1;
		int* c = (int*)malloc(sizeof(int)*range);
		memset(c, 0, sizeof(int)*range);
		
		for (i=begin; i<=end; i++)
			c[b[i]-mmin]++;
		
		int acc = 0, cur;
		for (i=0; i<range; i++) {
			cur = c[i];
			c[i] = acc;
			acc += cur;
		}
		
		for (i=begin; i<=end; i++) {
			a[c[b[i]-mmin]+begin] = b[i];
			c[b[i]-mmin]++;
		}
		
		delete b;
	}
}

int main() {
	
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	
	// int a[] = {1, 234, 5634, 2, 1, 3, 3412, 4, 1234, 312};
	// int n = sizeof(a) / sizeof(a[0]);
	int n = 1000000;
	int* a = (int*)malloc(sizeof(int)*n);
	int i;
	srand(111);
	for (i=0; i<n; i++)
		a[i] = rand() % 1000;
	
	clock_t t;
	t = clock();
	
	count_sort(a, 0, n-1);
	/*  quicker than sort */
	// sort(a, a+n);
	
	t = clock() - t;
	
	for (i=1; i<n; i++)
		assert(a[i-1] <= a[i]);
	
	
	printf("%f seconds\n", ((float)t)/CLOCKS_PER_SEC);
	
	return 0;
}