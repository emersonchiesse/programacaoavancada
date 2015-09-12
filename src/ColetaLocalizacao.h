#ifndef COLETA_LOCALIZACAO_H
#define COLETA_LOCALIZACAO_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Thread.h"
#include "LocalVeiculo.h"

class ColetaLocalizacao : public Thread
{
private:
	LocalVeiculo local;

	std::string agendat;

};
#endif
