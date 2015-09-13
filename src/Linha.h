#ifndef LINHA_H
#define LINHA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Entidade.h"
#include "CategoriaLinha.h"
#include "Lista.h"
#include "Lista2.h"
#include "PontoLinha.h"

class Linha : public Entidade
{
private:
	std::string descricao;
	CategoriaLinha categoria;
	bool somente_cartao;
	Lista<PontoLinha> pontos;
	List<PontoLinha> pontos2;
	List<Coordenada> contorno;

public:
	Linha (string id,
			string nome,
			bool cartao = false
	):Entidade(id,nome)
	{
		somente_cartao = cartao;
//		categoria = l;
	};

	~Linha() {};

	std::string getDescricao();
	std::string getCategoria();
	std::string getCartao();

	bool inserePonto(PontoLinha *p);
	string listaPontos ();
	List<PontoLinha>* getPontos();
	List<Coordenada>* getContorno();

	void insereCoordenada (Coordenada c);
};
#endif
