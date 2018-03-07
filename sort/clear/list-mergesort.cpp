#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<cstring>
#include<cassert>
#include<climits>
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
#include <chrono>

using namespace std;

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

ListNode* merge_list(ListNode* head_1, ListNode* head_2) {
	if (NULL == head_1) return head_2;
	if (NULL == head_2) return head_1;
	ListNode* p = head_1;
	ListNode* q = head_2;
	ListNode* head = NULL;
	ListNode* tail = NULL;
	while (p != NULL && q != NULL) {
		if (p->val < q->val) {
			if (NULL == head) {
				head = p;
				tail = p;
			} else {
				tail->next = p;
				tail = tail->next;
			}
			p = p->next;
		} else {
			if (NULL == head) {
				head = q;
				tail = q;
			} else {
				tail->next = q;
				tail = tail->next;
			}
			q = q->next;
		}
		tail->next = NULL;
	}
	
	if (p != NULL)
		tail->next = p;
	if (q != NULL)
		tail->next = q;
	
	return head;
}

int get_len(ListNode* head) {
	int c = 0;
	while (head != NULL) {
		c++;
		head = head->next;
	}
	return c;
}

ListNode* move(ListNode* head, int steps) {
	while (head != NULL && head->next != NULL && steps > 0) {
		head = head->next;
		steps--;
	}
	return head;
}

ListNode* get_tail(ListNode* head) {
	while (head != NULL && head->next != NULL)
		head = head->next;
	return head;
}

ListNode* non_rec(ListNode* head) {
	if (NULL == head || NULL == head->next)
		return head;
	
	int c = get_len(head);
	int base = 1;
	ListNode* p = NULL;
	ListNode* q = NULL;
	
	ListNode* tail = NULL;
	ListNode* nh = NULL;/*  next head */
	ListNode* pre_tail = NULL;
	
	while (c > 1) {
		p = head;
		pre_tail = NULL;
		while (p != NULL) {
			tail = move(p, base-1);
			q = tail->next;
			tail->next = NULL;
			
			if (NULL == q) {
				pre_tail->next = p;
				break;
			}
			
			tail = move(q, base-1);
			nh = tail->next;
			tail->next = NULL;
			
			p = merge_list(p, q);
			
			if (pre_tail != NULL)
				pre_tail->next = p;
			else
				head = p;
			pre_tail = get_tail(p);
			
			p = nh;
		}
		
		c = c / 2 + c % 2;
		base *= 2;
	}
	
	return head;
}

ListNode* split(ListNode* head) {
	ListNode* p = head;
	ListNode* q = head->next->next;
	while (q != NULL && q->next != NULL) {
		p = p->next;
		q = q->next->next;
	}
	q = p->next;
	/*  do split */
	p->next = NULL;
	return q;
}

ListNode* rec(ListNode* head) {
	if (NULL == head || NULL == head->next)
		return head;
	
	ListNode* head_1 = NULL;
	ListNode* head_2 = NULL;
	head_1 = head;
	head_2 = split(head);
	head_1 = rec(head_1);
	head_2 = rec(head_2);
	head = merge_list(head_1, head_2);
	
	return head;
}

int main() {
	
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	
	srand(time(NULL));
	int n;
	int i;
	// scanf("%d", &n);
	int t = 1000;
	while (t--) {
		n = rand() % 10000;
		ListNode* head = new ListNode(rand()%1000);
		ListNode* tail = head;
		for (i=0; i<n-1; i++) {
			tail->next = new ListNode(rand()%1000);
			tail = tail->next;
		}
		
		// head = rec(head);
		head = non_rec(head);
		
		tail = head;
		while (tail != NULL && tail->next != NULL) {
			assert(tail->val <= tail->next->val);
			tail = tail->next;
		}
	}
	
	return 0;
}
