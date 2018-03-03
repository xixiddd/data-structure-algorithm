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

struct TreeNode {
	int val;
	int h;
	int rc;/*  right subtree size */
	TreeNode* left;
	TreeNode* right;
	TreeNode (int x) : val(x), h(1), rc(0), left(NULL), right(NULL) {}
};

int naive(int* a, int n) {
	int inv = 0;
	for (int i=0; i<n; i++)
		for (int j=i+1; j<n; j++)
			if (a[j] < a[i])
				inv++;
	return inv;
}

int get_h(TreeNode* root) {
	if (NULL == root)
		return 0;
	return root->h;
}

int get_rc(TreeNode* root) {
	if (NULL == root)
		return 0;
	return root->rc;
}

int get_bf(TreeNode* root) {
	if (NULL == root)
		return 0;
	return get_h(root->right) - get_h(root->left);
}

TreeNode* left_rotate(TreeNode* x) {
	TreeNode* z = x->right;
	TreeNode* t23 = z->left;
	
	/*  update rc before rotation */
	x->rc -= (1 + get_rc(z));
	
	z->left = x;
	x->right = t23;
	
	x->h = max(get_h(x->left), get_h(x->right)) + 1;
	z->h = max(get_h(z->left), get_h(z->right)) + 1;

	return z;
}

TreeNode* right_rotate(TreeNode* x) {
	TreeNode* z = x->left;
	TreeNode* t23 = z->right;
	
	z->rc += (1 + get_rc(x));
	
	z->right = x;
	x->left = t23;
	
	x->h = max(get_h(x->left), get_h(x->right)) + 1;
	z->h = max(get_h(z->left), get_h(z->right)) + 1;
	
	return z;
}

TreeNode* avl_insert(TreeNode* root, int val, int* inv) {
	if (NULL == root)
		return new TreeNode(val);
	
	/*  insert into AVL tree */
	if (val < root->val) {
		*inv += (1 + get_rc(root));
		root->left = avl_insert(root->left, val, inv);
	} else {
		root->right = avl_insert(root->right, val, inv);
		/*  tricky & subtle here */
		root->rc += 1;
	}
	/*  after insertion, update height and then, check balance factor */
	root->h = max(get_h(root->left), get_h(root->right)) + 1;
	
	int balance = get_bf(root);
	if (2 == balance && 1 == get_bf(root->right)) {
		root = left_rotate(root);
	} else if (2 == balance && -1 == get_bf(root->right)) {
		root->right = right_rotate(root->right);
		root = left_rotate(root);
	} else if (-2 == balance && -1 == get_bf(root->left)) {
		root = right_rotate(root);
	} else if (-2 == balance && 1 == get_bf(root->left)) {
		root->left = left_rotate(root->left);
		root = right_rotate(root);
	}
	/*  if |balance| <= 1, do nothing */
	
	return root;
}

void pre_order(TreeNode* root) {
	if (NULL == root)
		return;
	printf(" %d(%d) ", root->val, root->rc);
	pre_order(root->left);
	pre_order(root->right);
}

int main() {
	
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	
	int n = 10000;
	// scanf("%d", &n);
	int inv = 0;
	int* a = (int*)malloc(sizeof(int)*n);
	TreeNode* root = NULL;
	for (int i=0; i<n; i++) {
		a[i] = rand() % 1000;
		// scanf("%d", &a[i]);
		root = avl_insert(root, a[i], &inv);
	}
	// pre_order(root);
	
	int answer = naive(a, n);
	printf("\n%d %d\n", inv, answer);
	assert(inv == answer);
	
	return 0;
}

/*  Count inversions in an array (Using Self-Balancing BST)
	reference : https://www.geeksforgeeks.org/count-inversions-in-an-array-set-2-using-self-balancing-bst/
	
	非常精妙的（逆序数）计数方法，在插入的时候，
	若往右边走，则计数不变，只更新当前结点的 rc ；
	若往左边走，则计数增加 (1 + p->rc) ，即，当前结点本身，加上其右子树的大小；
	
	原文中维护的是整棵树的 size ，这里，维护右子树的 size 。
	维护整棵树的 size 能让代码更加清晰
	
	复杂度为 O(nlogn)
 */
