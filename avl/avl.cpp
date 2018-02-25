
bool AVL_verify(TreeNode* root) {
	/*  Assuming that the factor value of each node are set	
		if not, call assign_height() firstly */
	if (NULL == root)
		return true;
	
	if (root->factor != -1 && root->factor != 0 && root->factor != 1)
		return false;
	
	return AVL_verify(root->left) && AVL_verify(root->right);
}

TreeNode* AVL_search(TreeNode* root, int val) {
	return BST_search(root, val);
}

TreeNode* rotate_Left(TreeNode* x, TreeNode* z);
TreeNode* rotate_RightLeft(TreeNode* x, TreeNode* z);
TreeNode* rotate_Right(TreeNode* x, TreeNode* z);
TreeNode* rotate_LeftRight(TreeNode* x, TreeNode* z);

TreeNode* AVL_insert(TreeNode* root, int val) {
	/*  root is an AVL tree */
	if (NULL == root) {
		root = new TreeNode(val);
		return root;
	}
	
	TreeNode* x = root;
	TreeNode* z = NULL;
	while (true) {
		if (val < x->val) {
			if (x->left != NULL) {
				x = x->left;
			} else {
				z = new TreeNode(val);
				x->left = z;
				z->parent = x;
				break;
			}
		} else {
			if (x->right != NULL) {
				x = x->right;
			} else {
				z = new TreeNode(val);
				x->right = z;
				z->parent = x;
				break;
			}
		}
	}
	
	TreeNode* g;
	TreeNode* n;
	
	while (true) {
		
		/*  retracing from z to root  */
		
		x = z->parent;
		if (NULL == x)
			break;
		
		if (z == x->right) {
			if (x->factor > 0) {
				g = x->parent;
				/*  here, z->factor only in {+1, -1}  
					because z is set to be the last round x
					and once x->factor equal to 0, it will break */
				if (z->factor < 0) {
					n = rotate_RightLeft(x, z);
					// printf("right left rotate\n");
				} else {
					n = rotate_Left(x, z);
					// printf("left rotate\n");
				}
			} else if (x->factor < 0) {
				/*  the height of x has not changed, retracing could stop here */
				x->factor = 0;
				break;
			} else {
				/*  before inserting z, x is a leaf node  */
				x->factor = 1;
				z = x;
				continue;
			}
		} else {
			if (x->factor < 0) {
				g = x->parent;
				if (z->factor > 0) {
					n = rotate_LeftRight(x, z);
					// printf("left right rotate\n");
				} else {
					n = rotate_Right(x, z);
					// printf("right rotate\n");
				}
			} else if (x->factor > 0) {
				x->factor = 0;
				break;
			} else {
				x->factor = -1;
				z = x;
				continue;
			}
		}
		
		/*  after a rotation, adapt parent link 
			n is the new root of the rotated subtree 
			height(n) == height(x), so retracing could stop */
		n->parent = g;
		if (g != NULL) {
			if (x == g->left)
				g->left = n;
			else
				g->right = n;
			break;
		} else {
			root = n;
			// n->parent = NULL;
			break;
		}
		
	}
	
	return root;
}

