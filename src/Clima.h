#ifndef CLIMA_H
#define CLIMA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "EstacaoMetereologica.h"

class Clima
{
private:
	int temperatura;

	int precipitacao;

	EstacaoMetereologica estacao;

	int data;


public:
	int getTemperatura();

	void setPrecipitacao(int precipitacao);

	int getPrecipitacao();

};
#endif
