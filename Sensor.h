/*
 * Sensor.h
 *
 *  Created on: 09/09/2018
 *      Author: raul
 */

#ifndef TP0_7504_SENSOR_H_
#define TP0_7504_SENSOR_H_
#include <iostream>
#include <fstream>
using namespace std;
class Sensor
{
	string name; // nombre del sensor
	size_t ranStart,ranEnd;  //Rango a promediar
	size_t min,max,average,N;
	bool good,bad;     //


public:

	Sensor (); // Constructor sin argumentos
	size_t  lengthArray( ); // tamaño del arreglo
	void   queryTemp(istream *&,ostream *&,ifstream &);  //consulta del promedio, maximo y minimo
	void   searchAverage(bool &, Sensor &);   // Busca el promedio
	friend istream & operator>>(istream &,Sensor &);
	friend ostream & operator<<(ostream &, const Sensor &);


};

#endif /* TP0_7504_SENSOR_H_ */
