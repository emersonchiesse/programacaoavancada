/*
 * Nodo.cpp
 *
 *  Created on: Jul 21, 2015
 *      Author: x
 */

#include "Nodo.h"

using namespace std;


Nodo::Nodo(string i) {
	id =i;
	x=0;
	y=0;
}

Nodo::Nodo(string i, int x, int y) {
	id=i;
	this->x=x;
	this->y=y;
}

Nodo::~Nodo() {
}

void Nodo::addVizinho(Vertice v) {
	vizinhos.push_back(v);
}

int Nodo::getCustoVizinho(string id) {

	// se eh vizinho, tem custo
	// senao eh infinito

	// se eh ele mesmo, tem custo 0;
	if (id == this->getId())
		return 0;

	int ind = procuraVizinho (id);
	if (ind >= 0)
	{
		return vizinhos[ind].getCusto();
	}
	else
		return Vertice::INFINITO;
}

int Nodo::procuraVizinho(string id) {
	for (int i = 0; i < vizinhos.size(); i++)
	{
		//if (vizinhos[i].getVizinho()->getId() == id)
		if (vizinhos[i].getId() == id)
			return i;
	}

	return -1;
}

