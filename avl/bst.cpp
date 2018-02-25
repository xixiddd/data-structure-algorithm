
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

TreeNode* BST_delete(TreeNode* root, int val, TreeNode** n=NULL, TreeNode** x=NULL, int* LR=NULL) {
	TreeNode* del = BST_search(root, val);
	if (NULL == del) {
		if (x != NULL)
			*x = NULL;
		return root;
	}
	
	TreeNode* leftmost = NULL;
	TreeNode* p = NULL;
	if (NULL != del->left && NULL != del->right) {
		/*  case 1: The del node has two child nodes */
		leftmost = del->right;
		while (NULL != leftmost->left)
			leftmost = leftmost->left;
		
		if (n != NULL)
			*n = leftmost->right;
		if (x != NULL)
			*x = leftmost->parent;
		if (LR != NULL)
			*LR = (leftmost == del->right) ? 1 : 0;
		
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
		
		/*  take care that *n could be NULL */
		if (n != NULL)
			*n = (del->left != NULL) ? del->left : del->right;
		if (x != NULL)
			*x = del->parent;

		p = del->parent;
		if (NULL == p) {
			/*  del node is root */
			root = (del->left != NULL) ? del->left : del->right;
			/*  a secluded case, root is the only node of the whole tree */
			if (root != NULL)
				root->parent = NULL;
			delete del;
			return root;
			/*  in this case, LR could be ignored, because *x is NULL,
				and the loop in AVL_delete will break out */
		}
		
		int lr = (p->left == del) ? 0 : 1;
		if (LR != NULL)
			*LR = lr;
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

/*  using global variable, only O(1) auxiliary space needed */
int first, pre, cur;

bool BST_check(TreeNode* root) {
	/*  in-order traversal non-decreasing <=> potential tree is BST */
	if (NULL == root)
		return true;
	
	bool l, mid, r;
	l = BST_check(root->left);
	if (!l)
		return false;
	
	if (!first) {
		first = 1;
		pre = root->val;
		mid = true;
	} else {
		cur = root->val;
		mid = (cur >= pre);
	}
	if (!mid)
		return false;
	
	r = BST_check(root->right);
	return r;
	
	// return (l && mid && r);
}

bool BST_verify(TreeNode* root) {
	first = 0;
	return BST_check(root);
}

void check(TreeNode* root);


void check(TreeNode* root) {
	/*  Debug function: check whether parent pointer is manipulated correctly
		output the number of node whose parent is NULL
		i.e. check whether there is only one root */
	if (NULL == root) {
		printf("root: (1)\n");
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
	
	printf("root: (%d)\n", c);
}
