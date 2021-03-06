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
#include "log.h"
#include "LocalVeiculo.h"

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

	config::Config *config;
	Log *log;

public:
	SistemaTransportePublico (): config(0), log(0) {};
	void Init (config::Config *c, Log *l) ;
	string sumario();

	void carregaLinhas ();
	void carregaLinhas (string arquivo);
	string listaLinhas(vector<string> *lista);
	void insereLinha(Linha *l);

	string listaPontosLinha (string linha);
	void carregaPontos();
	void carregaPontos (string linha, string arquivo);
	void inserePontoLinha (string linha, PontoLinha *p);

	void carregaRotas();
	void carregaRotas (string linha, string arquivo);

	void carregaContornos();
	void carregaContornos (int linha, string arquivo);
	void insereContorno (int linha, Coordenada c);

	void carregaVeiculos(string);
	void carregaArquivoVeiculos(string arquivo);
	void inserePosicaoVeiculo (string linha, LocalVeiculo* l);
	List<LocalVeiculo> *getPosicoesVeiculos (string linha){
		int ind = procuraLinha (linha);
		return linhas2[ind].getPosicoesVeiculos();
	}
	//ListaLinhas * getLinhas();
	List<Linha>* getLinhas();
//	Linha* procuraLinha(string id);
	int procuraLinha(string id);

	std::vector<Linha>* getLinhas2() {
		return &linhas2;
	}

	List<PontoLinha> *getPontos (string linha){
		int ind = procuraLinha (linha);
		return linhas2[ind].getPontos();
	}
	List<Coordenada> *getContorno (string linha){
		int ind = procuraLinha (linha);
		return linhas2[ind].getContorno();
	}


};
#endif
