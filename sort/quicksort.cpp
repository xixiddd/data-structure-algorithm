#include "sort_utility.cpp"

int median(int x, int y, int z) {
	int* arr = (int*)malloc(sizeof(int)*3);
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
	sort(arr, arr+3);
	return arr[1];
}

int get_pivot(int* a, int begin, int end) {
	int pivot;
	int x, y, z;
	x = a[begin];
	// to avoid integer overflow
	y = a[begin+(end-begin)/2];
	z = a[end];
	pivot = median(x, y, z);
	return pivot;
}

int naive_partition(int* a, int begin, int end) {
	/* Lomuto’s version
	   degrade to O(n^2) when:
	   1. the input array is already sorted
	   2. all elements are identity
	 */
	// the index "end" is included, i.e. [begin, end]
	int pivot = a[end];
	int i, j;
	i = begin - 1;
	for (j=begin; j<end; j++) {
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		}
	}
	// put the selected pivot into the right position
	swap(a[i+1], a[end]);
	return (i+1);
}

void naive_quicksort(int* a, int begin, int end) {
	if (begin < end) {
		int p = naive_partition(a, begin, end);
		naive_quicksort(a, begin, p-1);
		naive_quicksort(a, p+1, end);
	}
}

int partition(int* a, int begin, int end) {
	/* Hoare’s version
	   compared to Lomuto’s version,
	   this one creates efficient partitions even when all values are equal
	 */
	
	int pivot = a[begin];// original version
	// int pivot = get_pivot(a, begin, end);// opt in pivot selection
	int i, j;
	i = begin - 1;
	j = end + 1;
	for (;;) {
		do {
			i++;
		} while (a[i] < pivot);
		
		do {
			j--;
		} while (a[j] > pivot);
		// wiki is right, p185 in Introduce to Algorithm(3rd) is wrong
		
		if (i >= j)
			return j;
		// why return j, not i
		// only "return j" work correctly, confused about it
		
		swap(a[i], a[j]);
	}
}

void quicksort(int* a, int begin, int end) {
	if (begin < end) {
		int p = partition(a, begin, end);
		quicksort(a, begin, p);
		quicksort(a, p+1, end);
	}
}

int opt_partition(int* a, int begin, int end) {
	return partition(a, begin, end);
}

void opt_insertion_sort(int* a, int begin, int end);

void opt_quicksort(int* a, int begin, int end) {
	// when end - begin < K, use insert sort
	if (begin < end) {
		if (end - begin < 10) {
			opt_insertion_sort(a, begin, end);
		} else {
			int p = opt_partition(a, begin, end);
			opt_quicksort(a, begin, p);
			opt_quicksort(a, p+1, end);
		}
	}
}

int repeat_partition(int* a, int begin, int end, int pivot, int* left, int* right) {
	/* it does not seem to be a good implementation
	 */
	int i, j;
	int c = 0;
	i = begin - 1;
	for (j=begin; j<=end; j++) {
		if (a[j] < pivot) {
			i++;
			swap(a[i], a[j]);
		} else if (a[j] == pivot) {
			c++;
		}
	}
	*left = i + 1;
	*right = i + c;
	for (j=i+1; j<=end; j++) {
		if (a[j] == pivot) {
			i++;
			swap(a[i], a[j]);
			c--;
			if (0 == c)
				break;
		}
	}
}

void repeat_qsort(int* a, int begin, int end) {
	if (begin < end) {
		int pivot = get_pivot(a, begin, end);
		int left, right;
		repeat_partition(a, begin, end, pivot, &left, &right);
		repeat_qsort(a, begin, left-1);
		repeat_qsort(a, right+1, end);
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
	
	// quicksort(a, 0, n-1);
	
	clock_t t;
	t = clock();
	
	// naive_quicksort(a, 0, n-1);
	// quicksort(a, 0, n-1);
	opt_quicksort(a, 0, n-1);
	// repeat_qsort(a, 0, n-1);
	
	t = clock() - t;
	
	printf("(%d)\n", check(a, n));
	printf("%f seconds\n", ((float)t)/CLOCKS_PER_SEC);
	
	return 0;
}

void opt_insertion_sort(int* a, int begin, int end) {
	/*  From insertionsort.cpp */
	if (NULL == a || begin >= end)
		return;
	
	int i = begin + 1, j, cache;
	while (i <= end) {
		cache = a[i];
		j = i - 1;
		/*  in this way, repeat element would not move */
		while (j >= begin && a[j] > cache) {
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = cache;
		i++;
	}
}
