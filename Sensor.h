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
#include "Netsensor.h"
#define  OK_QUERY 0
#define  NO_DATA 1
#define UNKNOW_ID 2
#define  BAD_QUERY 3
using namespace std;
class Sensor
{
	string name; // nombre del sensor
	size_t ranStart,ranEnd;  //Rango a promediar
	int N;       //cantidad de elementos de la consulta
	float average,min,max;
	int badQuery;  //Errores en la consulta  puede ser BAD QUERY NO DATA UNKNOW ID

public:

	Sensor (); // Constructor sin argumentos
	size_t  lengthArray( ); // tamaño del arreglo
	void   queryTemp(istream *&,ostream *&,ifstream &);  //consulta del promedio, maximo y minimo
	void   searchAverage(bool &,NetSensor &,size_t &);   // Busca el que promedio tiene que hacer
	void   getAverage(float *); //calculo el promedio
	friend istream & operator>>(istream &,Sensor &);
	friend ostream & operator<<(ostream &,const Sensor &);


};

#endif /* TP0_7504_SENSOR_H_ */
