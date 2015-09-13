#ifndef LOCAL_VEICULO_H
#define LOCAL_VEICULO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "VeiculoEmpresa.h"
#include "Coordenada.h"
//#include "Linha.h"
#include "Motorista.h"
#include "Clima.h"
#include "Pontualidade.h"

class LocalVeiculo
{
private:
	//Veiculo veiculo;

	std::string prefixo;
	Coordenada coordenada;
	std::string  data;
	std::string  hora;
//	Linha linha;
	Motorista motorista;
	int ocupacao;
	Clima clima;
	Pontualidade pontualidade;


public:
	LocalVeiculo () {
		ocupacao = 0;
	};
	LocalVeiculo(string p,
			string d,
			string h,
			Coordenada c,
			int _ocupacao = 0
			): prefixo(p), data(d), hora(h),
					coordenada(c),
					ocupacao(_ocupacao)
	{};

	Coordenada getLocal();
	Motorista getMotorista();
	Clima getClima();
	Pontualidade getPontualidade();

	Coordenada* getCoordenada() {
		return &coordenada;
	}
};
#endif
