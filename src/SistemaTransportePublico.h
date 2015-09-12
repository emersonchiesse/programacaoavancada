#ifndef SISTEMA_TRANSPORTE_PUBLICO_H
#define SISTEMA_TRANSPORTE_PUBLICO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Lista.h"
#include "ListaLinhas.h"
#include "Empresa.h"
#include "CartaoUsuario.h"
#include "CalculoDeRota.h"
#include "SistemaRastreamentoPassageiro.h"
#include "Config.h"

using namespace std;

class SistemaTransportePublico
{
private:
	List<Linha> linhas;
	//ListaLinhas linhas;
	std::vector<Linha> linhas2;
	Lista<Empresa> empresas;
	Lista<CartaoUsuario> passageiros;
	CalculoDeRota calculoRota;
	SistemaRastreamentoPassageiro usuarios;
	config::Config config;

public:
	SistemaTransportePublico () {};
	void Init ();

	void carregaLinhas ();
	void carregaLinhas (string arquivo);
	void insereLinha(Linha *l);
	string listaLinhas();

	void inserePontoLinha (string linha, PontoLinha *p);
	string listaPontosLinha (string linha);

	//ListaLinhas * getLinhas();
	List<Linha>* getLinhas();
//	Linha* procuraLinha(string id);
	int procuraLinha(string id);

	std::vector<Linha>& getLinhas2() {
		return linhas2;
	}

	List<PontoLinha> *getPontos (string linha){
		int ind = procuraLinha (linha);
		return linhas2[ind].getPontos();
	}
};
#endif
