#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <fstream>
#include <dirent.h>
#include <sstream>

#include "SistemaTransportePublico.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "defs.h"
#include "Convert.h"

using namespace rapidjson;

void SistemaTransportePublico::Init(config::Config *c,
		Log *l) {
	config = c;
	log = l;

	if (config->getBool(CONFIG_CARREGA_AUTO, false))
	{
		if (config->getBool(CONFIG_CARREGA_AUTO_LINHAS, false))
			carregaLinhas();
		if (config->getBool(CONFIG_CARREGA_AUTO_PONTOS, false))
			carregaPontos();
		if (config->getBool(CONFIG_CARREGA_AUTO_CONTORNO, false))
			carregaContornos();
	}
}

void SistemaTransportePublico::insereLinha(Linha *l) {

	linhas.insere(*l);
	linhas2.push_back(*l);
}

std::string SistemaTransportePublico::listaLinhas() {

	string s = "";
	std::ostringstream out;
	for (List<Linha>::iterator i = linhas.begin();
						i != linhas.end(); i++)
		{
			Linha l = (Linha)(*i);
			s = s + l.getId() + "\n";
			out << l.getId() << endl; //"\t" << l.getNome() << endl;
		}
	return out.str();

}

void SistemaTransportePublico::carregaRotas() {
	// lista arquivos do diretorio
	// extrai linha do nome
	DIR *dir;
	struct dirent *ent;
	string diretorio = config->get(CONFIG_DIR_ROTAS);

	log->LOG("processando diretorio: " + diretorio);

	if ((dir = opendir (diretorio.c_str())) != NULL)
	{
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {

		string arquivo (ent->d_name);
		log->LOG("processando arquivo: " + arquivo);

		if (arquivo == "." || arquivo == "..")
			continue;

		int ind = arquivo.find("-")+1;
		string linha = arquivo.substr(ind, 3);

		// TODO checa se linha existe
		carregaRotas (linha, diretorio + "/" + arquivo);
	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
		log->LOG("erro para abrir diretorio ");
	}
}

void SistemaTransportePublico::carregaRotas(string linha, string arquivo) {

	// valida parametros
	if ((arquivo.size() == 0) || (linha.size() == 0))
	{
		log->LOG("parametros vazios.");
		return;
	}

	log->LOG("carregando arquivo de pontos: " + arquivo +
			" da linha " + linha);

	// verifica se arquivo existe
	std::ifstream t (arquivo.c_str());
	if (!t)
	{
		log->LOG("arquivo nao existe");
		return;
	}

	// transforma arquivo de ifstream para string
	std::string str;
	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

	if (str.length() == 0)
	{
		log->LOG("arquivo vazio");
		return;
	}
	// parse de string para JSON
	Document d;
	d.Parse(str.c_str());
	assert(d.IsArray());
	cout << d.Size() << endl;
	for (SizeType i = 0; i < d.Size(); i++)
	{
		assert(d[i].IsObject());
		assert(d[i].HasMember(JSON_PONTO_NOME));
		assert(d[i][JSON_PONTO_NOME].IsString());
		assert(d[i].HasMember(JSON_PONTO_LATITUDE));
		assert(d[i][JSON_PONTO_LATITUDE].IsString());
		assert(d[i].HasMember(JSON_PONTO_LONGITUDE));
		assert(d[i][JSON_PONTO_LONGITUDE].IsString());
		assert(d[i].HasMember(JSON_PONTO_TIPO));
		assert(d[i][JSON_PONTO_TIPO].IsString());
		assert(d[i].HasMember(JSON_PONTO_NUMERO));
		assert(d[i][JSON_PONTO_NUMERO].IsString());
		assert(d[i].HasMember(JSON_PONTO_SENTIDO));
		assert(d[i][JSON_PONTO_SENTIDO].IsString());
		assert(d[i].HasMember(JSON_PONTO_SEQUENCIA));
		assert(d[i][JSON_PONTO_SEQUENCIA].IsString());

		string lat = d[i][JSON_PONTO_LATITUDE].GetString();
		lat[3]='.';
		string lon = d[i][JSON_PONTO_LONGITUDE].GetString();
		lon[3]='.';

		Coordenada c (lat, lon);

		PontoLinha *p = new PontoLinha(
				d[i][JSON_PONTO_NOME].GetString(),
				d[i][JSON_PONTO_NUMERO].GetString(),
				d[i][JSON_PONTO_TIPO].GetString(),
				d[i][JSON_PONTO_SENTIDO].GetString(),
				0,
				0,
				c
		);

		cout << "ponto: " << d[i][JSON_PONTO_NOME].GetString()
									<< " lat " << lat
									<< " lon " << lon
									<< endl;

		inserePontoLinha (linha, p);
	}
	log->LOG("pontos inseridos:"  + convert::intToString(d.Size()));
}

void SistemaTransportePublico::carregaContornos() {
	// lista arquivos do diretorio
	// extrai linha do nome
	DIR *dir;
	struct dirent *ent;
	string diretorio = config->get(CONFIG_DIR_CONTORNOS);

	log->LOG("processando diretorio: " + diretorio);

	if ((dir = opendir (diretorio.c_str())) != NULL)
	{
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {

		string arquivo (ent->d_name);
		log->LOG("processando arquivo: " + arquivo);

		if (arquivo == "." || arquivo == "..")
			continue;

		int ind = arquivo.find("-")+1;
		string linha = arquivo.substr(ind, 3);

		// TODO checa se linha existe
		ind = procuraLinha(linha);
		if (ind >= 0)
			carregaContornos (ind, diretorio + "/" + arquivo);

	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
		log->LOG("erro para abrir diretorio ");
	}
}

void SistemaTransportePublico::carregaContornos(int linha, string arquivo) {

	// valida parametros
	if ((arquivo.size() == 0) || (linha < 0))
	{
		log->LOG("parametros invalidos.");
		return;
	}

	// verifica se arquivo existe
	std::ifstream t (arquivo.c_str());
	if (!t)
	{
		log->LOG("arquivo nao existe");
		return;
	}

	// transforma arquivo de ifstream para string
	std::string str;
	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

	if (str.length() == 0)
	{
		log->LOG("arquivo vazio");
		return;
	}
	// parse de string para JSON
	Document d;
	d.Parse(str.c_str());
	assert(d.IsArray());
	for (SizeType i = 0; i < d.Size(); i++)
	{
		assert(d[i].IsObject());
		assert(d[i].HasMember(JSON_PONTO_LATITUDE));
		assert(d[i][JSON_PONTO_LATITUDE].IsString());
		assert(d[i].HasMember(JSON_PONTO_LONGITUDE));
		assert(d[i][JSON_PONTO_LONGITUDE].IsString());

		string lat = d[i][JSON_PONTO_LATITUDE].GetString();
		lat[3]='.';
		string lon = d[i][JSON_PONTO_LONGITUDE].GetString();
		lon[3]='.';

		Coordenada c (lat, lon);

		//log->debug("coord: " + lat + ", " + lon );
		insereContorno (linha, c);
	}
	log->LOG("contornos inseridos: " + convert::intToString(d.Size()));
}

void SistemaTransportePublico::insereContorno(int linha, Coordenada c) {
	linhas2[linha].insereCoordenada(c);
}

void SistemaTransportePublico::insereLPosicaoVeiculo(string linha,
		LocalVeiculo* l) {
	int ind = procuraLinha(linha);
	if (ind > 0)
		linhas2[ind].inserePosicaoVeiculo(l);
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
	carregaLinhas(config->get(CONFIG_ARQUIVO_LINHAS));
}

void SistemaTransportePublico::carregaLinhas(string arquivo) {

	// valida parametro
	if (arquivo.size() == 0)
		return;

	log->LOG("carregando arquivo de linhas: " + arquivo);

	// verifica se arquivo existe
	std::ifstream t (arquivo.c_str());
	if (!t)
	{
		log->LOG("arquivo nao existe");
		return;
	}

	// transforma arquivo de ifstream para string
	std::string str;
	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
	            std::istreambuf_iterator<char>());

	// parse de string para JSON
	Document d;
	d.Parse(str.c_str());
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

		log->LOG("cod: " + string(d[i][JSON_LINHA_CODIGO].GetString()) + " nome: " +
				string(d[i][JSON_LINHA_NOME].GetString()));

		insereLinha (l);
	}
	log->LOG("linhas inseridas: "  + convert::intToString(d.Size()));
}

