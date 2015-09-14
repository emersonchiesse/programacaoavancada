#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <ctime>

#include "ColetaLinhas.h"
#include <unistd.h>
#include <sstream>


void ColetaLinhas::executa() {
	intervalo = config->getInt(CONFIG_THREAD_COLETA_LINHA);
	string url = config->get(CONFIG_URL_GET_LINHAS);
	bool sai = false;

	string comando;
	string resultado;

	while (!sai)
	{
		time_t t = time(0);   // get time now
		struct tm * now = localtime( & t );
		std::ostringstream  arqsaida;

		arqsaida << config->get(CONFIG_URL_GET_LINHAS_ARQ_SAIDA)
				<< (now->tm_year + 1900)
				<< (now->tm_mon + 1)
		        << now->tm_mday
				<< "-"
				<< now->tm_hour
				<< now->tm_min
				<< now->tm_sec
				<< ".txt"
				;

		comando = "wget -O " + arqsaida.str() + " " + url;
		// get arquivo do webservice
		resultado = Thread::shellcommand(comando.c_str());

		LOG(resultado);
		sleep(intervalo);
	}
}
