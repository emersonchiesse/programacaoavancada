#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "SistemaTransportePublico.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "defs.h"


void SistemaTransportePublico::Init() {
//	linhas.
}

void SistemaTransportePublico::insereLinha(Linha *l) {

	linhas.insere(*l);
	linhas2.push_back(*l);
}

std::string SistemaTransportePublico::listaLinhas() {

	string s = "";
	for (List<Linha>::iterator i = linhas.begin();
						i != linhas.end(); i++)
		{
			Linha l = (Linha)(*i);
			s = s + l.getId() + "\n";
		}
	return s;

}

//Linha* SistemaTransportePublico::procuraLinha(string id)
//{
////	for (List<Linha>::iterator i = linhas.begin();
////					i != linhas.end(); i++)
////	{
////		Linha *l = &(*i);
////		if (l->getId()== id)
////			return &*i;
////	}
//
//	for (int i = 0; i < linhas2.size(); i++)
//	{
//		if (linhas2[i].getId()==id)
//			return *linhas2[i];
//	}
//	return NULL;
//}

int SistemaTransportePublico::procuraLinha(string id)
{
	for (int i = 0; i < linhas2.size(); i++)
	{
		if (linhas2[i].getId()==id)
			return i;
	}
	return -1;
}

void SistemaTransportePublico::inserePontoLinha(
		string linha, PontoLinha *p) {

//	Linha *l = procuraLinha(linha);
	//	if (l != NULL)
//			l->inserePonto(p);

	int ind = procuraLinha(linha);
	if (ind >= 0)
		linhas2[ind].inserePonto(p);

}

string SistemaTransportePublico::listaPontosLinha(string linha) {

//	Linha *l = procuraLinha(linha);
//
//	return l->listaPontos();
	int ind = procuraLinha(linha);
	if (ind > 0)
		return linhas2[ind].listaPontos();

	return "";

}

List<Linha>* SistemaTransportePublico::getLinhas() {
	return &linhas;
}

void SistemaTransportePublico::carregaLinhas() {

}

using namespace rapidjson;
void SistemaTransportePublico::carregaLinhas(string arquivo) {
	Document d;
	d.Parse(arquivo.c_str());
	assert(d.IsArray());
	cout << d.Size() << endl;
	for (SizeType i = 0; i < d.Size(); i++)
	{
		assert(d[i].IsObject());
		assert(d[i].HasMember(JSON_LINHA_CODIGO));
		assert(d[i][JSON_LINHA_CODIGO].IsString());
		assert(d[i].HasMember(JSON_LINHA_NOME));
		assert(d[i][JSON_LINHA_NOME].IsString());
		Linha *l = new Linha (d[i][JSON_LINHA_CODIGO].GetString(),
				d[i][JSON_LINHA_NOME].GetString());

		cout << "cod: " << d[i][JSON_LINHA_CODIGO].GetString() << endl;

		insereLinha (l);
	}
}