void SistemaTransportePublico::carregaPontos() {

	// lista arquivos do diretorio
	// extrai linha do nome
	DIR *dir;
	struct dirent *ent;
	string diretorio = config->get(CONFIG_DIR_PONTOS);

	log->LOG("processando diretorio: " + diretorio);

	if ((dir = opendir (diretorio.c_str())) != NULL)
	{
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {

		string arquivo (ent->d_name);
		log->LOG("processando arquivo: " + arquivo);

		if (arquivo == "." || arquivo == "..")
			continue;

		int ind = arquivo.find("-")+1;
		string linha = arquivo.substr(ind, 3);

		// TODO checa se linha existe
		carregaPontos (linha, diretorio + "/" + arquivo);
	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
		log->LOG("erro para abrir diretorio ");
	}
}

void SistemaTransportePublico::carregaPontos(string linha, string arquivo) {

	// valida parametros
	if ((arquivo.size() == 0) || (linha.size() == 0))
	{
		log->LOG("parametros vazios.");
		return;
	}

	log->LOG("carregando arquivo de pontos: " + arquivo +
			" da linha " + linha);

	// verifica se arquivo existe
	std::ifstream t (arquivo.c_str());
	if (!t)
	{
		log->LOG("arquivo nao existe");
		return;
	}

	// transforma arquivo de ifstream para string
	std::string str;
	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());

	if (str.length() == 0)
	{
		log->LOG("arquivo vazio");
		return;
	}
	// parse de string para JSON
	Document d;
	d.Parse(str.c_str());
	assert(d.IsArray());
	cout << d.Size() << endl;
	for (SizeType i = 0; i < d.Size(); i++)
	{
		assert(d[i].IsObject());
		assert(d[i].HasMember(JSON_PONTO_NOME));
		assert(d[i][JSON_PONTO_NOME].IsString());
		assert(d[i].HasMember(JSON_PONTO_LATITUDE));
		assert(d[i][JSON_PONTO_LATITUDE].IsString());
		assert(d[i].HasMember(JSON_PONTO_LONGITUDE));
		assert(d[i][JSON_PONTO_LONGITUDE].IsString());
		assert(d[i].HasMember(JSON_PONTO_TIPO));
		assert(d[i][JSON_PONTO_TIPO].IsString());
		assert(d[i].HasMember(JSON_PONTO_NUMERO));
		assert(d[i][JSON_PONTO_NUMERO].IsString());
		assert(d[i].HasMember(JSON_PONTO_SENTIDO));
		assert(d[i][JSON_PONTO_SENTIDO].IsString());
		assert(d[i].HasMember(JSON_PONTO_SEQUENCIA));
		assert(d[i][JSON_PONTO_SEQUENCIA].IsString());

		string lat = d[i][JSON_PONTO_LATITUDE].GetString();
		lat[3]='.';
		string lon = d[i][JSON_PONTO_LONGITUDE].GetString();
		lon[3]='.';

		Coordenada c (lat, lon);

		PontoLinha *p = new PontoLinha(
				d[i][JSON_PONTO_NOME].GetString(),
				d[i][JSON_PONTO_NUMERO].GetString(),
				d[i][JSON_PONTO_TIPO].GetString(),
				d[i][JSON_PONTO_SENTIDO].GetString(),
				0,
				0,
				c
		);

//		log->LOG("ponto: " + d[i][JSON_PONTO_NOME].GetString()
//									+ " lat " + lat
//									+ " lon " + lon);

		inserePontoLinha (linha, p);
	}
	log->LOG("pontos inseridos:"  + convert::intToString(d.Size()));
}

