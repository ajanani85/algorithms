#include <iostream>
#include <vector>

using namespace std;

struct Node
{
	Node(int d)
	{
		data = d;
		next = NULL;
		prev = NULL;
	}

	Node(Node* n)
	{
		if(n == NULL)
		{
			Node(0);
			return;
		}
		data = n->data;
		next = n->next;
		prev = n->prev;
	}
	int data;
	Node *next;
	Node *prev;
};

void print(Node *head)
{
	Node *current = head;

	while(current != NULL)
	{
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}

void push_back(Node **head, int value)
{
	if(*head == NULL)
	{
		*head = new Node(value);
		return;
	}

	Node *current = *head;
	while(current->next != NULL)
	{
		current = current->next;
	}

	Node *item = new Node(value);
	current->next = item;
	current->next->prev = current;
}

void insert(Node **head, int value)
{
	if(*head == NULL)
	{
		*head = new Node(value);
		return;
	}

	Node *current = *head;
	while(current->next != NULL && current->data > value)
	{
		current = current->next;
	}
	Node *item = new Node(value);

	if(current->next != NULL)
	{
		current->prev = item;
		item->next = current;
	}


	if(current->prev == NULL)
	{
		Node *item = new Node(value);
		item->next = new Node(*head);
		*head = item;
		return;

	}

	Node *prev = current->prev;
	prev->next = new Node(value);
	prev->next->next = current;
}


int main(int argc, char **argv) {

	std::vector<int> arr = {1,10,9,2,5,13,-7,6,8};
	Node *head = NULL;

	for(int i = 0; i < arr.size(); i++)
	{
		insert(&head, arr[i]);
	}

	print(head);

	delete head;
	return 0;
}
