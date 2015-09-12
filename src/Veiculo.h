#ifndef VEICULO_H
#define VEICULO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Fabricante.h"
#include "Combustivel.h"

class Veiculo
{
private:
	std::string modelo;

	float consumoMedio;

	Fabricante fabricante;

	Combustivel combustivel;

	int capacidade;

	long odometro;

	int inicioAtividade;

	float custo;


public:
	Veiculo();
	virtual void deslocamento()=0;

};
#endif
