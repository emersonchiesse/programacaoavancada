#ifndef COLETA_ROTAS_H
#define COLETA_ROTAS_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Thread.h"
#include "RotaLinha.h"

class ColetaRotas : public Thread
{
private:
	RotaLinha rota;

	std::string agenda;

};
#endif
