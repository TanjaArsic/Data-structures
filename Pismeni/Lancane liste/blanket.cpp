#include <iostream>

// using namespace std;
class Node
{
public:
    int data;
    Node* next;

public:
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList
{
public:
    Node* head;
public:
    LinkedList() : head(nullptr) {}
    void Print()
    {
        Node* curr = head;
        std::cout << "The list is" << std::endl;
        while (curr != NULL)
        {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
    void MakeList()
    {
        Node* curr = head;
        int n, data, i = 0;
        std::cout << "Enter the number of elements" << std::endl;
        std::cin >> n;
        while (i < n)
        {
            std::cout << "Enter element: " << std::endl;
            std::cin >> data;
            Node* newNode = new Node(data);
            if (curr == NULL)
            {
                head = newNode;
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

    //bool moveSectionToHead(int start, int end); //jun2 2023.
    //bool deleteSublist(LinkedList* sublist); //jun 2023.
    //int SwapPairs(int data1, int data2); //kolokvijum 2023.
    //LinkedList* SplitOrMove(Node** head); //jun2 2022.
    //void MoveMinToHead(Node** head); //okt2 2022.
    //void SortList(); //okt2 2022.
    //int moveHigher(int value); // oktobar 2022
    //double calcPrefix(char* exp) //sept 2022.


    bool moveSectionToHead(int start, int end) //jun2 2023.
    {
        Node* next, * curr = head;
        Node* prev = nullptr;
        bool found = 0;
        while (curr->next != nullptr && !found)
        {
            if (curr->data == start)
            {
                next = curr->next;
                while (next != nullptr && next->data != end)
                {
                    next = next->next;
                }
                if (next == nullptr) return 0;

                else if (next->data == end)
                {
                    if (curr == head)
                        return 1;
                    found = 1;
                    prev->next = next->next;
                    next->next = head;
                    head = curr;
                    return 1;
                }
            }
            prev = curr;
            curr = curr->next;

        }
        if (found == 0)
        {
            std::cout << "There is no start" << std::endl;
            return 0;

        }

    }
    bool moveSectionToHead2(int start, int end)
    {
        Node* prev = nullptr;
        Node* first = head;
        if (first == nullptr || first->next == nullptr) return 0; //ima nijedan ili samo 1 cvor

        while (first != nullptr && first->data != start)
        {
            prev = first;
            first = first->next;
        }

        if (first == nullptr)
        {
            std::cout << "nema prvog cvora"; return 0;
        }

        Node* second = first;
        while (second != nullptr && second->data != end)
        {
            second = second->next;
        }
        if (second == nullptr)
        {
            std::cout << "nema drugog";
            return 0;
        }

        if (prev != nullptr) //ako je vec na pocetku liste ne treba da se nista pomera
        {
            prev->next = second->next;
            second->next = head;
            head = first; 
        }
    }



    bool deleteSublist(LinkedList* sublist) //jun 2023.
    {
        
        Node* sub = sublist->head; //neka je lista 1 2 3 1 2 3   a podlista 2 3, start = 2
        Node* curr = head;
        Node* prev = nullptr;
        bool deleted = 0;
        if (curr == nullptr || sub == nullptr) return deleted;
        while (curr != nullptr)
        {
            sub = sublist->head;
            if (curr->data == sub->data)
            {
                Node* startOfSublist = curr;
                while (sub != nullptr && startOfSublist->data == sub->data)
                {
                    startOfSublist = startOfSublist->next;
                    sub = sub->next;
                }
                if (sub == nullptr)
                {
                    if (prev == nullptr) //ako je prvi element odma
                        head = startOfSublist;
                    else 
                        prev->next = startOfSublist;

                    //while (startOfSublist != nullptr) //ovde gi brise*
                    //{
                    //    Node* tmp = startOfSublist;
                    //    startOfSublist = startOfSublist->next;
                    //    delete tmp;
                    //}
                    deleted = 1;
                    curr = startOfSublist;
                }
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        return deleted;

    }

    int SwapPairs(int data1, int data2) //kolokvijum 2023.
    {
        int count = 0;
        Node* prev = NULL;
        Node* start = head;
        if (start == NULL || start->next == NULL) //ako je prazna ili ima samo 1 element
            return 0;

        while (start != NULL && start->next != NULL)
        {
            if (start->data == data1)
            {
                Node* next = start->next;
                while (next != NULL && next->data != data2)
                {
                    next = next->next;
                }
                //if (next->data == data2) svakako je ili null ili jednak jer ne treba nuzno da se nadje kraj

                Node* end = next; //na kom cvoru ce da stane
                Node* curr = start;
                next = curr->next;
                while (next != NULL && end != curr)
                {
                    if (prev == NULL) //odma je na pocetku liste
                        head = next;
                    else
                        prev->next = next;

                    curr->next = next->next;
                    next->next = curr;

                    prev = curr;
                    curr = curr->next;
                    if (curr == NULL)
                        next = curr;
                    else
                        next = curr->next;
                    count++;
                }
            }
            prev = start;

            start = start->next;
        }
        if (start == NULL)
        {
            std::cout << "Ne postoji pocetak" << std::endl;
            return 0;
        }
        return count;
    }

    int SwapPairs2(int data1, int data2)
    {
        int swapped = 0;
        Node* first = head;
        Node* prev = nullptr;
        if (first == nullptr || first->next == nullptr)
            return 0;
        while (first->next != nullptr && first->data != data1)
        {
            prev = first;
            first = first->next;
        }

        if (first == nullptr) //nema prvi 
            return 0;
        Node* second = first->next;
        while (second != nullptr && first->data != data2) //bilo bi second->data da je neparan broj
        {

            first->next = second->next;
            second->next = first;
            if (prev == nullptr) head = second;
            else prev->next = second;
            prev = first;
            first = first->next;
            second = first->next;
            swapped++;
        }
        return swapped;
    }
    LinkedList* SplitOrMove() //jun2 2022.
    {
        LinkedList* newList = new LinkedList();
        Node* end = nullptr;
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr)
        {
            Node* flw = curr->next;
            Node* prevFlw = curr;
            while (flw != nullptr && flw->data != curr->data)
            {
                prevFlw = flw;
                flw = flw->next;
            }
            
            if (flw == nullptr) //nema duplikate
            {
                if (prev == nullptr) head = curr->next; // prvi element
                else prev->next = curr->next;
                Node* add = curr;
                curr = curr->next;
                add->next = newList->head;
                newList->head = add;
            }
            else
            {
                prevFlw->next = flw->next;
                flw->next = newList->head;
                newList->head = flw;
                prev = curr;
                curr = curr->next;
            }
            //if (next != nullptr && next->data == curr->data)              // ovo je za dodavanje na kraj liste
            //{
            //    follow->next = next->next;
            //    if (newList->head == nullptr)
            //    {
            //        next->next = newList->head;
            //        newList->head = next;
            //        end = newList->head;
            //    }
            //    else
            //    {
            //        next->next = end->next;
            //        end->next = next;
            //        end = end->next; //pokazuje na poslednji
            //    }
            //    prev = curr;
            //    curr = curr->next;
            //}
            //else
            //{
            //    Node* add = curr;
            //    if (prev == nullptr) //ako odma prvi el nema duplikata, da se prelanca
            //        head = curr->next;
            //    else
            //        prev->next = curr->next;
            //    curr = curr->next;
            //    if (newList->head == nullptr)
            //    {
            //        add->next = newList->head;
            //        newList->head = add;
            //        end = newList->head;
            //    }
            //    else
            //    {
            //        add->next = end->next;
            //        end->next = add;
            //        end = end->next; //pokazuje na poslednji
            //    }
            //}

        }
        return newList;
    }

    void MoveMinToHead(Node** start) //okt2 2022.
    {
        Node* min = *start;
        if (min == nullptr || min->next == nullptr)
            return;

        Node* prev = nullptr;
        Node* curr = *start;

        while (curr->next != nullptr)
        {
            if (curr->next->data < min->data)
            {
                prev = curr;
                min = curr->next;
            }
            curr = curr->next;
        }

        if (min != *start)
        {
            prev->next = min->next;
            min->next = *start;
            *start = min;
        }
    }


    void SortList(/*Node** head*/)
    {
    //    MoveMinToHead(&head);
    //    Node* start = head->next;
    //    Node* curr = head;
    //    while (start != nullptr && start->next != nullptr)
    //    {
    //        MoveMinToHead(&head);
    //        head = head->next;
    //    }

        Node** curr = &head;
        while (*curr != nullptr)
        {
            MoveMinToHead(curr);
            curr = &(*curr)->next;
        }
        //if (*head == nullptr || (*head)->next == nullptr)
        //    return;
        //MoveMinToHead(head);
        //SortList(&(*head)->next);
        
    }

    int moveHigher(int value) // oktobar 2022
    {
        if (head == nullptr || head->next == nullptr) return 0; // ima nijedan ili jedan element
        int moved = 0;
        Node* threshold = head;
        Node* prevT = nullptr;
        Node* prev = nullptr;
        Node* curr = head; //1 7 6 2 5 3
        while (curr != nullptr)
        {
            if (curr->data > value)
            {
                if (prev != nullptr)
                {
                    prev->next = curr->next;
                    if (prevT == nullptr)
                        head = curr;
                    else
                        prevT->next = curr;
                    prevT = curr;
                    curr->next = threshold;
                    curr = prev->next;
                    //threshold = threshold->next;
                }
                else
                {
                    prev = curr;
                    curr = curr->next;
                    prevT = threshold;
                    threshold = threshold->next; //ako je prev nullptr onda ostaje tako
                }
                moved++;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        return moved;
    }
    void GroupElements()
    {
        if (head == nullptr || head->next == nullptr) return;
        Node* curr = head;
        while (curr != nullptr && curr->next != nullptr) // 1 2 1 3 1 4 curr=1, flw=1, flw->next = 2, prev = 2, prev->next = 3
        {
            Node* prev = curr;
            Node* flw = curr->next;
            while (flw != nullptr)
            {
                if (flw->data == curr->data)
                {
                    prev->next = flw->next;
                    flw->next = curr->next;//ovo
                    curr->next = flw;
                    curr = flw;
                }
                prev = flw;
                flw = flw->next;
            }
            curr = curr->next;
        }

    }


};

int A[5];
int top = -1;

void Push(char x)
{
    if (top == 10)
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
    for (int i = 0; i < top; i++)
    {
        std::cout << A[i] << " ";
    }
}
char Top()
{
    return A[top];
}
bool isEmpty()
{
    return (top == -1);
}

double calcPrefix(char* exp)
{
    int i = strlen(exp) - 1;
    double result = 0;
    while (i >= 0)
    {
        if (exp[i] == '+' || exp[i] == '-' || exp[i] == '/' || exp[i] == '*')
        {
            double op1 = Top();
            Pop();
            double op2 = (char)Top();
            Pop();
            if (exp[i] == '+')
                Push(op1 + op2);
            else if (exp[i] == '-')
                Push(op1 - op2);
            else if (exp[i] == '/')
                Push(op1 / op2);
            else if (exp[i] == '*')
                Push(op1 * op2);
        }
        else
        {
            Push(exp[i] - '0');
        }
        i--;

    }
    result = Top();
    Pop();
    return result;

}
bool HigherPrecedence(char op) //vraca precedence za operator trenutni
{
    if ((op == '*' || op == '/') && (A[top] == '-' || A[top] == '+')
        ||
        (op == '(') && (A[top] == '-' || A[top] == '+' || A[top] == '*' || A[top] == '/'))
        return true;
    return false;
}

char* InfixToPostFix(char* exp) //popravi ovooooooooooooo
{
    int n = strlen(exp);
    int i = 0; int j = 0;
    char* postfix = (char*)malloc(strlen(exp) + 1);
    while (i < n)
    {
        if (exp[i] == '+' || exp[i] == '-' || exp[i] == '/' || exp[i] == '*' || exp[i] == '(')
        {
            if (isEmpty() || HigherPrecedence(exp[i]))
                Push(exp[i]); //stek je {+}

            else
            {
                while (!isEmpty() && !HigherPrecedence(exp[i]) && Top() != '(')
                {
                    postfix[j++] = Top();
                    Pop();
                }
                Push(exp[i]);
            }
        }
        else if (exp[i] == '(')
        {
            Push(exp[i]);
        }
        else if (exp[i] == ')')
        {
            postfix[j++] = Top();
            Pop();
        }
        else
            postfix[j++] = exp[i];
        i++;
    }
    while (!isEmpty())
    {
        if (Top() != '(')
        {
            postfix[j++] = Top();
        }
        Pop();
    }
    postfix[j] = '\0';
    return postfix;
}




int main(int argc, char* argv[])
{
    LinkedList* list = new LinkedList();
    list->MakeList();
    list->Print();

    //std::cout << list->moveSectionToHead2(2, 4) << std::endl;
    //list->Print();

    //LinkedList* sublist = new LinkedList();
    //sublist->MakeList();
    //sublist->Print();
    //std::cout << list->deleteSublist(sublist) << std::endl;
    //list->Print();

    //std::cout << "Broj zamenjenih parova je " << list->SwapPairs2(4, 8) << std::endl;
    //list->Print();

    //LinkedList* newList = list->SplitOrMove();
    //std::cout << "Lista 1" << std::endl;
    //list->Print();
    //std::cout << "Lista 2" << std::endl;
    //newList->Print();

    //std::cout << "Broj pomerenih elemenata je je " << list->moveHigher(5) << std::endl;
    //list->Print();

    list->GroupElements();
    list->Print();

   /* list->MoveMinToHead(&(list->head));
    list->Print();*/
    list->SortList(/*&(list->head)*/);
    list->Print();



    //Pop(); Pop(); Pop(); Pop(); Pop();

    //PrintStack();
    //char sent[] = "-*+342/84";
    //std::cout << calcPrefix(sent) << std::endl;
    //char infix[] = "(4+6)*(2-3)/5";
    //std::cout << InfixToPostFix(infix) << std::endl;

    return 0;
}


