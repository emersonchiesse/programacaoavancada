#ifndef PONTO_INTERESSE_H
#define PONTO_INTERESSE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "CategoriaPonto.h"
#include "Coordenada.h"

class PontoInteresse
{
private:
	std::string nome;

	CategoriaPonto categoria;

	Coordenada coordenada;

};
#endif
