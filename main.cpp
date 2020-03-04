#include <iostream>

using namespace std;

struct Node {
	int key;
	Node *left, *right;
};

Node* newNode(int item) {
	Node *temp = new Node;
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

void inorder(Node *root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

Node* insert(Node *root, int key) {
	if (root == NULL) 
		return newNode(key);
	if (key < root->key) 
		root->left = insert(root->left, key);
	else if (key > root->key) 
		root->right = insert(root->right, key);
	return root;
}

Node* minValueNode(Node *node) {
	Node *current = new Node;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

Node* deleteNode(Node *root, int key) {
	if (root == NULL)
		return root;

	if (key < root->key) {
		root->left = deleteNode(root->left, key);
		return root;
	}
	else if (key > root->key) {
		root->right = deleteNode(root->right, key);
		return root;
	}
	else {
		if (root->left == NULL) {
			Node *temp = new Node;
			temp = root->right;
			delete root; 
			return temp;
		}
		else if (root->right == NULL) {
			Node *temp = new Node;
			temp = root->left;
			delete root;
			return temp;
		}
		// now we are at the case of node with two children
		// Get the inorder successor (smallest in the right subtree)
		Node *temp = new Node;
		temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node
		root->key = temp->key;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}

bool searchNode(Node *root, int key) {
	if (root == NULL)
		return false;
	else if (root->key == key)
		return true;
	else if (root->key <= key)
		return searchNode(root->right, key);
	else
		return searchNode(root->left, key);
}

int main()
{
	Node *root = new Node;
	root = NULL;
	root = insert(root, 50);
	insert(root, 30);
	insert(root, 20);
	insert(root, 40);
	insert(root, 70);
	insert(root, 60);
	insert(root, 80);

	printf("Inorder traversal of the given tree \n");
	inorder(root);

	if (searchNode(root, 80)) 
	printf("\nNumber 80 is found.");

	printf("\nDelete 20\n");
	root = deleteNode(root, 20);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);

	printf("\nDelete 30\n");
	root = deleteNode(root, 30);
	printf("Inorder traversal of the modified tree \n");
	inorder(root);


	delete root;
	cout << endl;
	system("pause");
	return 0;
}
