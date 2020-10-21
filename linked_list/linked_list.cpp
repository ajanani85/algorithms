#include <iostream>
#include <vector>
using namespace std;

struct LinkedList
{
	LinkedList(int d)
	{
		data = d;
		next = NULL;
		size = 1;
	}
	LinkedList(LinkedList *item)
	{
		data = item->data;
		next = item->next;
		size = item->size;
	}
	int data;
	LinkedList *next;
	size_t size;
};

/**
 * reverse the order of the passed LinkedList
 */
void reverse(LinkedList **head)
{
}

/**
 * insert an item at the given index
 */
void insert(LinkedList **head, int data, int index)
{
}

/**
 * insert an item in order
 */
void insert(LinkedList **head, int data)
{
	if(*head == NULL)
	{
		*head = new LinkedList(data);
		return;
	}

	LinkedList *current = *head;
	LinkedList *prev = current;
	while(current->data < data)
	{
		prev = current;
		current = current->next;
		if(current == NULL)
		{
			break;
		}
	}

	LinkedList *item = new LinkedList(data);
	//normal case
	if(prev != current)
	{
		prev->next = item;
		item->next = current;
		(*head)->size +=1;
		return;
	}

	//where the place is the head (when prev = current)
	LinkedList *tmp = new LinkedList(*current);
	item->next = tmp;
	size_t size = (*head)->size;
	*head = item;
	(*head)->size = ++size;
}

/**
 * push the passed item in the front
 */
void push_front(LinkedList **head, int data)
{
	if(*head == NULL)
	{
		*head = new LinkedList(data);
		return;
	}

	LinkedList *tmp = new LinkedList(*head);

	LinkedList *current = new LinkedList(data);
	current->next = tmp;
	current->size = (*head)->size + 1;

	*head = current;
	//(*head)->size++;
}

void push_back(LinkedList **head, int data)
{
	if(*head == NULL)
	{
		*head = new LinkedList(data);
		return;
	}

	//Move the cursor to the end of the array
	LinkedList *current = *head;
	while(current->next != NULL)
	{
		current = current->next;
	}

	//create a new item and add it the current cursor position
	LinkedList *item = new LinkedList(data);
	current->next = item;
	(*head)->size++;
}

void print(LinkedList *head)
{
	if (head == NULL)
	{
		return;
	}

	LinkedList *current = head;
	int id = 0;
	while (current != NULL)
	{
		cout << "item " << id << ": " << current->data << endl;
		current = current->next;
		id++;
	}
}

int main(int argc, char **argv) {

	vector<int> A = {9, 3, 5, 7, 1, -10, 2, 4, 6, 8};
	LinkedList *head = NULL;

	for(int i = 0; i < A.size(); i++)
	{
		insert(&head, A[i]);
	}

	print(head);

	return 0;
}
