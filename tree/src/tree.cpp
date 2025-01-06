#include <iostream>
#include <vector>
using namespace std;

enum ORDER_TYPE
{
	IN_ORDER=0,
	PRE_ORDER,
	POST_ORDER
};

struct Node
{
	int data;
	Node* left = NULL;
	Node* right = NULL;
	Node(int value)
	{
		data = value;
	}
};

void insert(Node **root, int value)
{
	//this is the root condition
	if(*root == NULL)
	{
		*root = new Node(value);
		return;
	}


	//insert in an ordered tree where the left is smaller than the right branch
	if(value < (*root)->data)
	{
		insert(&(*root)->left, value);
	}	
	else
	{
		insert(&(*root)->right, value);
	}
}

/*
	The print is done in three different ways:
	1. IN_ORDER: in which the order is left, root, and right
	2. PRE_ORDER: in which the order is root, left and right (top to bottom)
	3. POST_ORDER: in which the order is left, right, and root (bottom to top)
*/

void print(Node **root, const ORDER_TYPE &order_type)
{
	if(*root == NULL)
	{
		return;
	}
	switch(order_type)
	{
		case ORDER_TYPE::IN_ORDER:
		{
			print(&(*root)->left, order_type);
			cout << " " << (*root)->data;
			print(&(*root)->right, order_type);
			break;
		}
		case ORDER_TYPE::PRE_ORDER:
		{
			cout << " " << (*root)->data;
			print(&(*root)->left, order_type);
			print(&(*root)->right, order_type);
			break;
		}
		case ORDER_TYPE::POST_ORDER:
		{
			print(&(*root)->left, order_type);
			print(&(*root)->right, order_type);
			cout << " " << (*root)->data;
			break;
		}
		default:
			return;
	}
}

int main(int argc, char **argv) {

	vector<int> A = {4,2,6,1,3,5,7};
	
	Node* head = nullptr;

	for(int i : A)
	{
		insert(&head, i);
	}

	cout << "done with insert" << endl;

	cout << "in_order: ";
	print(&head, ORDER_TYPE::IN_ORDER);
	cout << endl;
	cout << "pre_order: ";
	print(&head, ORDER_TYPE::PRE_ORDER);
	cout << endl;
	cout << "post_order: ";
	print(&head,ORDER_TYPE::POST_ORDER);
	cout << endl;
	return 0;
}
