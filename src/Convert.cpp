/*
 * Convert.cpp
 *
 *  Created on: 13 de set de 2015
 *      Author: x
 */

#include "Convert.h"
#include <sstream>

namespace convert {


std::string  intToString (int i)
{
	std::string s;
	std::stringstream out;
	out << i;
	return out.str();
}

} /* namespace convert */
