/*
 * log.cpp
 *
 *  Created on: 12 de set de 2015
 *      Author: x
 */

#include "log.h"
#include <iostream>


Log::Log() {

}

Log::~Log() {
}

const void Log::LOG(std::string msg) {
	std::cout << msg << std::endl;
}

const void Log::debug(std::string msg) {
	if (level == LOG_DEBUG)
		LOG(msg);
}
