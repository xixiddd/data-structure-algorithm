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

const int maxn = 100000 + 5;

bool check_arr(int* a, int n) {
	for (int i=1; i<n; i++)
		if (a[i-1] > a[i])
			return false;
	return true;
}

bool bs(int* a, int begin, int end, int val) {
	if (NULL == a || begin > end)
		return false;
	else {
		int middle = begin + (end - begin) / 2;
		if (a[middle] == val)
			return true;
		else if (a[middle] > val)
			return bs(a, begin, middle-1, val);
		else
			return bs(a, middle+1, end, val);
		/*  inspiration of processing index(middle-1, middle+1) is from merge_sort
			do like this could make the codes concise and clear .
			*/
	}
}

bool iter_bs(int* a, int begin, int end, int val) {
	if (NULL == a || begin > end)
		return false;
	else {
		int i = begin, j = end, middle;
		while (i <= j) {
			middle = i + (j - i) / 2;
			if (a[middle] == val)
				return true;
			else if (a[middle] > val)
				j = middle - 1;
			else
				i = middle + 1;
		}
		return false;
	}
}

int main() {
	int n = maxn - 5;
	int* a = (int*)malloc(sizeof(int)*n);
	srand(time(NULL));
	for (int i=0; i<n; i++)
		a[i] = rand();
	sort(a, a+n);
	printf("(%d)\n", check_arr(a, n));
	int val = rand();
	printf("val = %d\n", val);
	
	// int a[] = {3};
	// int n = sizeof(a) / sizeof(a[0]);
	// int val = 1;
	
	cout << bs(a, 0, n-1, val) << endl;
	cout << iter_bs(a, 0, n-1, val) << endl;
	cout << binary_search(a, a+n, val);
	return 0;
}

/*  Test cases:
	arr = {1}, val = 1;
	arr = {1}, val = 2;
	arr = {1, 6}, val = 1;
	arr = {1, 6}, val = 6;
	arr = {1, 6}, val = -1;
	arr = {1, 6}, val = 5;
	arr = {1, 6}, val = 7;
	arr = {1, 6, 9}, val = 8;
	
	*/
