#ifndef LOCAL_VEICULO_H
#define LOCAL_VEICULO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "VeiculoEmpresa.h"
#include "Coordenada.h"
#include "Linha.h"
#include "Motorista.h"
#include "Clima.h"
#include "Pontualidade.h"

class LocalVeiculo
{
private:
	//Veiculo veiculo;

	Coordenada coordenada;

	std::string  hora;

	Linha linha;

	Motorista motorista;

	int ocupacao;

	Clima clima;

	Pontualidade pontualidade;


public:
	Coordenada getLocal();

	Motorista getMotorista();

	Clima getClima();

	Pontualidade getPontualidade();

};
#endif
