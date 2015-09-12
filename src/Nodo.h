/*
 * Nodo.h
 *
 *  Created on: Jul 21, 2015
 *      Author: x
 */

#ifndef NODO_H_
#define NODO_H_

#include <vector>
#include <string>

#include "Vertice.h"

using namespace std;


class Nodo {
private:
	std::string id;
	std::vector<Vertice> vizinhos;
	int x, y;

public:
	Nodo(string i);
	Nodo(string i, int x, int y);
	virtual ~Nodo();

	void addVizinho (Vertice v);

	const std::string& getId() const {
		return id;
	}

	void setId(const std::string& id) {
		this->id = id;
	}

	const std::vector<Vertice>& getVizinhos() const {
		return vizinhos;
	}

	void setVizinhos(const std::vector<Vertice>& vizinhos) {
		this->vizinhos = vizinhos;
	}

	int getCustoVizinho(string id);
	int procuraVizinho (string id);

	int getX() const {
		return x;
	}
	int getY() const {
			return y;
	}

	void setCoord(int x, int y) {
		this->x = x;
		this->y = y;
	}


};

#endif /* NODO_H_ */
