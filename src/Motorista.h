#ifndef MOTORISTA_H
#define MOTORISTA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Entidade.h"
#include "Empresa.h"

class Motorista : public Entidade
{
private:
	Empresa empresa;

	std::string matricula;


public:
	std::string getMatricula();

};
#endif
