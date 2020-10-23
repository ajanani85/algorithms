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

void deleteAt(LinkedList **head, int index)
{
	if(*head == NULL)
	{
		return;
	}
	LinkedList* current = *head;
	LinkedList *prev = *head;
	int cnt = 0;
	while(current != NULL && cnt < index)
	{
		prev = current;
		current = current->next;
		cnt++;
	}

	if(current == NULL)
	{
		return;
	}

	if(current == prev)
	{
		*head = (*head)->next;
		return;
	}

	prev->next = current->next;
}

void deleteWithVal(LinkedList **head, int value)
{
	if(*head == NULL)
	{
		return;
	}

	LinkedList* current = *head;
	LinkedList *prev = *head;
	while(current != NULL)
	{
		if(current->data == value)
		{
			//when at the beginning
			if(prev == current)
			{
				*head = current->next;

			}
			else
			{
				//general case
				prev->next = current->next;
				//increment the cursor
				current = prev->next;
				continue;
			}

		}
		prev = current;
		current = current->next;



	}
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
	LinkedList *tmp = new LinkedList(*head);
	item->next = tmp;
	*head = item;
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

	vector<int> A = {9, 3, 5, 7, 9, -10, 2, 9, 9, 8};
	LinkedList *head = NULL;

	for(int i = 0; i < A.size(); i++)
	{
		insert(&head, A[i]);
	}


	deleteAt(&head, 1);

	print(head);
	return 0;
}
