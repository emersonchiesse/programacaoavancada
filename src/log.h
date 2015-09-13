/*
 * log.h
 *
 *  Created on: 12 de set de 2015
 *      Author: x
 */

#ifndef LOG_H_
#define LOG_H_

#include <string>

#define LOG_NORMAL 0
#define LOG_DEBUG 1

class Log {
private:
	// path
	int level;

public:
	Log();
	virtual ~Log();

	const void LOG(std::string );
	const void debug(std::string );

	int getLevel() const {
		return level;
	}

	void setLevel(int level) {
		this->level = level;
	}
};

#endif /* LOG_H_ */
