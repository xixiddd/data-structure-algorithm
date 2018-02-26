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

void pause() {
	string line;
	getline(cin, line);
}

void pa(int* a, int n) {
	for (int i=0; i<n; i++)
		printf(" %d ", a[i]);
	printf("\n");
}

bool check(int* a, int n) {
	for (int i=1; i<n; i++)
		if (a[i] < a[i-1])
			return false;
	return true;
}
