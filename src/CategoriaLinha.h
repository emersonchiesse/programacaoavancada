#ifndef CATEGORIA_LINHA_H
#define CATEGORIA_LINHA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Entidade.h"

#define CATEG_CONVENCIONAL "CONVENCIONAL"
#define CATEG_ALIMENTADOR "ALIMENTADOR"
#define CATEG_TRONCAL "TRONCAL"

//enum enumCategoriaLinha
//{
//	CATEGORIA_CONVENCIONAL=0,
//	CATEGORIA_ALIMENTADOR,
//	CATEGORIA_LINHA_DIRETA,
//	CATEGORIA_TRONCAL
//} ;



class CategoriaLinha : public Entidade
{
public:
	CategoriaLinha() {};
	CategoriaLinha(string i, string n):
		Entidade(i, n) {};

//	enumCategoriaLinha getCategoria(string);
	int getCategoria(string);
};
#endif
