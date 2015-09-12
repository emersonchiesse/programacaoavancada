#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Entidade.h"


void Entidade::setId(string id)
{
	this->id = id;
}

string Entidade::getId()
{
	return id;
}

void Entidade::setNome(std::string nome)
{
	this->nome = nome;
}

string Entidade::getNome()
{
	return nome;
}

