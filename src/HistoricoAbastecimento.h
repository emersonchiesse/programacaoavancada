#ifndef HISTORICO_ABASTECIMENTO_H
#define HISTORICO_ABASTECIMENTO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Combustivel.h"

class HistoricoAbastecimento
{
private:
	float abastecimento;

	std::string data;

	Combustivel combustivel;

};
#endif
