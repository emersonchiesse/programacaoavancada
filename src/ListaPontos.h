/*
 * ListaPontos.h
 *
 *  Created on: 30 de ago de 2015
 *      Author: x
 */

#ifndef LISTAPONTOS_H_
#define LISTAPONTOS_H_

#include "Lista.h"
#include "PontoLinha.h"

class ListaPontos {
private:
	Lista<PontoLinha> pontos;

public:
	ListaPontos();
	virtual ~ListaPontos();

	bool insere (PontoLinha *l);
	string mostraLista ();
};

#endif /* LISTAPONTOS_H_ */
