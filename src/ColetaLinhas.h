#ifndef COLETA_LINHAS_H
#define COLETA_LINHAS_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Thread.h"
#include "Linha.h"

class ColetaLinhas : public Thread
{
private:
	Linha linha;

	int agenda;

};
#endif
