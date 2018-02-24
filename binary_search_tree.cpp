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

struct TreeNode {
	int val;
	/*  height & factor for AVL tree */
	int height;
	int factor;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	TreeNode(int x) : val(x), height(1), factor(0), left(NULL), right(NULL), parent(NULL) {}
};

void pre_order(TreeNode* root) {
	if (NULL == root)
		return;
	
	printf(" %d ", root->val);
	pre_order(root->left);
	pre_order(root->right);
}

void in_order(TreeNode* root) {
	if (NULL == root)
		return;
	
	in_order(root->left);
	printf(" %d ", root->val);
	in_order(root->right);
}

TreeNode* BST_search(TreeNode* root, int val) {
	// traverse the tree
	if (NULL == root)
		return NULL;
	
	if (val == root->val)
		return root;
	TreeNode* l = BST_search(root->left, val);
	TreeNode* r = BST_search(root->right, val);
	return (NULL != l) ? l : r;
}

TreeNode* BST_insert(TreeNode* root, int val) {
	if (NULL == root)
		return new TreeNode(val);
	
	TreeNode* x = root;
	while (true) {
		if (val < x->val) {
			if (NULL == x->left) {
				x->left = new TreeNode(val);
				x->left->parent = x;
				break;
			}
			x = x->left;
		} else {
			if (NULL == x->right) {
				x->right = new TreeNode(val);
				x->right->parent = x;
				break;
			}
			x = x->right;
		}
	}
	
	return root;
}

TreeNode* BST_construct(int* a, int n) {
	TreeNode* root = NULL;
	for (int i=0; i<n; i++)
		root = BST_insert(root, a[i]);
	return root;
}

TreeNode* BST_delete(TreeNode* root, int val) {
	TreeNode* del = BST_search(root, val);
	if (NULL == del)
		return root;
	
	TreeNode* leftmost = NULL;
	TreeNode* p = NULL;
	if (NULL != del->left && NULL != del->right) {
		/*  case 1: The del node has two child nodes */
		leftmost = del->right;
		while (NULL != leftmost->left)
			leftmost = leftmost->left;
		del->val = leftmost->val;
		
		if (del->right == leftmost) {
			del->right = leftmost->right;
			if (leftmost->right != NULL)
				leftmost->right->parent = del;
		} else {
			p = leftmost->parent;
			p->left = leftmost->right;
			if (leftmost->right != NULL)
				leftmost->right->parent = p;
		}
		delete leftmost;
	} else {
		int lr;
		p = del->parent;
		if (NULL == p) {
			/*  del node is root */
			root = (del->left != NULL) ? del->left : del->right;
			root->parent = NULL;
			delete del;
			return root;
		}
		lr = (p->left == del) ? 0 : 1;
		/*  case 2: has one child node */
		if (NULL != del->left) {
			(!lr) ? (p->left = del->left) : (p->right = del->left);
			del->left->parent = p;
		} else if (NULL != del->right) {
			(!lr) ? (p->left = del->right) : (p->right = del->right);
			del->right->parent = p;
		} else {
			/*  case 3: has no child node */
			(!lr) ? (p->left = NULL) : (p->right = NULL);
		}
		delete del;
	}
	
	return root;
}

// O(1) auxiliary space overhead
int first, pre, cur;

bool BST_check(TreeNode* root) {
	// in-order traversal non-decreasing <=> potential tree is BST
	if (NULL == root)
		return true;
	
	bool l, i = true, r;
	l = BST_check(root->left);
	if (!first) {
		first = 1;
		pre = root->val;
	} else {
		cur = root->val;
		i = (cur >= pre);
	}
	r = BST_check(root->right);
	
	return (l && i && r);
}

bool BST_verify(TreeNode* root) {
	first = 0;
	return BST_check(root);
}

void check(TreeNode* root);

int main() {
	
	int n = 1000;
	int* a = (int*)malloc(sizeof(int)*n);
	srand(111);
	for (int i=0; i<n; i++)
		a[i] = rand();
	TreeNode* root = BST_construct(a, n);
	
	string info;
	info = BST_verify(root)?"BST":"NOT BST";
	printf("%s\n", &info[0]);
	// in_order(root);
	
	root = BST_insert(root, 1);
	root = BST_insert(root, -1);
	
	info = BST_verify(root)?"BST":"NOT BST";
	printf("\n%s\n", &info[0]);
	// in_order(root);
	
	root = BST_delete(root, root->val);
	info = BST_verify(root)?"BST":"NOT BST";
	printf("\n%s\n", &info[0]);
	// in_order(root);
	
	check(root);
	
	return 0;
}

void check(TreeNode* root) {
	/*  print the number of node whose parent is NULL
		i.e. check whether there is only one root */
	if (NULL == root) {
		printf("(1)\n");
		return;
	}
	
	int c = 0;
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* h = q.front();
		q.pop();
		if (NULL == h->parent)
			c++;
		if (h->left != NULL) q.push(h->left);
		if (h->right != NULL) q.push(h->right);
	}
	
	printf("(%d)\n", c);
}
