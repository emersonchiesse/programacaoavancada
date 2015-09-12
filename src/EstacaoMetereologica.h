#ifndef ESTACAO_METEREOLOGICA_H
#define ESTACAO_METEREOLOGICA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Entidade.h"
#include "Coordenada.h"

class EstacaoMetereologica : public Entidade
{
private:
	std::string descricao;

	Coordenada local;

};
#endif
