#include "sort_utility.cpp"

int min_index(int* a, int begin, int end) {
	int mmin = a[begin], index = begin;
	for (int i=begin+1; i<=end; i++) {
		if (a[i] < mmin) {
			mmin = a[i];
			index = i;
		}
	}
	return index;
}

void selection_sort(int* a, int begin, int end) {
	if (NULL == a || begin >= end)
		return;
	
	int i = begin - 1, j;
	while (i < end - 1) {
		j = min_index(a, i+1, end);
		swap(a[i+1], a[j]);
		i++;
	}
}

struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {};
};

ListNode* get_min_node(ListNode* head, ListNode** mp) {
	ListNode* pre = NULL;
	ListNode* min_p = head;
	ListNode* p = head;
	ListNode* q = head->next;
	while (q != NULL) {
		if (q->val < min_p->val) {
			pre = p;
			min_p = q;
		}
		p = q;
		q = q->next;
	}
	
	if (pre != NULL)
		pre->next = min_p->next;
	else
		head = head->next;
	
	*mp = min_p;
	return head;
}

ListNode* list_selection_sort(ListNode* head) {
	if (NULL == head)
		return NULL;
	
	ListNode* sh = NULL;
	ListNode* st = NULL;
	ListNode* mp = NULL;
	
	while (head != NULL) {
		
		head = get_min_node(head, &mp);
		
		if (NULL == sh) {
			sh = mp;
			st = mp;
		} else {
			st->next = mp;
			st = mp;
		}
	}
	st->next = NULL;
	
	return sh;
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
	
	int n = 100000;
	int* a = (int*)malloc(sizeof(int)*n);
	srand(time(NULL));
	for (int i=0; i<n; i++)
		a[i] = rand();
	
	ListNode* head = list_construct(a, n);
	head = NULL;
	
	clock_t t;
	t = clock();
	
	selection_sort(a, 0, n-1);
	// head = list_selection_sort(head);
	
	t = clock() - t;
	
	printf("(%d)\n", check(a, n));
	// printf("(%d)\n", check_list(head));
	printf("%f seconds\n", ((float)t)/CLOCKS_PER_SEC);
	
	return 0;
}