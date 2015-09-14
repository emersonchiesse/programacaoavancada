#ifndef THREAD_H
#define THREAD_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include "pthread.h"
#include "Config.h"
#include "log.h"

class Thread: public Log
{
private:
	pthread_t thread;


	static void * InternalThreadEntryFunc(void * This)
	{
		((Thread *)This)->executa();
		return NULL;
	}

public:
	Thread();

	virtual ~Thread();

	bool inicia()
	{
		return (pthread_create(&thread, NULL, InternalThreadEntryFunc, this) == 0);
	}

	void encerra()
	{
		(void) pthread_join(thread, NULL);

	}

    void *coleta(void)
    {
        //std::cout << "Hello, world!" << std::endl;
        return 0;
    }

    static void *coleta_helper(void *context)
    {
        return ((Thread *)context)->coleta();
    }

	void setConfig(config::Config* config) {
		this->config = config;
	}

	std::string shellcommand(const char* cmd);

protected:
   virtual void executa () = 0;
   int intervalo;
   config::Config *config;

};
#endif
