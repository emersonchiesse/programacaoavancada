/*
 * ListaLinhas.h
 *
 *  Created on: 30 de ago de 2015
 *      Author: x
 */

#ifndef LISTALINHAS_H_
#define LISTALINHAS_H_

#include "Lista.h"
#include "Linha.h"


class ListaLinhas {
private:
	Lista<Linha> linhas;

public:
	ListaLinhas();
	virtual ~ListaLinhas();
	bool insere (Linha *l);
	string mostraLista ();

	Linha * procura (string l);

};


#endif /* LISTALINHAS_H_ */
