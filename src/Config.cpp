/*
 * Config.cpp
 *
 *  Created on: 28 de ago de 2015
 *      Author: x
 */

#include "Config.h"
#include <fstream>
#include "Convert.h"

using namespace std;

namespace config {

Config::Config() {
	log = NULL;
}

Config::~Config() {
}

void Config::parse(std::string cfgfile)
{
	log->LOG("abrindo arquivo de config: " + cfgfile);
    std::string id, eq, val;
    std::ifstream ifs (cfgfile.c_str());

    if (!ifs)
    {
    	log->LOG("arquivo de config nao existe");
    	return;
    }
    while(ifs >> id >> eq >> val)
    {
      if (id[0] == '#') continue;  // skip comments
      //if (eq != "=") throw std::runtime_error("Parse error");

      options[id] = val;
      log->LOG(id + eq + val);
    }

    log->setLevel(atoi(get(CONFIG_LOG_LEVEL).c_str()));
    log->LOG("done");
}


string Config::get(string id) {
	return options[id];
}

int Config::getInt(string c, int i) {
	string s = get(c);

	if (s.length() == 0)
		return i;
	else
		return atoi (s.c_str());
}

void Config::set(string id, string valor) {
	options[id] = valor;
}

bool Config::getBool(string c, bool b) {
	string s = get(c);

	if (s.length() == 0)
		return true;
	else
		return atoi (s.c_str());
}

void Config::setBool(string id, bool valor) {
	options[id] = convert::intToString(valor);
}

} /* namespace config */
