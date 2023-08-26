#include <iostream>
#include <stdio.h>
#include <queue>
#include <stack>
using namespace std;
class Edge;
class Node
{
public:
	int data;
	Node* next;
	Edge* adj;
	Node* prev; //za path
	int status; // 0 - unvisited, 1 - visited, 2 - explored
	int distance;
	Node(int data) : data(data), next(nullptr), adj(nullptr), status(0), prev(nullptr), distance(INT_MAX) {}
};
class Edge
{
public:
	Node* dst;
	int weight;
	Edge* next;
	Edge() : next(nullptr), dst(nullptr), weight(0){}
	Edge(int w) : next(nullptr), dst(nullptr), weight(w) {}
	Edge(Node* dst, Edge* next, int w) : dst(dst), next(next), weight(w) {}
};
class Graph
{
public:
	Node* head;
	int count;
public:
	Graph() : head(nullptr), count(0) {}
	void insertNode(int value)
	{
		Node* newNode = new Node(value);
		if (head == nullptr)
			head = newNode;
		else
		{
			Node* curr = head;
			while (curr->next != nullptr)
				curr = curr->next;
			curr->next = newNode;
		}
		count++;
	}
	void insertEdge(int node1, int node2, int weight)
	{
		Node* curr = head;
		Node* curr2 = head;
		while (curr != nullptr && curr->data != node1)
			curr = curr->next;
		while (curr2 != nullptr && curr2->data != node2)
			curr2 = curr2->next;
		if (curr != nullptr && curr2 != nullptr)
		{
			Edge* edge = new Edge(curr2, curr->adj, weight);
			curr->adj = edge;
		}

		//while (curr != nullptr)
		//{
		//	if (curr->data == node1)
		//	{
		//		while (curr->adj != nullptr && curr->adj->next != nullptr)
		//			curr->adj = curr->adj->next;
		//		curr->adj->next = edge;
		//	}
		//	else 
		//	curr = curr->next;
		//}
	}
	void printGraph()
	{
		if (head == nullptr) cout << "Nema cvorova";
		else
		{
			Node* curr = head;
			while (curr != nullptr)
			{
				cout << "|" << endl << curr->data << "->";
				Edge* edge = curr->adj;
				while (edge != nullptr)
				{
					cout << edge->dst->data << "|";
					edge = edge->next;
				}
				cout << endl;
				curr = curr->next;
			}
			//cout << endl;
		}

	}
	Node* findNode(int value)
	{
		Node* curr = head;
		while (curr != nullptr && curr->data != value)
			curr = curr->next;
		return curr;
	}
	Edge* findEdge(int node1, int node2)
	{
		Node* n1 = findNode(node1);
		Edge* e = n1->adj;
		while (e != nullptr && e->dst->data != node2)
		{
			e = e->next;
		}
		return e;
	}
	bool deleteEdge(int node1, int node2)
	{
		Node* n1 = head;
		while (n1 != nullptr && n1->data != node1)
			n1 = n1->next;

		if (n1 != nullptr)
		{
			Edge* e = n1->adj;
			Edge* prev = nullptr;
			while (e != nullptr && e->dst->data != node2)
			{
				prev = e;
				e = e->next;
			}
			if (e == nullptr)
			{
				cout << "Nije nadjen drugi cvor" << endl;
				return false;
			}
			else if (e->dst->data == node2)
			{
				if (prev == nullptr)
				{
					n1->adj = e->next;
				}
				else
				{
					prev->next = e->next;
				}
				delete e;
				return true;
			}
		}
		cout << "Nije nadjen prvi cvor" << endl;
		return false;
	}
	bool deleteNode(int data)
	{
		Node* tmp = head;
		Node* prevNode = nullptr;
		while (tmp != nullptr && tmp->data != data)
		{
			prevNode = tmp;
			tmp = tmp->next;
		}
		if (tmp == nullptr)
		{
			cout << "Nije nadjen cvor" << endl;
			return false;
		}
		Edge* e = tmp->adj;
		while (e != nullptr) // brisanije grana tog cvora
		{
			Edge* del = e;
			e = e->next;
			tmp->adj = e;
			delete del;
		}
		Node* curr = head;
		while (curr != nullptr)
		{
			e = curr->adj;
			Edge* prevEdge = nullptr;
			while (e != nullptr)
			{
				if (e->dst != nullptr && e->dst->data == data)
				{
					Edge* del = e;
					if (prevEdge == nullptr)
						curr->adj = e->next;
					else
						prevEdge->next = e->next;
					e->dst = nullptr;
					e = e->next;
					delete del;
				}
				else
				{
					prevEdge = e;
					e = e->next;
				}
			}
			curr = curr->next;
		}
		if (prevNode == nullptr)
			head = tmp->next;
		else
			prevNode->next = tmp->next;
		delete tmp;
		count--;
		return true;

	}
	bool BreadthFirstSearch()
	{
		Node* tmp = head;
		while (tmp != nullptr)
		{
			tmp->status = 0;
			tmp = tmp->next;
		}
		int countNodes = 0;
		queue<Node*> Q;
		Q.push(head);
		while (!Q.empty())
		{
			Node* curr = Q.front();
			Edge* edge = curr->adj;
			while (edge != nullptr)
			{
				if (edge->dst->status == 0)
				{
					edge->dst->status = 1;
					Q.push(edge->dst);
				}
				edge = edge->next;
			}
			cout << curr->data << " ";
			curr->status = 2;
			countNodes++;
			Q.pop();
		}
		return countNodes == this->count;
	}

