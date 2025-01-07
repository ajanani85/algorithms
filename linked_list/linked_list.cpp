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
void insert(LinkedList **head, int data, bool exclusive = false)
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

	if(exclusive)
	{
		if(current && current->data == data)
		{
			return;
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

void makeItCycleAtKthElement(LinkedList **head, int k)
{
	if(*head == NULL)
	{
		return;
	}

	LinkedList *slow = *head;
	
	//iterate to the Kth element
	for(int i = 0; i <= k; i++)
	{
		slow = slow->next;
		if(slow == NULL)
		{
			return;
		}
	}

	//pass the pointer to the fast and iterate that to the end
	LinkedList *fast = slow;
	while(fast->next != NULL)
	{
		fast = fast->next;
	}

	fast->next = slow;
}

/*
	Floyd's Cycle Detection Algorithm, also known as the Tortoise and Hare Algorithm.
*/
bool isThereCycle(LinkedList **head)
{

	if(*head == NULL || (*head)->next == NULL)
	{
		return false;
	}

	LinkedList *slow = *head;
	LinkedList *fast = (*head)->next;

	while(fast && fast->next)
	{

		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast)
		{
			return true;
		}

	}

	return false; 
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

void merge(LinkedList **l1, LinkedList **l2)
{
	if(*l1 == NULL)
	{
		*l1 = *l2;
		return;
	}
	if(*l2 == NULL)
	{
		return;
	}

	LinkedList *t1 = *l1;
	LinkedList *t2 = *l2;
	LinkedList *prev = NULL;
	while(t1 != NULL && t2 != NULL)
	{
		if(t2->data >= t1->data)
		{
			prev = t1;
			t1 = t1->next;
		}
		else
		{
			if(prev)
			{
				prev->next = t2;
			}
			prev= t2;
			t2 = t2->next;
			prev->next = t1;
			if(t1 == *l1)
			{
				*l1 = prev;
			}
		}
	}
	if (t2 != nullptr) 
	{
		prev->next = t2;
	}
}

LinkedList *toList(const vector<int> &arr)
{
	if (arr.size() == 0)
	{
		return nullptr;
	}

	LinkedList *head = new LinkedList(arr[0]);
	LinkedList *it = head;
	for(int i = 1; i < arr.size(); i++)
	{
		it->next = new LinkedList(arr[i]);
		it = it->next;
	}
	return head;
}	


/*
	You are given two non-empty linked lists representing two non-negative integers. 
	The digits are stored in reverse order, and each of their nodes contains a single digit. 
	Add the two numbers and return the sum as a linked list.
	You may assume the two numbers do not contain any leading zero, except the number 0 itself.
*/
LinkedList *sum(LinkedList **head1, LinkedList **head2)
{
	LinkedList *dummy = new LinkedList(0);
	LinkedList *it = dummy;

	LinkedList *l1 = *head1;
	LinkedList *l2 = *head2;
	int carry = 0;

	while(l1 || l2 || carry != 0)
	{
		int digit1 = (l1) ? l1->data : 0;
		int digit2 = (l2) ? l2->data : 0;

		int sum = digit1 + digit2 + carry;
		carry = sum / 10;
		sum = sum % 10;

		LinkedList *item = new LinkedList(sum);
		it->next = item;
		
		it = it->next;
		l1 = (l1) ? l1->next : nullptr;
		l2 = (l2) ? l2->next : nullptr;
	}

	LinkedList *result = dummy->next;
	delete dummy;
	return result;
}

int main(int argc, char **argv) {

	vector<int> A = {9, 3, 5, 7, 9, -10, 2, 9, 9, 8};
	vector<int> B = {-200,1,2,3,4,5,6,7,8,9,10};
	LinkedList *head = NULL;
	LinkedList *head_b = NULL;
	for(int i = 0; i < B.size(); i++)
	{
		insert(&head_b, B[i], true);
	}

	for(int i = 0; i < A.size(); i++)
	{
		//push to the back of the list (maintaining the order)
		//push_back(&head, A[i]);

		//push to the front of the list (order is reveresed)
		//push_front(&head, A[i]);

		//sort while inserting
		//insert(&head, A[i]);

		//insert with one copy just like set data structure
		insert(&head, A[i], true);
	}

	insert(&head, 200, true);

	//reverse(&head);

	//print(head);

	deleteWithVal(&head, 9);

	print(head);

	deleteKthElementFromEnd(&head, 3);

	print(head);

	cout << (isThereCycle(&head) ? "true" : "false") << endl;

	//makeItCycleAtKthElement(&head, 2);

	//cout << (isThereCycle(&head) ? "true" : "false") << endl;

	cout << "MERGING TEST INPUT: " << endl;

	print(head);
	print(head_b);


	cout << "MERGING TEST OUTPUT: " << endl;
	merge(&head, &head_b);
	print(head);


	vector<int> C = {2,4,3};
	vector<int> D = {5,6,4};

	LinkedList *head_c = toList(C);
	LinkedList *head_d = toList(D);

	print(head_c);
	print(head_d);

	LinkedList *sum_cd = sum(&head_c, &head_d);
	print(sum_cd);
		
	return 0;
}
