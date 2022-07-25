#include "LList.h"

void main()
{
	LList lista;
	lista.addToHead(9);
	lista.addToHead(8);
	lista.addToHead(7);
	lista.addToHead(6);
	lista.addToHead(5);
	lista.addToHead(4);
	lista.addToHead(3);
	lista.addToHead(2);
	lista.addToHead(1);
	lista.printAll();
	bool a = lista.relocate(3,5,7);
	lista.printAll();

}