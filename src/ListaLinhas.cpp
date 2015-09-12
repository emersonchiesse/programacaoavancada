/*
 * ListaLinhas.cpp
 *
 *  Created on: 30 de ago de 2015
 *      Author: x
 */

#include "ListaLinhas.h"
#include <stdarg.h>
#include <memory>
#include <cstring>



ListaLinhas::ListaLinhas() {
}

ListaLinhas::~ListaLinhas() {
}

bool ListaLinhas::insere(Linha* l) {
	if (l == NULL)
		return false;

	return linhas.incluaInfo(l);
}

std::string string_format(const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::string str;
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}

string ListaLinhas::mostraLista() {
	string s;
	Elemento<Linha>* pElAux = NULL;
	Linha* pAlAux = NULL;
	pElAux = linhas.getpPrimeiro();
	while (NULL != pElAux)
	{
		pAlAux = pElAux->getInfo();
		s = s + string_format(string("%s\n"), //\t%s\n"),
				pAlAux->getId().c_str());//,
//				pAlAux->getNome().c_str());
		pElAux = pElAux->getProximo();
	}
	return s;
}

Linha* ListaLinhas::procura(string l) {

	Elemento<Linha>* pElAux = NULL;
	Linha* linha = NULL;
	pElAux = linhas.getpPrimeiro();
	bool achou = false;
	while (NULL != pElAux)
	{
		linha = pElAux->getInfo();
		if (linha->getId()== l)
		{
			achou = true;
			break;
		}
		pElAux = pElAux->getProximo();
	}

	if (achou)
		return linha;

	return NULL;
}