	void BreadthFirstSearch(Node* start, int& max)
	{
		Node* tmp = start;
		queue<Node*> Q;
		max = 0;
		Q.push(tmp);
		Node* curr = nullptr;
		while (!Q.empty())
		{
			curr = Q.front();
			curr->status = 2;
			max++; // OVO OTKOMENTARISI AKO TREBA DA SE BROJE CVOROVI
			Q.pop();
			Edge* edge = curr->adj;
			while (edge != nullptr)
			{
				if (edge->dst->status == 0)
				{
					//max++;	OVO OTKOMENTARISI AKO TREBA DA SE BROJE GRANE
					edge->dst->status = 1;
					//edge->dst->prev = curr;
					Q.push(edge->dst);
				}
				edge = edge->next;
			}
		}
		
		//tmp->next = nullptr;
	}

	bool DepthFirstSearch()
	{
		int numNodes = 0;
		stack<Node*> myStack;
		Node* tmp = head;
		while (tmp != nullptr)
		{
			tmp->status = 0;
			tmp = tmp->next;
		}
		myStack.push(head);

		while (!myStack.empty())
		{
			Node* curr = myStack.top();
			myStack.pop();
			Edge* edge = curr->adj;
			while (edge != nullptr)
			{
				if (edge->dst->status == 0)
				{
					edge->dst->status = 1;
					myStack.push(edge->dst);
				}
				edge = edge->next;
			}
			cout << curr->data << " ";
			curr->status = 2;
			numNodes++;
		}
		Node* tmp2 = head;
		return numNodes == this->count;
	}

	void topologicalOrderTraversal()
	{
		Node* tmp = head;
		while (tmp != nullptr)
		{
			tmp->status = 0;
			tmp = tmp->next;
		}
		tmp = head;
		while (tmp != nullptr)
		{
			Edge* edge = tmp->adj;
			while (edge != nullptr)
			{
				edge->dst->status++;
				edge = edge->next;
			}
			tmp = tmp->next;
		}
		queue<Node*> Q;
		tmp = head;
		while (tmp != nullptr)
		{
			if (tmp->status == 0)
				Q.push(tmp);
			tmp = tmp->next;
		}
		while (!Q.empty())
		{
			tmp = Q.front();
			cout << tmp->data << " ";
			Q.pop();
			Edge* edge = tmp->adj;
			while (edge != nullptr)
			{
				edge->dst->status--;
				if (edge->dst->status == 0)
					Q.push(edge->dst);
				edge = edge->next;
			}
		}
	}

