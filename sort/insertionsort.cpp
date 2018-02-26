#include "sort_utility.cpp"

void insertion_sort(int* a, int begin, int end) {
	/*  this implementation is NOT correct, it's always O(n^2)
		it make (<x) (>=x) x to (<x) x (>=x) 
		but the right insertion sort is to make
		(<=x) (>x) x to (<=x) x (>x)  */
	if (NULL == a || begin >= end)
		return;
	int i, j, k;
	int cache;
	for (i=begin+1; i<=end; i++) {
		j = begin;
		/*  not opt. (precisely, not correct)
			repeat element's move is not necessary 
			it's better to do from right to left */
		while (a[j] < a[i])
			j++;
		cache = a[i];
		for (k=i; k>j; k--)
			a[k] = a[k-1];
		a[j] = cache;
	}
}

void opt_insertion_sort(int* a, int begin, int end) {
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

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {};
};

ListNode* list_insert(ListNode* head, ListNode* x) {
	if (NULL == head)
		return x;
	if (NULL == x)
		return head;
	
	int v = x->val;
	ListNode* t = head;
	while (t->val < v) {
		if (NULL == t->next) {
			x->next = t->next;
			t->next = x;
			return head;
		}
		t = t->next;
	}
		
	x->next = t->next;
	t->next = x;
	x->val = t->val;
	t->val = v;
	
	return head;
}

ListNode* list_insertion_sort(ListNode* head) {
	if (NULL == head)
		return NULL;
	
	ListNode* r = head->next;
	head->next = NULL;
	ListNode* p = NULL;
	
	while (r != NULL) {
		p = r;
		r = r->next;
		head = list_insert(head, p);
	}
	
	return head;
}

ListNode* list_construct(int* a, int n) {
	if (n <= 0 || NULL == a)
		return NULL;
	ListNode* head = new ListNode(a[0]);
	ListNode* p = head;
	for (int i=1; i<n; i++) {
		p->next = new ListNode(a[i]);
		p = p->next;
	}
	return head;
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
	
	// insertion_sort(a, 0, n-1);
	opt_insertion_sort(a, 0, n-1);
	// ListNode* head = list_construct(a, n);
	// head = list_insertion_sort(head);
	
	t = clock() - t;
	
	printf("(%d)\n", check(a, n));
	// printf("(%d)\n", check_list(head));
	printf("%f seconds\n", ((float)t)/CLOCKS_PER_SEC);
	
	return 0;
}