#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "Thread.h"

Thread::Thread()
{
}

Thread::~Thread() {
}



std::string Thread::shellcommand(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    pclose(pipe);
    return result;
}
