#include <iostream>
using namespace std;

struct LinkedList
{
	int data;
	LinkedList *next;
};

LinkedList* push_back(LinkedList *head, int data)
{
	if(head == NULL)
	{
		head = new LinkedList();
		head->data = data;
		return head;
	}

	LinkedList *current = head;
	while(current->next != NULL)
	{
		current = current->next;
	}

	LinkedList *item = new LinkedList();
	item->data = data;
	current->next = item;
	return head;
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


	LinkedList *head;

	push_back(head, 10);

	print(head);

	return 0;
}
