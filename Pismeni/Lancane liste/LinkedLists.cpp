#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
using namespace std;

struct Node
{
	int data;
	Node* next;
};

/* ---------- Linked List ---------- */
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

/* ---------- Stack ---------- */

int A[5];
int top = -1;
Node* topp = nullptr;
void Push(int x);
void Pop();
void PrintStack();
int Top();
bool isEmpty();
void PushLL(Node* x);
void PopLL();
Node* TopLL();
bool isEmptyLL();
void ReverseLL(Node** head);
bool BalancedParentheses(char string[]);




int main(int argc, char* argv[])
{
	Node* head = NULL;
	////Node* head2 = NULL;

	//MakeList(&head);
	//cout << "The length of the list is: ";
	//int len = Length(&head);
	//cout << len << endl;
	///*Prepend(&head, 11);
	//Append(&head,7);
	//Insert(&head, 10, 3);
	//Print(&head);
	//Delete(&head, 3);
	//Print(&head);
	//Reverse(&head);
	//Print(&head);
	//DeleteData(&head, 3);
	//Print(&head);
	//Delete1stOccurrence(&head, 7);
	//RemoveDuplicates(&head);*/
	//Print(&head);
	///*cout << endl;
	//cout << isPalindrome(&head) << endl;*/
	//Node* mid = Middle(&head);
	//cout << mid->data << " je sredina." << endl;

	////MakeList(&head2);
	////Merge(&head, &head2); 
	//Print(&head);

	//Print(&topp);
	//if (isEmptyLL)
	//	cout << "The stack is empty, the top is null" << endl;
	//else 
	//	cout << "The top of the stack is: " << TopLL() << endl;

	
	char exp[] = "({({}[{{}}]())})";
	//return 0;
	if (BalancedParentheses(exp)) cout << "They're balanced!" << endl;
	else cout << "They're not balanced!" << endl;
	//ReverseLL(&head);
	//Print(&head);
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


void Push(int x)
{
	if (top == 5)
	{
		std::cout << "Stack overflow" << std::endl;
		return;
	}
	A[++top] = x;
}
void Pop()
{
	if (top == -1)
	{
		std::cout << "Stack underflow" << std::endl;
		return;
	}
	top--;
}
void PrintStack()
{
	for (int i = 0; i <= top; i++)
	{
		std::cout << A[i] << " ";
	}
}

int Top()
{
	return A[top];
}

bool isEmpty()
{
	return (top == -1);
}

void PushLL(Node* x) 
{
	Node* newNode = new Node();
	newNode->data = x->data;
	newNode->next = topp;
	topp = newNode;
}

void PopLL()
{
	if (topp == nullptr)
	{
		throw std::runtime_error("Stack Underflow!");
	}
	//Node* tmp = topp;
	topp = topp->next;
	//delete tmp;
}

Node* TopLL()
{
	if (isEmptyLL())
		return 0;
	return topp;
}

bool isEmptyLL()
{
	return (topp == nullptr);
}

void ReverseLL(Node** head)
{
	
	Node* curr = *head;
	while (curr != nullptr)
	{
		PushLL(curr);
		curr = curr->next;
	}

	curr = topp;
	PopLL();
	*head = curr;
	
	while (!isEmptyLL())
	{
		curr->next = topp;
		PopLL();
		curr = curr->next;
	}
	curr->next = nullptr;

}
//void ReverseLL(Node** head) //druga verzija
//{
//	if (*head == nullptr || (*head)->next == nullptr)
//		return;
//
//	std::stack<Node*> nodeStack;
//	Node* curr = *head;
//
//	while (curr != nullptr)
//	{
//		nodeStack.push(curr);
//		curr = curr->next;
//	}
//
//	*head = nodeStack.top();
//	nodeStack.pop();
//	curr = *head;
//
//	while (!nodeStack.empty())
//	{
//		curr->next = nodeStack.top();
//		nodeStack.pop();
//		curr = curr->next;
//	}
//
//	curr->next = nullptr;
//}

bool BalancedParentheses(char string[])
{
	int n = strlen(string);
	for (int i = 0; i < n; i++)
	{
		if (string[i] == '(' || string[i] == '[' || string[i] == '{')
		{
			Node* par = new Node();
			par->data = string[i];
			par->next = nullptr;
			PushLL(par);
		}
		else if (topp == nullptr)
			return false; // ako je prazan stack ili nema uopste zagrada
		else if (string[i] == ')' && topp->data == '('
			|| string[i] == '}' && topp->data == '{'
			|| string[i] == ']' && topp->data == '[')
			PopLL();
		else if (string[i] == ')' || string[i] == '}' || string[i] == ']')
			// ovaj deo push-uje neuparene zatvorene zagrade jer ako se nadje random zatvorena zagrada
			// bez koresp. otvorene, onda ce da kaze da je balansirano; npr. izraz: (})
		{
			Node* nepar = new Node();
			nepar->data = string[i];
			nepar->next = nullptr;
			PushLL(nepar);
		}
		
	}
	return isEmptyLL();
}
