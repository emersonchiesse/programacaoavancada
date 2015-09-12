#ifndef HORA_H
#define HORA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>


class Hora
{
private:
	std::string hora;


public:
	Hora (){
		hora="";
	}
	std::string getHora();

	void operationSoma();

	void operationDiferenca();

};
#endif
