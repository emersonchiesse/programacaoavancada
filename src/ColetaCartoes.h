#ifndef COLETA_CARTOES_H
#define COLETA_CARTOES_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Thread.h"
#include "CartaoUsuario.h"

class ColetaCartoes : public Thread
{
private:
	CartaoUsuario cartoes;

	int agenda;

};
#endif