	void Dijkstra(int data)
	{
		// Pronalazi se cvor
		Node* tmp = head;
		while (tmp != nullptr && tmp->data != data)
		{
			tmp = tmp->next;
		}
		if (tmp == nullptr) return;
		// U konstruktoru stavljene su sve distance na max, a status na 0.. al ae

		Node* con = head;
		while (con != nullptr)
		{
			con->distance = INT_MAX;
			con->status = 0;
			con = con->next;
		}

		auto nodeComparator = [](const Node* a, const Node* b) {
			return a->distance > b->distance;
		};

		priority_queue<Node*, vector<Node*>, decltype(nodeComparator)> Q(nodeComparator);
		tmp->distance = 0;
		Q.push(tmp);

		while (!Q.empty())
		{
			Node* curr = Q.top();
			Q.pop();
			curr->status = 2;

			Edge* edge = curr->adj;
			while (edge != nullptr)
			{
				if (edge->dst->status == 0 || edge->dst->status == 1)
				{
					if (edge->dst->distance > edge->weight + curr->distance)
					{
						edge->dst->distance = edge->weight + curr->distance;
						edge->dst->prev = curr;
						edge->dst->status = 1;
						Q.push(edge->dst);
					}
				}
				edge = edge->next;
			}

		}
		for (Node* node = head; node != nullptr; node = node->next)
		{
			if (node->distance == INT_MAX)
				cout << "Distance from " << head->data << " to " << node->data << " is unreachable." << endl;
			else
			{
				cout << "Distance from " << head->data << " to " << node->data << " is " << node->distance;
				cout << " and the path is: ";
				Node* curr = node;
				while (curr != nullptr)
				{
					cout << curr->data << " ";
					curr = curr->prev;
				}
				cout << endl;
			}
		}
	}

	/*==================== B = L = A = N = K = E = T = I ====================*/

	// Kolokvijum II 2023.
	/*Написати методу int doesConnectedComponenetExists(int k) чланицу класе графа реализоване
	коришћењем ланчаних листи чворова и потега која проверава да ли постоји бар једна повезана
	компонента грага (повезани подграф) који садржи више од k чворова. Граф је оријентисан и
	потребно је направити методу која ће га трансформисати у неоријентисан. Дозвољено је
	дефинисати додатне методе чланице класе графа ако је потребно. Водити рачуна о ефикасности
	решења. Напомена: Компонента повезаности оријентисаног графа је његов подграф за који
	важи да након трансформације оригиналног графа у неоријентисани између свака два чвора
	подграфа постоји пут, али не постоји пут ка ниједном чвору ван овог подграфа.*/
	void orientedToNonOriented()
	{
		if (head == nullptr || head->next == nullptr) return;
		Node* curr = head;
		while (curr != nullptr)
		{
			for (Edge* edg = curr->adj; edg != nullptr; edg = edg->next)
			{
				Edge* reversedg = edg->dst->adj;
				while (reversedg != nullptr && reversedg->dst != curr)
					reversedg = reversedg->next;
				if (!reversedg)
				{
					Edge* e = new Edge(curr, nullptr, 1);
					e->next = edg->dst->adj;
					edg->dst->adj = e;
				}
			}
			curr = curr->next;
		}
	}
	int doesConnectedComponenetExists(int k) /*чланицу класе графа реализоване
		коришћењем ланчаних листи чворова и потега која проверава да ли постоји бар једна повезана
		компонента грага(повезани подграф) који садржи више од k чворова...vrv vraca broj povezanih podgrafova koji imaju vise od k cvorova?*/
	{
		if (head == nullptr || head->next == nullptr) return 0; // ima nijedan ili jedan cvor
		Node* curr = head;
		int numOfNodes = 0;
		int count = 0;
		setNodeStatusAndDistance(0);
		while (curr != nullptr)
		{
			Node* tmp = curr;
			if (curr->status != 2)
			{
				int numOfNodes = 0;
				BreadthFirstSearch(curr, numOfNodes);
				if (numOfNodes > k)
					count++;
			}
			curr = curr->next;
		}		
		return count;
	}

	// Kolokvijum II (popravni) 2023.

