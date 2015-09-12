#ifndef ENTIDADE_H
#define ENTIDADE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

using namespace std;
class Entidade
{
private:
	string id;
	string nome;


public:
	Entidade() {id = ""; nome = "";};
	Entidade(string i, string n) {id = i; nome = n;};

	void setId(std::string id);

	std::string getId();

	void setNome(string nome);

	string getNome();

};
#endif
