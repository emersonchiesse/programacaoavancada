#ifndef ROTA_LINHA_H
#define ROTA_LINHA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Lista.h"
#include "Linha.h"
#include "Coordenada.h"

class RotaLinha //: public Lista
{
private:
	Linha linha;

	Lista<Coordenada> coordenadas;

};
#endif
