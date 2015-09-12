/*
 * ListaPontos.cpp
 *
 *  Created on: 30 de ago de 2015
 *      Author: x
 */

#include "ListaPontos.h"

ListaPontos::ListaPontos() {

}

ListaPontos::~ListaPontos() {
}

bool ListaPontos::insere(PontoLinha* l) {
	if (l == NULL)
		return false;

	pontos.incluaInfo(l);
	return true;
}

string ListaPontos::mostraLista() {
	return "";
}
