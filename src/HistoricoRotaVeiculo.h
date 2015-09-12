#ifndef HISTORICO_ROTA_VEICULO_H
#define HISTORICO_ROTA_VEICULO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Lista.h"
#include "LocalVeiculo.h"

class HistoricoRotaVeiculo
{
private:
	Lista<LocalVeiculo> historico;

	std::string  dataInicio;

	std::string  dataFim;


public:
	float getVelocidadeInstantanea(std::string data);

	float getVelocidadeMedia();

	float getDistanciaTotal();

	long getPassageirosTransportados();

	void getConsumoTotal();

};
#endif