TreeNode* AVL_delete(TreeNode* root, int val) {
	/*  root is an AVL tree  */
	/*  firstly, n is the del node 
		and then, n means "new"
		x is the parent of n */
	TreeNode* n = NULL;
	TreeNode* x = NULL;
	TreeNode* g = NULL;
	TreeNode* z = NULL;
	
	int b;
	int LR;
	root = BST_delete(root, val, &n, &x, &LR);
	
	while (true) {
		if (NULL == x)
			break;
		g = x->parent;
		
		if (NULL == n) {
			// printf("once\n");
			if (!LR) goto LEFT;
			else goto RIGHT;
		}
		
		if (n == x->left) {
			LEFT:
			// printf("LEFT\n");
			if (0 < x->factor) {
				// printf("rotate\n");
				z = x->right;
				b = z->factor;
				if (b < 0) {
					// printf("right left rotate\n");
					n = rotate_RightLeft(x, z);
				} else {
					// printf("left rotate\n");
					n = rotate_Left(x, z);
				}
			} else if (0 == x->factor) {
				// printf("break\n");
				x->factor = 1;
				break;
			} else {
				// printf("continue\n");
				n = x;
				n->factor = 0;
				x = g;
				continue;
			}
		} else {
			RIGHT:
			// printf("RIGHT\n");
			if (0 > x->factor) {
				z = x->left;
				b = z->factor;
				if (b > 0) {
					n = rotate_LeftRight(x, z);
					// printf("left right rotate\n");
				} else {
					n = rotate_Right(x, z);
					// printf("right rotate\n");
				}
			} else if (0 == x->factor) {
				x->factor = -1;
				break;
			} else {
				n = x;
				n->factor = 0;
				x = g;
				continue;
			}
		}
		
		n->parent = g;
		if (g != NULL) {
			if (x == g->left)
				g->left = n;
			else
				g->right = n;
			/*  b equal 0, which indicate after rotation,
				the height of the new subtree has not changed,
				and the retracing could be stop */
			if (0 == b)
				break;
		} else {
			root = n;
		}
		
		/*  The height of the rotated tree decrease by 1,
			retracing should be continue */
		x = g;
		continue;
	}
	
	return root;
}

/*  For the 4 rotation, check the picture in wiki, and it may be helpful */

TreeNode* rotate_Left(TreeNode* x, TreeNode* z) {
	TreeNode* t23 = z->left;
	x->right = t23;
	if (t23 != NULL)
		t23->parent = x;
	z->left = x;
	x->parent = z;
	// z->parent = 
	
	if (0 == z->factor) {
		/*  only for deletion */
		x->factor = 1;
		z->factor = -1;
	} else {
		/*  deletion and insertion */
		x->factor = 0;
		z->factor = 0;
	}
	
	return z;
}

TreeNode* rotate_RightLeft(TreeNode* x, TreeNode* z) {
	TreeNode* y = z->left;
	
	TreeNode* t3 = y->right;
	z->left = t3;
	if (t3 != NULL)
		t3->parent = z;
	y->right = z;
	z->parent = y;
	
	TreeNode* t2 = y->left;
	x->right = t2;
	if (t2 != NULL)
		t2->parent = x;
	y->left = x;
	x->parent = y;
	
	if (0 < y->factor) {
		x->factor = -1;
		z->factor = 0;
	} else if (0 == y->factor) {
		x->factor = 0;
		z->factor = 0;
	} else {
		x->factor = 0;
		z->factor = 1;
	}
	
	y->factor = 0;
	// y->parent = 
	return y;
}

TreeNode* rotate_Right(TreeNode* x, TreeNode* z) {
	TreeNode* t23 = z->right;
	x->left = t23;
	if (t23 != NULL)
		t23->parent = x;
	z->right = x;
	x->parent = z;
	
	if (0 == z->factor) {
		// only for deletion
		x->factor = -1;
		z->factor = 1;
	} else {
		x->factor = 0;
		z->factor = 0;
	}
	
	return z;
}

TreeNode* rotate_LeftRight(TreeNode* x, TreeNode* z) {
	TreeNode* y = z->right;
	
	TreeNode* t2 = y->left;
	z->right = t2;
	if (t2 != NULL)
		t2->parent = z;
	y->left = z;
	z->parent = y;
	
	TreeNode* t3 = y->right;
	x->left = t3;
	if (t3 != NULL)
		t3->parent = x;
	y->right = x;
	x->parent = y;
	
	if (0 < y->factor) {
		x->factor = 0;
		z->factor = -1;
	} else if (0 == y->factor) {
		x->factor = 0;
		z->factor = 0;
	} else {
		x->factor = 1;
		z->factor = 0;
	}
	
	y->factor = 0;
	// y->parent = 
	return y;
}

