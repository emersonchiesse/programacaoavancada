#ifndef PONTO_LINHA_H
#define PONTO_LINHA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Coordenada.h"
#include "TipoPonto.h"

using namespace std;

class PontoLinha
{
private:
	std::string nome;
	std::string num;
	Coordenada coordenada;
	int sequencia;
	string tipo;
	int grupo;
	std::string sentido;

public:
	PontoLinha() { grupo = 0; sequencia = 0;};
	PontoLinha(string _nome,
			string _num,
			string _tipo,
			string _sentido,
			int _grupo,
			int seq,
			Coordenada c):
				nome(_nome),
				num(_num),
				tipo(_tipo),
				sentido(_sentido),
				grupo(_grupo),
				coordenada(c),
				sequencia(seq)
	{

	};

	Coordenada *getCoordenada ();
};
#endif
