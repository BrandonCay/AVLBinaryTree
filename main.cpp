//AVL6
#include <string>
#include <iostream>
#include <queue>
#include "node.h"
#include "nodeShadow.h"
#include <time.h>
#include <stdlib.h>
using namespace std;
// A function to create a new BST node
node* newNode(int newItem);
// Postcondition: a new node is returned and members initialized to newItem, nullptr, and nullptr, respectively. 
bool insert(const int & x, node*& t);
//pre: checks t==nullptr.
//post: if true: adds a newNode at that location then proceeds to balance THEN return true. 
//Otherwise: it will travel the tree recursively until its t==nullptr. if the value==a node THEn returns false
int height(node* t);//standard height
//pre: checks if t==nullptr
//post: IF so: assigns 0 to the maxHeight. Otherwise: recursively travels down the BST until it does
//THEN returns the value of maxHeight after being incremented for each layer traveled
int balanceHeight(node*& t, int limit);//modified height
//pre: checks if t==nullptr
//postcondition: IF so: assigns maxHeight=0. Otherwise: recursively travels the BST while incrementing the max, and the left and right
//subtree's height. If the height of the ancestor's differ by more than 1. Checks children Rotates accordingly. 
//finds the height of the children using its ancestor THEN rotates 
void rotateWithLeftChild(node*& k);//rotate right
//postcondition: uses ancestor to rotate the left child right THEN replaces the ancestor with the child as the new ancestor
void rotateWithRightChild(node*& k);//rotate left
//postcondition: uses ancestor to rotate the right child left THEN replaces the ancestor with the child as the new ancestor
void doubleWithLeftChild(node*& k);
//post: rotate left THEN right
void doubleWithRightChild(node*& k);
//post: rotate left THEN right
void levelOrderOutput(node* t);
//post: outputs the tree in level order

int COUNT = 5;//spaces used for printing2D
void print2DUtil(node* root, int space);
//post: prints a 2D binary tree with the top being on the left and the bottom being on the right. code from GeekForGeeks
void print2D(node* root);
//post: wrapper function for print2DUtil
int main() {
	srand(time(0));
	cout << "Tree 1:" << endl;
	node* hptr=nullptr;
	insert(10, hptr);
	insert(6, hptr);
	insert(1, hptr);
	levelOrderOutput(hptr);
	cout << endl;
	node* t2Hptr = nullptr;
	cout << "Tree 2:" << endl;
	insert(10,t2Hptr);
	insert(5, t2Hptr);
	insert(8, t2Hptr);
	levelOrderOutput(t2Hptr);
	cout << endl;
	cout << "Tree 3:" << endl;
	node* t3Hptr = nullptr;
	insert(10, t3Hptr);
	insert(20, t3Hptr);
	insert(30, t3Hptr);
	levelOrderOutput(t3Hptr);
	cout << endl;
	cout << "Tree 4:" << endl;
	node* t4Hptr = nullptr;
	int cnt=0;
	while(cnt<10) {
		int x = rand() % 100;
		if (!insert(x, t4Hptr)) {
			continue;
		}
		++cnt;
		levelOrderOutput(t4Hptr);
	}
	print2D(t4Hptr);
	return 0;
}

void print2DUtil(node* root, int space)
{
	// Base case  
	if (root == NULL)
		return;

	// Increase distance between levels  
	space += COUNT;

	// Process right child first  
	print2DUtil(root->right, space);

	// Print current node after space  
	// count  
	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->item << "\n";

	// Process left child  
	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()  
void print2D(node * root)
{
	// Pass initial space count as 0  
	print2DUtil(root, 0);
}
void levelOrderOutput(node* t) {
	if (t == nullptr) {
		return;
	}
	queue<node*>q;
	node* temp;
	q.push(t);
	while (!q.empty()) {
		temp=q.front();
		q.pop();
		cout << temp->item <<" ";
		if (temp->left!=nullptr) {
			q.push(temp->left);
		}
		if (temp->right!=nullptr) {
			q.push(temp->right);
		}
	}
	cout << endl;
}

node* newNode(int newItem) {
	node* temp = new node();
	temp->item = newItem;
	temp->left = nullptr;
	temp->right = nullptr;
	return temp;
}

bool insert(const int& x, node*& t) {
	if (t == nullptr) {
		t = newNode(x);
	}
	else if (t->item > x) {
		insert(x, t->left);
	}
	else if (t->item < x) {
		insert(x, t->right);
	}
	else {
		cout <<endl<< "FAILURE: can't have similar values" << endl;
		return false;//AVL can't have similar values
	}
	balanceHeight(t,1);
	return true;
}

int balanceHeight(node*& t, int limit)
{
	int HLeft, HRight, Hval;

	if (t == nullptr) {
		// depth of an empty tree is 0
		Hval = 0;
	}
	else
	{
		HLeft = balanceHeight(t->left, limit);
		HRight = balanceHeight(t->right, limit);

		if (HLeft - HRight > limit) {
			if (height(t->left->left) >= height(t->left->right)) {
				rotateWithLeftChild(t);
			}
			else {
				doubleWithLeftChild(t);
			}
		}
		else if (HRight - HLeft > limit) {
			if (height(t->right->right) >= height(t->right->left)) {
				rotateWithRightChild(t);
			}
			else {
				doubleWithRightChild(t);
			}
		}
		Hval = 1 + (HLeft > HRight ? HLeft : HRight);
	}
	return Hval;
}

int height(node* t)
{
	int depthLeft, depthRight, depthval;

	if (t == nullptr)
		// depth of an empty tree is -1
		depthval = 0;
	else
	{
		// find the depth of the left subtree of t
		depthLeft = height(t->left);
		// find the depth of the right subtree of t
		depthRight = height(t->right);
		// depth of the tree with root t is 1 + maximum
		// of the depths of the two subtrees
		depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
	}
	return depthval;
}


void rotateWithLeftChild(node*& k) {//rotate right
	//k is an ancestor
	//cout << "rotateRight" << endl;
	node* lc = k->left;//left child
	k->left = lc->right;//ancestor CUTS OFF lc and replaces it with its right to make space for lc's right to rotate

	lc->right = k;
	k = lc;

}//rotate right
void rotateWithRightChild(node*& k) {
//	cout << "rotateLeft" << endl;
	node* rc = k->right;
	k->right = rc->left;
	rc->left = k;
	k = rc;

}	//rotate left
void doubleWithLeftChild(node*& k) {
	rotateWithRightChild(k->left);//rotate left
	rotateWithLeftChild(k);//rotate right
}
void doubleWithRightChild(node*& k) {
	rotateWithLeftChild(k->right);
	rotateWithRightChild(k);
}

