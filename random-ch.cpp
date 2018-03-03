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

int gen_5() {
	return rand() % 5 + 1;
}

int gen_7() {
	int r;
	do {
		r = 5 * (gen_5() - 1) + gen_5();
		/*  r \in [1, 25] */
	} while(r > 21);
	return r % 7 + 1;
}

int gen_100() {
	int r;
	do {
		r = 25 * (gen_5() - 1) + 5 * (gen_5() - 1) + gen_5();
		/*  r \in [1, 125] */
	} while(r > 100);
	return r % 100 + 1;
}

int main() {
	
	srand(time(NULL));
	int n = 1000000;
	int i;
	int c[7] = {0};
	int cc[100] = {0};
	for (i=0; i<n; i++) {
		// c[gen_7()-1]++;
		cc[gen_100()-1]++;
	}
	int mmin = n + 1, mmax = -1;
	for (i=0; i<100; i++) {
		printf("%d: %d\n", i+1, cc[i]);
		if (mmin > cc[i]) mmin = cc[i];
		if (mmax < cc[i]) mmax = cc[i];
	}
	
	printf("diff: %d\n", mmax-mmin);
	
	return 0;
}

/*  给定一个随机（均匀）生成整数 1-5 的函数 gen_5 ，构造一个随机生成整数 1-7 的函数 gen_7 。
	reference : https://stackoverflow.com/questions/137783/expand-a-random-range-from-1-5-to-1-7?page=1&tab=votes#tab-top
	
	思路：
	r = 5 * (gen_5() - 1) + gen_5() 然后 rejection sampling ，去掉 22-25 的整数
	Q1：为什么是保留前 21 个？
	A1：因为 21 能够被 7 整除；
	
	Q2：保留前 14 个，或者前 7 个整数是否可行？
	A2：可以，但是最好保留尽可能多的整数，提高 rejection sampling 的效率；
	
	Q3：如何利用 gen_5 构造 gen_100 ？
	A3：构造 gen_7 是二维，因为 5^2 > 7 ，构造 gen_100 则（至少）需要三维， 5^3 > 100 ，
		r = 5^2 * (gen_5() - 1) + 5^1 * (gen_5() - 1) + gen_5()
		还是 rejection sampling ，去掉 101-125 的整数；
		
		实际上，通过增加 “维度” ，可以利用 gen_5 构造出任意大的 gen_N 。
 */
