/*
 * Vertice.h
 *
 *  Created on: Jul 22, 2015
 *      Author: x
 */

#ifndef VERTICE_H_
#define VERTICE_H_

#include <string>

class Nodo;

class Custo
{
private:
	int valor;
};

using namespace std;

class Vertice
{
public:
	const static int INFINITO=9999;

	Vertice (string n, int c)
	{
		//vizinho = n;
		id = n;
		custo = c;
	}

	~Vertice();

	int getCusto() const {
		return custo;
	}

	void setCusto(int peso) {
		this->custo = peso;
	}

	const Nodo* getVizinho() const {
		return vizinho;
	}

	void setVizinho(Nodo* vizinho) {
		this->vizinho = vizinho;
	}

	const string& getId() const {
		return id;
	}

	void setId(const string& id) {
		this->id = id;
	}

private:
	Nodo *vizinho;
	int custo;
	string id;
};

#endif /* VERTICE_H_ */