	/*Написати методу int subgraphCnt(int p), која враћа број дисјукнтних подграфова који садрже
	бар један чвор већи од задате вредности „p“. Подргаф се сматра дисјунктним ако се из њега не
	може прећи у било који други подграф, нити се из другог подграфа може прећи у њега. За
	ефикасну реализацију претходне методе потребно је имплементирати и метод void
	toUndirected(), која дати оријентисани граф преводи у неоријентисани. Дозвољено је
	имплементирати и помоћне методе, уколико је потребно. Све методе морају бити чланице класе
	GraphAsListsInt.*/
	int subgraphCnt(int p)
	{
		if (head == nullptr || head->next == nullptr) return 0; // ima nijedan ili jedan cvor
		Node* curr = head;
		int numOfSubgraphs = 0;
		setNodeStatusAndDistance(0);
		while (curr != nullptr)
		{
			if (curr->status != 2)
			{
				queue<Node*> Q;
				Q.push(curr);
				bool foundGreater = false;
				//Node* curr = nullptr;
				while (!Q.empty())
				{
					Node* tmp = Q.front();
					tmp->status = 2;
					Q.pop();
					if (tmp->data > p)
						foundGreater = true;
					Edge* edge = tmp->adj;
					while (edge != nullptr)
					{
						if (edge->dst->status == 0)
						{
							edge->dst->status = 1;
							Q.push(edge->dst);
						}
						edge = edge->next;
					}
				}
				if (foundGreater) numOfSubgraphs++;
			}
			curr = curr->next;
		}
		return numOfSubgraphs;
	}


	bool isCyclic() // Jun II 2023.
	{
		int numNodes = 0;
		Node* tmp = head;
		while (tmp != nullptr)
		{
			tmp->status = 0;
			tmp = tmp->next;
		}
		tmp = head;
		while (tmp != nullptr)
		{
			Edge* edge = tmp->adj;
			while (edge != nullptr)
			{
				edge->dst->status++;
				edge = edge->next;
			}
			tmp = tmp->next;
		}
		queue<Node*> Q;
		tmp = head;
		while (tmp != nullptr)
		{
			if (tmp->status == 0)
				Q.push(tmp);
			tmp = tmp->next;
		}
		while (!Q.empty())
		{
			tmp = Q.front();
			cout << tmp->data << " ";
			numNodes++;
			Q.pop();
			Edge* edge = tmp->adj;
			while (edge != nullptr)
			{
				edge->dst->status--;
				if (edge->dst->status == 0)
					Q.push(edge->dst);
				edge = edge->next;
			}
		}
		return numNodes != this->count;
	}

	bool isCyclic2()
	{
		if (head == nullptr) return false;

		Node* curr = head;
		setNodeStatusAndDistance(0);
		queue<Node*>Q;
		Q.push(curr);
		while (!Q.empty())
		{
			curr = Q.front();
			if (curr->status == 2) return true;
			curr->status = 2;
			Q.pop();
			Edge* edg = curr->adj;
			while (edg != nullptr)
			{
				if (edg->dst->status != 1)
				{
					if (edg->dst->status == 0) 					
						edg->dst->status = 1;
					Q.push(edg->dst);
				}
				edg = edg->next;
			}
		}
		return false;
	}

	int BridgeCount(int a, int b) // Jun II 2022. --- BFS
	{
		Node* aa = head, * bb = head;
		if (head == nullptr || head->next == nullptr)
			return 0;
		while (aa != nullptr && aa->data != a) //nalazi se cvor a
		{
			aa = aa->next;
		}
		if (aa == nullptr) return INT_MAX;
		while (bb != nullptr && bb->data != b) //nalazi se cvor b
		{
			bb = bb->next;
		}
		if (bb == nullptr) return INT_MAX;
		if (aa == bb) return 0;
		queue<Node*> Q;
		Node* con = head;
		while (con != nullptr)
		{
			con->distance = 1;
			con->status = 0;
			con = con->next;
		}
		aa->distance = 0;
		Q.push(aa);

		while (!Q.empty())
		{
			Node* curr = Q.front();
			Q.pop();
			curr->status = 2;
			if (curr->data == b)
				return curr->distance; // pronasao je cvor

			Edge* edg = curr->adj;
			while (edg != nullptr)
			{
				if (edg->dst->status == 0)
				{					
					edg->dst->distance += 1;
					edg->dst->status = 1;
					Q.push(edg->dst);
				}
				edg = edg->next;
			}
		}
		if (Q.empty()) 
		cout << "There is no path from node " << a << " to node " << b << endl;
		return INT_MAX;
	
	}
	void setNodeStatusAndDistance(int value)
	{
		Node* curr = head;
		while (curr != nullptr)
		{
			curr->status = value;
			curr->distance = 0;
			curr = curr->next;
		}

	}

