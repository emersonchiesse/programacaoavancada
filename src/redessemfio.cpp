//============================================================================
// Name        : redessemfio.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif


#include "Grafo.h"

using namespace std;

void caminhomaiscurto(Grafo g)
{
	string n1, n2;
	cout << "nodo 1: ";
	cin >> n1;
	cout << "nodo 2: ";
	cin >> n2;

	g.caminhomaiscurto(n1, n2);
}

int main1() {

	Grafo grafo;

	bool run = true;
	string command;

	while (run)
	{
		cout << "$ ";
		cin >> command;

		switch (command[0])
		{

		// load nodos
		case '1':
			grafo.load();
			break;

		// list nodos
		case '2':
			cout << "list nodos: \n";
			grafo.list();
			break;

		// caminho mais curto
		case '3':
			caminhomaiscurto(grafo);
			break;

		// quit
		case 'q': run = false;
					break;
		default:
			break;
		}
	}

	cout << "bye";
	return 0;
}
