#include "sort_utility.cpp"

const int maxn = 1000000 + 5;
int arr[maxn];/* O(n) auxiliary space */

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

void pl(ListNode* head, ListNode* tail=NULL) {
	ListNode* p = head;
	while (p != tail) {
		printf(" %d ", p->val);
		p = p->next;
	}
	(NULL == tail)?printf("^\n"):printf("%d^\n", tail->val);
}

bool check_list(ListNode* head) {
	if (NULL == head)
		return true;
	ListNode* p = head;
	while (p->next != NULL) {
		if (p->val > (p->next)->val)
			return false;
		p = p->next;
	}
	return true;
}

void merge(int* a, int begin, int middle, int end) {
	/*  merge [begin, middle] & [middle->next, end],
		workhorse for top_down_mergesort and bottom_up_mergesort */
	int i = begin, j = middle + 1, k = 0;
	while (i <= middle && j <= end)
		arr[k++] = (a[i] < a[j])?a[i++]:a[j++];
	while (i <= middle)
		arr[k++] = a[i++];
	while (j <= end)
		arr[k++] = a[j++];
	memcpy(a+begin, arr, sizeof(int)*k);
}

void top_down_mergesort(int* a, int begin, int end) {
	if (begin < end) {
		/* To avoid integer overflow */
		int middle = begin + (end - begin) / 2;
		top_down_mergesort(a, begin, middle);
		top_down_mergesort(a, middle+1, end);
		merge(a, begin, middle, end);
	}
}

void bottom_up_mergesort(int* a, int begin, int end) {
	if (begin < end) {
		int c = end - begin + 1;
		int base = 2;
		int i, middle;
		while (c != 1) {
			for (i=begin; i<=end; i+=base) {
				middle = i + base / 2 - 1;
				if (middle < end)
					merge(a, i, middle, min(i+base-1, end));
			}
			base *= 2;
			c = c / 2 + c % 2;
		}
	}
}

vector<ListNode*> merge_list(ListNode* head, ListNode* middle, ListNode* tail) {
	
	/* special case for bottom_up_list_mergesort */
	if (middle == tail) {
		vector<ListNode*> v = {head, tail};
		return v;
	}
	
	/* [head, middle] and [middle->next, tail] are two sorted list */
	ListNode* tail_next = tail->next;
	ListNode* q = NULL;
	ListNode* p = middle->next;
	NEXT:
	while (p != tail_next) {
		
		q = head;
		while (q->val <= p->val) {
			q = q->next;
			if (q == middle->next) {
				middle = middle->next;
				p = middle->next;
				goto NEXT;
			}
		}
		
		middle->next = p->next;
		p->next = q->next;
		q->next = p;
		
		int cache = p->val;
		p->val = q->val;
		q->val = cache;
		
		p = middle->next;
	}
	
	tail = middle;
	vector<ListNode*> v = {head, tail};
	return v;
}

ListNode* find_middle(ListNode* head, ListNode* tail) {
	ListNode* middle = head;
	ListNode* q = head;
	while (q != tail && q->next != tail) {
		middle = middle->next;
		q = q->next->next;
	}
	return middle;
}

vector<ListNode*> top_down_list_mergesort(ListNode* head, ListNode* tail) {
	vector<ListNode*> v;
	
	/* illegal input */
	if (NULL == head || NULL == tail)
		return v;
	
	if (head == tail) {
		// printf(" *%d \n", head->val);
		v.push_back(head);
		v.push_back(tail);
		return v;
	}
	
	ListNode* middle = find_middle(head, tail);
	ListNode* middle_next = middle->next;
	// printf("%d - %d - %d\n", head->val, middle->val, tail->val);
	
	v = top_down_list_mergesort(head, middle);
	head = v[0];
	middle = v[1];
	// pl(head, middle);
	
	v = top_down_list_mergesort(middle_next, tail);
	middle->next = v[0];
	tail = v[1];
	// pl(middle->next, tail);
	
	// pl(head, tail);
	v = merge_list(head, middle, tail);
	
	return v;
}

int get_len(ListNode* head) {
	int len = 0;
	while (head != NULL) {
		len++;
		head = head->next;
	}
	return len;
}

ListNode* move(ListNode* head, int steps) {
	/* normal moves or the last element of linked list */
	if (NULL == head)
		return NULL;
	
	while ((steps--) > 0 && head->next != NULL)
		head = head->next;
	return head;
}

vector<ListNode*> bottom_up_list_mergesort(ListNode* head, ListNode* tail) {
	vector<ListNode*> v;
	
	if (head == tail) {
		v.push_back(head);
		v.push_back(tail);
		return v;
	}
	
	ListNode* p = NULL;
	ListNode* pre = NULL;
	int c = get_len(head);
	int base = 2;
	int middle;
	vector<ListNode*> vv;
	
	while (c != 1) {
		p = head;
		while (p != NULL) {
			middle = base / 2 - 1;
			vv = merge_list(p, move(p, middle), move(p, base-1));
			if (NULL == pre) {
				head = vv[0];
			}
			pre = vv[1];
			// p = move(p, base);
			p = pre->next;
		}
		base *= 2;
		c = c / 2 + c % 2;
	}
	
	v.push_back(head);
	v.push_back(pre);
	return v;
}

ListNode* create_list(int* a, int n) {
	if (n <= 0)
		return NULL;
	ListNode* head = new ListNode(a[0]);
	ListNode* p = head;
	for (int i=1; i<n; i++) {
		p->next = new ListNode(a[i]);
		p = p->next;
	}
	return head;
}

int main() {
	
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	
	// int a[] = {1, 234, 5634, 2, 1, 3, 3412, 4, 1234, 312};
	// int n = sizeof(a) / sizeof(a[0]);
	int n = maxn - 5;
	int* a = (int*)malloc(sizeof(int)*n);
	srand(111);
	for (int i=0; i<n; i++)
		a[i] = rand();
	
	
	ListNode* head = create_list(a, n);
	ListNode* tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	
	clock_t t;
	t = clock();
	
	// top_down_mergesort(a, 0, n-1);
	bottom_up_mergesort(a, 0, n-1);
	
	// head = top_down_list_mergesort(head, tail)[0];
	// head = bottom_up_list_mergesort(head, tail)[0];
	
	t = clock() - t;
	
	printf("(%d)\n", check(a, n));
	// printf("(%d)\n", check_list(head));
	
	printf("%f seconds\n", ((float)t)/CLOCKS_PER_SEC);
	
	return 0;
}

/*  Performance notes:
	two array version top_down_mergesort & bottom_up_mergesort have
	the equivalent speed, for 10^5 element, cost 0.016s ;
	two linked list version are very inefficient, for 10^5 element,
	top_down_list_mergesort takes 70s, bottom_up_list_mergesort 60s .
  */