#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

int Length(Node** head);
void Print(Node** head);
void Prepend(Node** head, int data);
void Append(Node** head, int data);
void Insert(Node** head, int data, int pos);
void Delete(Node** head, int pos);
void DeleteData(Node** head, int data);
void Reverse(Node** head);
void MakeList(Node** head);
void Delete1stOccurrence(Node** head, int data);
bool isPalindrome(Node** head);
void Merge(Node** head, Node** head2);
void RemoveDuplicates(Node** head);
Node* Middle(Node** head);
void SwapNodes(Node** head);


int main(int argc, char* argv[])
{
	Node* head = NULL;
	//Node* head2 = NULL;

	MakeList(&head);
	cout << "The length of the list is: ";
	int len = Length(&head);
	cout << len << endl;
	/*Prepend(&head, 11);
	Append(&head,7);
	Insert(&head, 10, 3);
	Print(&head);
	Delete(&head, 3);
	Print(&head);
	Reverse(&head);
	Print(&head);
	DeleteData(&head, 3);
	Print(&head);
	Delete1stOccurrence(&head, 7);
	RemoveDuplicates(&head);*/
	Print(&head);
	/*cout << endl;
	cout << isPalindrome(&head) << endl;*/
	Node* mid = Middle(&head);
	cout << mid->data << " je sredina." << endl;

	//MakeList(&head2);
	//Merge(&head, &head2); 
	Print(&head);

	return 0;
}

void Print(Node** head)
{
	cout << "The list is: ";

	Node* curr = *head;
	if (*head == NULL)
	{
		cout << "Lista je prazna" << endl;
		return;
	}
	while (curr != NULL)
	{
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << endl;
}

int Length(Node** head)
{
	int n = 0;
	/*Node* curr = *head;
	while (curr != NULL)
	{
		n++;
		curr = curr->next;
	}*/
	for (Node* curr = *head; curr != NULL; curr = curr->next) n++;

	return n;
}
void Prepend(Node** head, int data)
{
	Node* tmp = new Node();
	tmp->data = data;
	tmp->next = *head;
	*head = tmp;
}

void Append(Node** head, int data)
{
	Node* tmp = new Node();
	tmp->data = data;

	//if the list is empty
	if (*head == NULL)
	{
		tmp->next = *head; //null
		*head = tmp;
	}
	else{
		//if the list aint empty
		Node* curr = *head;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		tmp->next = curr->next;
		curr->next = tmp;
	}
}
void Insert(Node** head, int data, int pos)
{
	Node* tmp = new Node();
	tmp->data = data;
	if (pos == 1)
	{
		tmp->next = *head;
		*head = tmp;
	}
	else
	{
		Node* curr = *head;
		int i = 1;
		while (i < pos - 1)
		{
			curr = curr->next;
			i++;
		}
		tmp->next = curr->next;
		curr->next = tmp;

	}
}
void Delete(Node** head, int pos)
{
	Node* curr = *head;
	if (curr == NULL)
	{
		cout << "Lista je prazna!" << endl;
	}
	else
	{
		if (pos == 1)
			*head = curr->next;
		else
		{
			int i = 1;
			while (i < pos - 1)
			{
				curr = curr->next;
				i++;
			}
			Node* tmp = curr->next;
			curr->next = tmp->next;
			delete tmp;
		}
	}
}

void DeleteData(Node** head, int data)
{
	Node* curr = *head;
	while (curr != NULL && curr->data == data)
	{
		Node* del = curr;
		curr = curr->next;
		*head = curr;
		delete del;
		cout << "Obrisano s pozicije 1 " << endl;
	}
	if (curr == NULL)
	{
		cout << "Lista je prazna" << endl;
	}
	int pos = 1;
	while (curr != NULL && curr->next != NULL)
	{
		if (curr->next->data == data)
		{
			Node* tmp = curr->next;
			curr->next = tmp->next;
			delete tmp;
			pos++;
			cout << "Obrisano s pozicije " << pos << endl;
		}
		else 
		{
			pos++;
			curr = curr->next;
		}
			
	}
	if (curr == NULL)
	{
		cout << "Lista je prazna" << endl;
	}

}

void Reverse(Node** head)
{
	cout << "Izopacena lista: ";
	Node* prev, *next, *curr;
	prev = NULL;
	curr = *head;

	while (curr != NULL)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;

}
void MakeList(Node** head)
{
	Node* curr = *head;
	int n, data, i = 0;
	cout << "Enter the number of elements" << endl;
	cin >> n;
	while (i < n)
	{
		Node* newNode = new Node();
		cout << "Enter element: " << endl;
		cin >> data;
		newNode->data = data;
		newNode->next = NULL;
		if (curr == NULL)
		{
			*head = newNode;
			curr = newNode;
		}
		else
		{
			curr->next = newNode;
			curr = newNode;
		}
		i++;
	}
	
}

void Delete1stOccurrence(Node** head, int data)
{
	if (*head == NULL)
	{
		cout << "The list is empty!" << endl;
		return;
	}
	Node* curr = *head;
	Node* prev = NULL;
	while (curr != NULL && curr->data != data)
	{
		prev = curr;
		curr = curr->next;
	}
	
	if (curr == NULL)
		cout << "No occurences of " << data << endl;

	if (curr->data == data)
	{
		if (prev == NULL)
			*head = curr->next;
		else
			prev->next = curr->next;
	}
	delete curr;

}

bool isPalindrome(Node** head)
{
	Node* start = *head;
	if (start == NULL || start->next == NULL) //ako je prazna lista il ima samo 1 element onda je palindrom
		return 1;
	
	// fast&slow metoda za nalazenje sredine
	Node* slow = *head;
	Node* fast = *head;
	while (fast->next != NULL && fast->next->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	//middle je slow->next, a prev je slow
	Node* end = slow->next;
	slow->next = NULL;
	Node* prev = NULL;
	

	while (end != NULL)
	{
		Node* next = end->next; //dosta je bitno da se inicijalizuje unutar petlje jer nece da prolazi lepo
		end->next = prev;
		prev = end;
		end = next;
	}
	end = prev;

	while (start != NULL && end != NULL)
	{
		if (start->data == end->data)
		{
			start = start->next;
			end = end->next;
		}
		else
		{
			cout << "It aint a palindrome" << endl;
			return 0;
		}
	}
	cout << "It is a palindrome" << endl;
	return 1;
	
}

void RemoveDuplicates(Node** head)
{
	Node* curr = *head;

	while (curr != NULL)
	{
		Node* prev = curr;
		Node* next = curr->next;
		while (next != NULL)
		{
			if (curr->data == next->data)
			{
				Node* del = next;
				prev->next = next->next;
				next = del->next;
				delete del;
			}
			else
			{
				prev = prev->next;
				next = next->next;
			}
		}
		curr = curr->next;
	}
}

Node* Middle(Node** head)
{
	Node* slow, * fast;
	slow = *head;
	fast = *head;
	if (slow == NULL)
	{
		cout << "Lista je prazna" << endl;
		return 0;
	}	
	if (slow->next == NULL)
		return slow;

	while (fast->next != NULL && fast->next->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

void Merge(Node** head, Node** head2)
{
	Node* first;
	first = *head;
	while (first->next != NULL)
	{
		first = first->next;
	}
	first->next = *head2;
}

void SwapNodes(Node** head)
{

}