	//Oktobar II 2022.
	/*u dinamicki implementiranom orijentisanom grafu napisati funkciju bool PathExists(Node*a, Node*b, Node*c, Node*d)
	koja odredjuje da li postoji put izmedju cvorova a i b koji ukljucuje poteg uzmedju cvorova e i d*/
	bool PathExists(Node* a, Node* b, Node* c, Node* d)
	{
		if (!head || !head->next) return false;
		Node* nodeA = head;
		while (nodeA != nullptr && nodeA != a)
		{
			nodeA = nodeA->next;
		}
		if (!nodeA) return false; // cvor a ne postoji u grafu

		setNodeStatusAndDistance(0);
		
		queue<Node*> Q;
		Node* curr = nodeA;
		Q.push(curr);
		while (!Q.empty())
		{
			curr = Q.front();
			Q.pop();
			curr->status = 2;
			Edge* edg = curr->adj;
			while (edg != nullptr)
			{
				if ((curr == c || curr == d) && (edg->dst == d || edg->dst == c)) //pp.nema petlji
				{
					while (!Q.empty())
					{
						Q.pop();
					}
					curr = edg->dst; 
					break;
				}
				if (edg->dst->status == 0)
				{

					edg->dst->status = 1;
					Q.push(edg->dst);
				}
				edg = edg->next;
			}

		}
		if (curr != c && curr != d) return false;
		
		setNodeStatusAndDistance(0);
	 // ako je curr == c znaci pocinje se od d pustanje bfs. ako je curr == d pocinje se od c pustanje bfs.
		Q.push(curr);
		while (!Q.empty())
		{
			curr = Q.front();
			Q.pop();
			if (curr == b) return true;
			curr->status = 2;
			Edge* edg = curr->adj;
			while (edg != nullptr)
			{
				if (edg->dst->status == 0)
				{
					edg->dst->status = 1;
					Q.push(edg->dst);
				}
				edg = edg->next;
			}

		}
		return false;
	}


	//Septembarski 2022.
	/*﻿Avio prevoznik nudi veliki broj letova izmedju velikog broja aerodroma.
	Informacije o aerodromima i letovima zapamcene su u dinamicki realizovanim grafom koji koristi lanc ane liste.
	Dva prijatenja se nalaze na razlicitim aerodromima i zele da stignu do istog ciljnog aerodroma sa najmanjim brojem presedanja.
	Napisati metodu int numOfSameFlights(Node* airport1, Node* airport2, Node* airportEnd) koja odredjuje
	broj zajednickih letova koje ce ova dva prijatelja imati.
	Smartati da klasa cvora grafa sadrzi atribut clan klase koji ukazuje na cvor prethodnik na putu do tog cvora.
	Voditi racuna o efikasnosti resenja.*/
	int numOfSameFlights2(int airport1, int airport2, int airportEnd)
	{
		if (head == nullptr || head->next == nullptr)
			return INT_MAX;

		Node* tmp = head, * first = nullptr, * second = nullptr;

		while (tmp != nullptr) 
		{
			if (first == nullptr && tmp->data == airport1)
				first = tmp;
			if (second == nullptr && tmp->data == airport2)
				second = tmp;
			tmp = tmp->next;
		}
		if (!first || !second)
			return INT_MAX;

		queue<Node*> Q;

		setNodeStatusAndDistance(0);
		first->distance = 0;

		Q.push(first);
		Node* curr = first;

		while (!Q.empty())
		{
			curr = Q.front();
			Q.pop();
			curr->status = 2;
			if (curr->data == airportEnd)
				break; // pronasao je cvor

			Edge* edg = curr->adj;
			while (edg != nullptr)
			{
				if (edg->dst->status == 0)
				{	
					edg->dst->status = 1;
					edg->dst->prev = curr;
					Q.push(edg->dst);
				}
				edg = edg->next;
			}
		}
		while (!Q.empty())
		{
			Q.pop();
		}
		setNodeStatusAndDistance(0);
		while (second != nullptr && second->data != airport2) //nalazi se drugi aer
		{
			second = second->next;
		}
		if (second == nullptr) return INT_MAX;
		second->distance = 0;
		Q.push(second);
		Node* curr2 = second;

		while (!Q.empty())
		{
			curr2 = Q.front();
			Q.pop();
			curr2->status = 2;
			if (curr2->data == airportEnd)
				break; // pronasao je cvor

			Edge* edg = curr2->adj;
			while (edg != nullptr)
			{
				if (edg->dst->status == 0 )
				{
					edg->dst->status = 1;
					edg->dst->prev = curr2;
					Q.push(edg->dst);
					
				}
				edg = edg->next;
			}
		}

		int count = 0;
		for (curr; curr != first; curr = curr->prev)
		{
			for (Node* cmp = curr2; cmp != second; cmp = cmp->prev)
			{
				if (cmp->data == curr->data)
					count++;
			}
		}
		return count;
	}

