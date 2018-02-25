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
	/*  height & factor are for AVL tree,
		precisely, height is not necessary,
		the info that height provided is the same as factor provided */
	int height;
	int factor;
	TreeNode* left;
	TreeNode* right;
	TreeNode* parent;
	TreeNode(int x) : val(x), height(1), factor(0), left(NULL), right(NULL), parent(NULL) {}
};

/*  utility function for BST & AVL */

void pause() {
	string line;
	getline(cin, line);
}

void pre_order(TreeNode* root) {
	if (NULL == root)
		return;
	
	printf(" %d(%d) ", root->val, root->factor);
	pre_order(root->left);
	pre_order(root->right);
}

void in_order(TreeNode* root) {
	if (NULL == root)
		return;
	
	in_order(root->left);
	printf(" %d(%d) ", root->val, root->factor);
	in_order(root->right);
}

void assign_height(TreeNode* root) {
	if (NULL == root)
		return;
	
	assign_height(root->left);
	assign_height(root->right);
	
	int lh, rh;
	lh = (root->left != NULL) ? root->left->height : 0;
	rh = (root->right != NULL) ? root->right->height : 0;
	
	root->height = max(lh, rh) + 1;
	// if (root->factor != rh - lh)
		// printf("error\n");
}



