#ifndef COORDENADA_H
#define COORDENADA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

using namespace std;

class Coordenada
{
private:
	double latitude;
	double longitude;
	int altitude;


public:
	Coordenada() { latitude = 0; longitude = 0; altitude = 0;};
	Coordenada(string lat, string lon)
	{
		latitude = ::atof(lat.c_str());
		longitude = ::atof(lon.c_str());;
		altitude = 0;
	}

	int getAltitude();
	double getLatitude();
	double getLongitude();

};
#endif
