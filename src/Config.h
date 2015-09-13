/*
 * Config.h
 *
 *  Created on: 28 de ago de 2015
 *      Author: x
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <map>
#include <string>
#include "log.h"

namespace config {

using namespace std;

#define CONFIG_ARQUIVO_LINHAS 	"arquivoLinhas"
#define CONFIG_CARREGA_AUTO   	"iniciaAutomatico"
#define CONFIG_DIR_PONTOS		"diretorioPontos"
#define CONFIG_DIR_ROTAS		"diretorioRotas"
#define CONFIG_DIR_CONTORNOS	"diretorioContornos"
#define CONFIG_LOG_LEVEL		"loglevel"
#define CONFIG_RAIO_PONTO		"raioponto"
#define CONFIG_DESENHA_CONTORNOS "desenhaContornos"

class Config {
	std::map<std::string, std::string> options;
	Log *log;

public:
	Config();
	virtual ~Config();

	void parse(std::string cfgfile);
	string get(string);
	int getInt(string s, int i = 0);
	bool getBool(string s, bool b = true);

	void setLog(Log* log) {
		this->log = log;
	}
};

} /* namespace config */

#endif /* CONFIG_H_ */
