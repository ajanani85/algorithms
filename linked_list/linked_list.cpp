#include <iostream>
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
	while(current->next != NULL || current->data < data)
	{
		current = current->next;
	}

	LinkedList *item = new LinkedList(data);
	item->next = current->next;
	current->next = item;
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


	LinkedList *head = NULL;

	for(int i = 1; i <= 10; i++)
	{
		insert(&head, i * 100 / i);
	}

	print(head);

	return 0;
}
