#include "avl.h"
#include "bst.cpp"
#include "avl.cpp"

void BST_test() {
	clock_t t;
	t = clock();
	
	TreeNode* root = NULL;
	int n = 100000;
	// srand(111);
	for (int i=0; i<n; i++) {
		if (rand() > RAND_MAX / 3)
			root = BST_insert(root, rand());
		else
			root = BST_delete(root, rand());
	}
	t = clock() - t;
	// TreeNode* root = BST_insert(NULL, 0);
	
	printf("BST verify: (%d)\n", BST_verify(root));
	// in_order(root);
	check(root);
	
	// root = BST_delete(root, root->val);
	// root = BST_delete(root, root->val);
	// root = BST_delete(root, 2 * RAND_MAX);
	// printf("BST verify: (%d)\n", BST_verify(root));
	// in_order(root);
	// check(root);
	
	assign_height(root);
	int h = (root != NULL) ? root->height : 0;
	printf("height: %d\n", h);
	
	printf("%f seconds\n", ((float)t) / CLOCKS_PER_SEC);
}

void AVL_test() {
	clock_t t;
	t = clock();
	
	TreeNode* root = NULL;
	int n = 100000;
	
	for (int i=0; i<n; i++) {
		if (rand() > RAND_MAX / 3)
			root = AVL_insert(root, rand());
		else
			root = AVL_delete(root, rand());
	}
	
	// root = AVL_insert(root, 100);
	// root = AVL_insert(root, 50);
	// root = AVL_insert(root, 200);
	// root = AVL_insert(root, 25);
	// root = AVL_insert(root, 75);
	// root = AVL_insert(root, 80);
	// pre_order(root);printf("\n");
	
	// root = AVL_delete(root, 50);
	// root = AVL_delete(root, 200);
	
	// printf("AVL verify: (%d)\n", AVL_verify(root));
	// pre_order(root);
	// in_order(root);
	
	t = clock() - t;
	
	printf("AVL verify: (%d)\n", AVL_verify(root));
	assign_height(root);
	int h = (root != NULL) ? root->height : 0;
	printf("height: %d\n", h);
	
	printf("%f seconds\n", ((float)t) / CLOCKS_PER_SEC);
}

int main() {
	
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	
	srand(111);
	BST_test();
	AVL_test();
	
	return 0;
}
