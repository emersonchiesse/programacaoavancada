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
#include "LocalVeiculo.h"

class Linha : public Entidade
{
private:
	std::string descricao;
	CategoriaLinha categoria;
	bool somente_cartao;
	Lista<PontoLinha> pontos;
	List<PontoLinha> pontos2;
	List<Coordenada> contorno;
	List<LocalVeiculo> posicoesVeiculos;

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

	string listaPontos ();
	List<PontoLinha>* getPontos();
	List<Coordenada>* getContorno();
	List<LocalVeiculo>* getPosicoesVeiculos();

	bool inserePonto(PontoLinha *p);
	void insereCoordenada (Coordenada c);
	void inserePosicaoVeiculo (LocalVeiculo *p);
};
#endif
