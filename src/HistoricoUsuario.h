#ifndef HISTORICO_USUARIO_H
#define HISTORICO_USUARIO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "CartaoUsuario.h"
#include "PontoLinha.h"

class HistoricoUsuario
{
private:
	CartaoUsuario cartao;

	std::string data;

	PontoLinha ponto;

};
#endif