	// Oktobarski 2022.
	bool edgeExists(Node* a, Node* b) //		da li postoji poteg u neorijentisanom grafu
	{
		Edge* edgA = a->adj;
		Edge* edgB = b->adj;
		while (edgA != nullptr && edgA->dst != b)
		{
			edgA = edgA->next;
		}
		if (edgA == nullptr) return false;
		while (edgB != nullptr && edgB->dst != a)
		{
			edgB = edgB->next;
		}
		if (edgB == nullptr) return false;
		return true;
	}
	bool isConnected() // da li je graf (slabo)povezan, ako je neorijentisan i povezan onda jeste slabo povezan
	{
		if (head == nullptr || head->next == nullptr) return false;
		Node* curr = head;
		int numNodes = 0;
		while (curr != nullptr)
		{
			numNodes++;
			curr = curr->next;
		}
		this->count = 0;
		setNodeStatusAndDistance(0);
		queue<Node*> Q;
		curr = head;
		Q.push(curr);
		
		while (!Q.empty())
		{
			curr = Q.front();
			Q.pop();
			curr->status = 2;
			count++;
			Edge* edg = curr->adj;
			while (edg != nullptr)
			{
				if (edg->dst->status == 0)
				{
					edg->dst->status = 1;
					Q.push(edg->dst);
				}
				edg = edg->next;
			}
		}
		return this->count == numNodes;
	}
	void connectGraph()		// dodaje nedostajuce grane sve dok graf ne postane povezan
	{
		Node* curr = head;
		while (curr != nullptr && !isConnected())
		{
			Node* flw = curr->next;
			if (!edgeExists(curr, flw))
			{
				Edge* e = new Edge(flw, nullptr, 1);
				e->next = curr->adj;
				curr->adj = e;
			}
			curr = curr->next;
		}
	}
	
	// Junski 2023. - povezi podgraf s najmanjim brojem potega i podgraf s najvecim brojem cvorova
	
	void connectMaxAndMin()
	{
		if (head == nullptr || head->next == nullptr) return; // ima nijedan ili jedan cvor
		Node* curr = head;
		int min = INT_MIN, max = 0;
		Node* maxSubgrapf = nullptr, *minSubgraph = nullptr;
		setNodeStatusAndDistance(0); 
		while (curr != nullptr)
		{
			Node* tmp=curr;
			if (curr->status != 2)
			{
				int numOfNodes = 0;
				BreadthFirstSearch(curr, numOfNodes);
				if (numOfNodes > max)
				{
					max = numOfNodes;
					maxSubgrapf = curr;
				}
				else if (numOfNodes < min)
				{
					min = numOfNodes;
					minSubgraph = curr;
				}
			}
			curr = curr->next; 
		}
		Edge* e = new Edge(maxSubgrapf, nullptr, 1);
		if (minSubgraph)
		{
			e->next = minSubgraph->adj;
			minSubgraph->adj = e;
		}
	}


	// Junski 2022.
	int getMaxConnectionsDisjoingSubgraph()
	{
		if (head == nullptr || head->next == nullptr) return 0; // nema potega
		Node* curr = head;
		setNodeStatusAndDistance(0);
		int max = 0;
		//int noEdg /*=*/ 0;
		while (curr != nullptr)
		{
			if (curr->status != 2)
			{
				int noEdg = 0;
				BreadthFirstSearch(curr, noEdg);
				if (noEdg > max) max = noEdg;
			}
			curr = curr->next;
		}
		return max;
	}


