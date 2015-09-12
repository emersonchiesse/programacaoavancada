#ifndef CARTAO_USUARIO_H
#define CARTAO_USUARIO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Entidade.h"

class CartaoUsuario : public Entidade
{
private:
	std::string RG;

	std::string CPF;

	float saldo;

	int aquisicao;

};
#endif
