/*
 * Config.cpp
 *
 *  Created on: 28 de ago de 2015
 *      Author: x
 */

#include "Config.h"
#include <fstream>
using namespace std;

namespace config {

Config::Config() {

}

Config::~Config() {
}

void Config::parse(std::string cfgfile)
{
    std::string id, eq, val;
    std::ifstream ifs (cfgfile.c_str());

    while(ifs >> id >> eq >> val)
    {
      if (id[0] == '#') continue;  // skip comments
      //if (eq != "=") throw std::runtime_error("Parse error");

      options[id] = val;
    }
}

} /* namespace config */
