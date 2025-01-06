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
		if(item == nullptr)
		{
			return;
		}
		data = item->data;
		next = item->next;
		size = item->size;
	}
	int data;
	LinkedList *next;
	int size = 0;
};

/**
 * reverse the order of the passed LinkedList
 */
void reverse(LinkedList **head)
{

	if(*head == NULL)
	{
		return;
	}

	LinkedList *current = *head;
	LinkedList *prev = nullptr;
	LinkedList *iterator;

	while(current)
	{
		iterator = current->next;

		current->next = prev;

		prev = current;

		current = iterator;
	}

	*head = prev;
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


/*
	Delete a node without head
*/
void deleteNode(LinkedList **node)
{
	if(*node == NULL)
	{
		return;
	}

	LinkedList *temp = (*node)->next;

	if(temp == NULL)
	{
		node = NULL;
	}
	else
	{
		(*node)->data = temp->data;
		(*node)->next = temp->next;
	}
}

void deleteWithVal(LinkedList **head, int value)
{
	if (*head == NULL)
	{
		return;
	}
	LinkedList *current = *head;
	while(current)
	{
		//there might be more than one copy with the same value
		if(current->data == value)
		{	
			deleteNode(&current);
			(*head)->size--;
		}
		else
		{
			current = current->next;
		}
	}
}

/**
 * insert an item at the given index
 */
void insert(LinkedList **head, int data, int index)
{
	if(*head == NULL)
	{
		return;
	}

	LinkedList *current = *head;
	LinkedList *prev = current;
	int cnt = 0;
	while(cnt < index && current != NULL)
	{
		prev= current;
		current=current->next;
		cnt++;
	}
	if(current == NULL)
	{
		return;
	}
	LinkedList* item = new LinkedList(data);
	//index is zero
	if(current == prev)
	{
		LinkedList* tmp = new LinkedList(*head);
		item->next = tmp;
		*head = item;
		return;
	}

	prev->next = item;
	item->next = current;
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
	//when we get here, one of the following conditions are true;
	//1. current and prev are both the same: the edge case that happens at the beginning of the array
	LinkedList *temp = new LinkedList(data);
	if(current == prev)
	{
		temp->next = current;
		*head = temp;
	}
	//2. when current and previous are not the same
	else
	{
		temp->next = current;
		prev->next = temp;
	}	
	(*head)->size++;

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
	LinkedList *new_head = new LinkedList(data);
	new_head->size += (*head)->size;

	new_head->next = *head;
	*head = new_head;
}

void push_back(LinkedList **head, int data)
{
	if(*head == NULL)
	{
		*head = new LinkedList(data);
		return;
	}
	LinkedList* current = *head;
	while(current->next != NULL)
	{
		current = current->next;
	}
	//when here, the next item is null
	current->next = new LinkedList(data);
	(*head)->size++;
}

void print(LinkedList *head)
{
	if(!head)
	{
		return;
	}

	LinkedList *current = head;
	cout << "size: " << current->size << endl;
	while(current)
	{
		cout << current->data;
		current = current->next;
		if(current == NULL)
		{
			cout << endl;
		}
		else
		{
			cout << "->";
		}
	}
}

void deleteKthElementFromEnd(LinkedList **head, int k)
{
	if(*head == NULL)
	{
		return;
	}

	LinkedList *slow = *head;
	LinkedList *fast = *head;

	//move the fast pointer K element forward
	for(int i = 0; i <= k; i++)
	{
		fast = fast->next;
		if(fast == NULL)
		{
			return;
		}
	}

	//move both slow and fast pointer until fast reaches the end
	while(fast != NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}

	deleteNode(&slow->next);
}

int main(int argc, char **argv) {

	vector<int> A = {9, 3, 5, 7, 9, -10, 2, 9, 9, 8};
	LinkedList *head = NULL;

	for(int i = 0; i < A.size(); i++)
	{
		//push to the back of the list (maintaining the order)
		//push_back(&head, A[i]);

		//push to the front of the list (order is reveresed)
		//push_front(&head, A[i]);

		//sort while inserting
		insert(&head, A[i]);
	}

	insert(&head, 200);

	reverse(&head);

	print(head);

	deleteWithVal(&head, 9);

	print(head);

	deleteKthElementFromEnd(&head, 3);

	print(head);
	
	return 0;
}
