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

namespace config {

class Config {
	std::map<std::string, std::string> options;

public:
	Config();
	virtual ~Config();

	void parse(std::string cfgfile);
};

} /* namespace config */

#endif /* CONFIG_H_ */
