#ifndef HORARIO_LINHA_H
#define HORARIO_LINHA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Linha.h"
#include "Hora.h"
#include "TipoDia.h"
#include "PontoLinha.h"

class HorarioLinha
{
private:
	Linha linha;

	Hora hora;

	TipoDia dia;

	int numero;

	PontoLinha ponto;

};
#endif
