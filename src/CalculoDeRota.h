#ifndef CALCULO_DE_ROTA_H
#define CALCULO_DE_ROTA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Lista.h"
#include "Rotas.h"
#include "Hora.h"
#include "Coordenada.h"

class CalculoDeRota
{
private:
//	Lista<Rotas> listaRotas;

	float custoTotal;

	Hora tempoDeslocamento;


public:
	CalculoDeRota() {};
	~CalculoDeRota() {};
	void calculaRota(Coordenada inicio, Coordenada fim, int preferencias);

};
#endif
