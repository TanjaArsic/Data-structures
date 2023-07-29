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


    bool moveSectionToHead(int start, int end) //jun2 2023.
    {
        Node* next, * curr = head;
        Node* prev = NULL;
        bool found = 0;
        while (curr->next != NULL && !found)
        {
            if (curr->data == start)
            {
                next = curr->next;
                while (next != NULL && next->data != end)
                {
                    next = next->next;
                }
                if (next->data == end)
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

    bool deleteSublist(LinkedList* sublist) //jun 2023.
    {
        
        Node* sub = sublist->head;
        Node* curr = head;
        Node* prev = NULL;
        while (curr != NULL)
        {
            sub = sublist->head;
            if (curr->data == sub->data)
            {
                while (sub != NULL && curr->data == sub->data)
                {
                    curr = curr->next;
                    sub = sub->next;
                }
                if (sub == NULL)
                {
                    if (prev == NULL) //ako je prvi element odma
                        head = curr;
                    else [[p]]
                        prev->next = curr;

                    sub = sublist->head;
                    while (sub != NULL) //ovde gi brise
                    {
                        Node* tmp = sub;
                        sub = sub->next;
                        delete tmp;
                    }
                    return 1;
                }

            }
            prev = curr;
            curr = curr->next;
        }
        if (curr == NULL)
        {
            std::cout << "Not found" << std::endl;
            return 0;
        }

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

    LinkedList* SplitOrMove() //jun2 2022.
    {
        LinkedList* newList = new LinkedList();
        Node* end = nullptr;
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr)
        {
            Node* next = curr->next;
            Node* follow = curr;
            while (next != nullptr && next->data != curr->data)
            {
                follow = next;
                next = next->next;
            }
            if (next != nullptr && next->data == curr->data) //poslednji element resava
            {

                follow->next = next->next;
                if (newList->head == nullptr)
                {
                    next->next = newList->head;
                    newList->head = next;
                    end = newList->head;

                }
                else
                {
                    next->next = end->next;
                    end->next = next;
                    end = end->next; //pokazuje na poslednji
                }
                prev = curr;
                curr = curr->next;

            }
            else
            {
                Node* add = curr;
                if (prev == nullptr) //ako odma prvi el nema duplikata, da se prelanca
                    head = curr->next;
                else
                    prev->next = curr->next;
                curr = curr->next;
                if (newList->head == nullptr)
                {
                    add->next = newList->head;
                    newList->head = add;
                    end = newList->head;
                }
                else
                {
                    add->next = end->next;
                    end->next = add;
                    end = end->next; //pokazuje na poslednji
                }
            }

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

    Node* findTail(Node* node)
    {
        if (node == NULL || node->next == NULL)
            return node;

        return findTail(node->next);
    }

    void SortList(Node* start)
    {
        if (start == NULL || start->next == NULL)
            return;

        MoveMinToHead(&start);
        Node* tail = findTail(start);
        SortList(start->next);
        tail->next = start;
        start->next = NULL;
        head = start; // Update the head to the first element of the sorted list
    }
    /*void SortList()
    {
        if (head == NULL || head->next == NULL)
            return;

        MoveMinToHead(&head);
        Node* new_head = head->next;
        head = new_head;
        SortList();
    }*/

};


int main(int argc, char* argv[])
{ 
    LinkedList* list = new LinkedList();
    list->MakeList();
    list->Print();

    //std::cout << list->moveSectionToHead(2, 4) << std::endl;
    //list->Print();

    //LinkedList* sublist = new LinkedList();
    //sublist->MakeList();
    //sublist->Print();
    //std::cout << list->deleteSublist(sublist) << std::endl;
    //list->Print();
    
    //std::cout << "Broj zamenjenih parova je " << list->SwapPairs(4, 8) << std::endl;
    //list->Print();

    //LinkedList* newList = list->SplitOrMove();
    //std::cout << "Lista 1" << std::endl;
    //list->Print();
    //std::cout << "Lista 2" << std::endl;
    //newList->Print();

    //list->MoveMinToHead(&(list->head));
    //list->Print();
    list->SortList(list->head);
    list->Print();

    return 0;
}
