#ifndef LOCAL_ONIBUS_H
#define LOCAL_ONIBUS_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "VeiculoEmpresa.h"
#include "Linha.h"
#include "Motorista.h"
#include "Coordenada.h"

class LocalOnibus
{
private:
	//VeiculoEmpresa onibus;

	Linha linha;

	Motorista motorista;

	Coordenada coordenada;

	std::string  data;

};
#endif