void SistemaTransportePublico::carregaVeiculos(string arquivo) {

	// valida parametro
	if (arquivo.size() == 0)
		return;

	log->LOG("carregando arquivo de linhas: " + arquivo);

	// verifica se arquivo existe
	std::ifstream t (arquivo.c_str());
	if (!t)
	{
		log->LOG("arquivo nao existe");
		return;
	}

	// extrai data e hora
	int ind = arquivo.find("--")+2;
	string data = arquivo.substr(ind, 8);
//	ind = arquivo.find(".")-6;
//	string hora = arquivo.substr(ind, 6);

	// transforma arquivo de ifstream para string
	std::string str;
	t.seekg(0, std::ios::end);
	str.reserve(t.tellg());
	t.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(t)),
	            std::istreambuf_iterator<char>());

	// parse de string para JSON
	Document d;
	d.Parse(str.c_str());
	assert(d.IsArray());
	cout << d.Size() << endl;
	for (SizeType i = 0; i < d.Size(); i++)
	{
		assert(d[i].IsObject());
		assert(d[i].HasMember(JSON_VEICULO_LINHA));
		assert(d[i][JSON_VEICULO_LINHA].IsString());
		assert(d[i].HasMember(JSON_VEICULO_PREFIXO));
		assert(d[i][JSON_VEICULO_PREFIXO].IsString());
		assert(d[i].HasMember(JSON_VEICULO_LAT));
		assert(d[i][JSON_VEICULO_LAT].IsString());
		assert(d[i].HasMember(JSON_VEICULO_LONG));
		assert(d[i][JSON_VEICULO_LONG].IsString());
		assert(d[i].HasMember(JSON_VEICULO_HORA));
		assert(d[i][JSON_VEICULO_HORA].IsString());
//		assert(d[i].HasMember(JSON_VEICULO_ADAP));
//		assert(d[i][JSON_VEICULO_ADAP].IsString());

		string lat = d[i][JSON_PONTO_LATITUDE].GetString();
		lat[3]='.';
		string lon = d[i][JSON_PONTO_LONGITUDE].GetString();
		lon[3]='.';

		Coordenada c (lat, lon);

		LocalVeiculo *l = new LocalVeiculo (
				d[i][JSON_VEICULO_PREFIXO].GetString(),
				data,
				d[i][JSON_VEICULO_HORA].GetString(),
				c
				);

		insereLPosicaoVeiculo (d[i][JSON_VEICULO_LINHA].GetString(),
				l);
	}
	log->LOG("posicoes de veiculos inseridas: "  + convert::intToString(d.Size()));
}
