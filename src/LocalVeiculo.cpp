#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "LocalVeiculo.h"


Coordenada LocalVeiculo::getLocal()
{
	return coordenada;
}

Motorista LocalVeiculo::getMotorista()
{
	return motorista;
}

Clima LocalVeiculo::getClima()
{
	return clima;
}

Pontualidade LocalVeiculo::getPontualidade()
{
	return pontualidade ;
}
