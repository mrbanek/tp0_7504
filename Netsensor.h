/*
 * Netsensor.h
 *
 *  Created on: 15/09/2018
 *      Author: raul
 */

#ifndef TP0_7504_NETSENSOR_H_
#define TP0_7504_NETSENSOR_H_

#include <iostream>
using namespace std;
class NetSensor				//falta definir los construcores y destructores
{
	  string *name;			// arreglo dinamico que almacena la  cantidad de  sensores
	  int **data;			// datos almacenados
	  size_t row,column;	//dimensiones
public:
	  void readDataBase(ifstream &); //lee y carga los datos en una matriz
	  friend class Sensor;
};






#endif /* TP0_7504_NETSENSOR_H_ */
