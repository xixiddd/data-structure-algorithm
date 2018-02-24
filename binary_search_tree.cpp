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
	TreeNode* left;
	TreeNode* right;
	// TreeNode* parent;
	TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

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
	
	if (val < root->val)
		root->left = BST_insert(root->left, val);
	else
		root->right = BST_insert(root->right, val);
	
	return root;
}

TreeNode* BST_construct(int* a, int n) {
	/*
	 a : array
	 n : length of array
	 */
	TreeNode* root = NULL;
	for (int i=0; i<n; i++)
		root = BST_insert(root, a[i]);
	return root;
}

TreeNode* BST_find_parent(TreeNode* root, TreeNode* t, int* lr) {
	if (NULL == root || t == root)
		return NULL;
	
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* p = q.front();
		q.pop();
		if (p->left == t || p->right == t) {
			// 0 indicate left, 1 right
			if (NULL != lr)
				*lr = (p->left == t) ? 0 : 1;
			return p;
		}
			
		if (NULL != p->left)
			q.push(p->left);
		if (NULL != p->right)
			q.push(p->right);
	}
	
	return NULL;
}

TreeNode* BST_delete(TreeNode* root, int val) {
	TreeNode* del = BST_search(root, val);
	if (NULL == del)
		return root;
	
	TreeNode* t = NULL;
	TreeNode* p = NULL;
	if (NULL != del->left && NULL != del->right) {
		// case 1: has two child node
		t = del->right;
		while (NULL != t->left)
			t = t->left;
		del->val = t->val;
		
		p = BST_find_parent(del->right, t, NULL);
		if (NULL == p) {
			// del->right = t
			del->right = t->right;
		} else {
			// del->right retain
			// t->right NULL or not
			p->left = t->right;
		}
	} else {
		int lr;
		p = BST_find_parent(root, del, &lr);
		if (NULL == p) {
			/*  del is root  */
			root = (del->left != NULL) ? del->left : del->right;
			return root;
		}
		// case 2: has one child node
		if (NULL != del->left)
			(!lr) ? (p->left = del->left) : (p->right = del->left);
		else if (NULL != del->right)
			(!lr) ? (p->left = del->right) : (p->right = del->right);
		// case 3: has no child node
		else
			(!lr) ? (p->left = NULL) : (p->right = NULL);
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

int main() {
	
	// int a[] = {12, 324, 42, 42, 5, 74, 534, 543, 9};
	// int n = sizeof(a) / sizeof(a[0]);
	
	// TreeNode* root = BST_construct(a, n);
	
	TreeNode* root = new TreeNode(0);
	// root->left = new TreeNode(-2);
	// root->right = new TreeNode(2);
	// root->left->left = new TreeNode(-6);
	// root->left->right = new TreeNode(0);
	// root->right->left = new TreeNode(0);
	// root->right->right = new TreeNode(6);
	
	string info;
	info = BST_verify(root) ? "BST" : "NOT BST";
	printf("%s\n", &info[0]);
	in_order(root);
	
	root = BST_insert(root, 1);
	root = BST_insert(root, -1);
	
	info = BST_verify(root) ? "BST" : "NOT BST";
	printf("\n%s\n", &info[0]);
	in_order(root);
	
	root = BST_delete(root, 0);
	info = BST_verify(root) ? "BST" : "NOT BST";
	printf("\n%s\n", &info[0]);
	in_order(root);
	
	return 0;
}
