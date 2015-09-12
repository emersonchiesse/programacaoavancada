#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Linha.h"


std::string Linha::getDescricao()
{
	return descricao;
}

std::string Linha::getCategoria()
{
	return 0;
}

std::string Linha::getCartao()
{
	return 0;
}

bool Linha::inserePonto(PontoLinha *p) {

		pontos2.insere(*p);
//	if (p != NULL)
//		return pontos.incluaInfo(p);
//	else
//		return false;
}

string Linha::listaPontos() {


}

List<PontoLinha>* Linha::getPontos() {
	return &pontos2;
}