	//Jun II 2021
	/*vraca broj cvorova do kojih je moguce doci za tacno n skokova(prolaska kroz potege)*/
	/* ? je l se ovde gleda bez ciklusa graf, je l prolazi kroz razlicite potege ? */
	int reachableInNHoops(int a, int n)
	{
		if (head == nullptr || head->next == nullptr)
			return -1;
		Node* curr = head;
		while (curr != nullptr && curr->data != a) 
		{
			curr = curr->next;
		}
		if (curr == nullptr) return -1;

		int count = 0;
		setNodeStatusAndDistance(0);
		queue<Node*>Q;
		Q.push(curr);
		while (!Q.empty())
		{
			curr = Q.front();
			if (curr->distance == n) count++;
			curr->status = 2;
			Q.pop();
			Edge* edg = curr->adj;
			while (edg != nullptr) 
			{
				if (edg->dst->status != 2)				// == 0 ako je prost put
				{
					edg->dst->status = 1;
					edg->dst->distance = curr->distance + 1; 
					Q.push(edg->dst);
				}
				edg = edg->next;
			}
		}
		return count;
	}

};

int main(int argc, char* argv[])
{
	Graph* graf = new Graph();
	for (int i = 1; i <= 11; i++)
		graf->insertNode(i);
	//graf->insertEdge(1, 3, 1);
	//graf->insertEdge(1, 2, 1);
	//graf->insertEdge(2, 3, 1);
	//graf->insertEdge(2, 4, 1);
	////graf->insertEdge(5, 2, 1);
	//graf->insertEdge(3, 5, 1);
	//graf->insertEdge(4, 5, 1);
	////graf->insertEdge(0, 3, 1);
	//graf->insertEdge(5, 6, 1);

	//graf->insertEdge(1, 1, 1);
		graf->insertEdge(1, 2, 1);		//graf->insertEdge(2, 3, 1);
		graf->insertEdge(1, 3, 1);		//graf->insertEdge(2,4, 1);		

		graf->insertEdge(3, 5, 1);		graf->insertEdge(2, 5, 1);
		graf->insertEdge(4, 5, 1);		graf->insertEdge(5, 4, 1);

		graf->insertEdge(7, 8,1);
		graf->insertEdge(8, 9,1);
		graf->insertEdge(9, 10,1);
		graf->insertEdge(10, 11, 1);


		/*
	       5-4----
			 ^   |
			 |   |
		1 - 2 -> 3 
			 
		*/

	graf->printGraph();
	//
	//if (!(graf->findEdge(6, 6))) cout << "Nije nadjeno" << endl;
	//else cout << "Nadjena grana" << endl;
	//cout << "Broj cvorova je " << graf->count << endl;
	// 
	//if (graf->deleteEdge(1, 1)) cout << "uspesno obrisano" << endl;
	//else cout << "neuspesno obrisano" << endl;
	// 
	//if (graf->deleteNode(6)) cout << "uspesno obrisano" << endl;
	//else cout << "neuspesno" << endl;

	//graf->printGraph();

	//if (graf->BreadthFirstSearch()) cout << "Uspesan bfs" << endl;
	if (graf->isCyclic()) cout << "Ciklican" << endl;
	else cout << "nema ciklusi" << endl;

	graf->Dijkstra(1);
	cout << "Najkraci put od cvora a do cvora b je: " << graf->BridgeCount(1, 4) << endl;

	//if (graf->PathExists(1,5,2,4)) cout << "Postoji put" << endl;
	//else cout << "ne postoji put" << endl;

	//cout << "Broj zajednickih grana za 1 i 2 do 5 je " << graf->numOfSameFlights2(1, 2, 6) << endl;

	//cout << graf->reachableInNHoops(3, 1) << endl;
	cout << graf->isConnected() << endl;
	//graf->connectGraph();
	//cout << graf->isConnected() << endl;
	//cout << graf->getMaxConnectionsDisjoingSubgraph() << endl;
	//graf->setNodeStatusAndDistance(0); 

	//graf->connectMaxAndMin(); 

	graf->orientedToNonOriented();
	graf->printGraph();

	cout << graf->isConnected() << endl;
	cout << "broj podgrafova sa vise od k cvorova u grafu: " << graf->doesConnectedComponenetExists(4) << endl; 

	cout << "broj podgrafova sa barem 1 cvorom koji ima vecu vrednost: " << graf->subgraphCnt(4) << endl;

	return 0;
}
