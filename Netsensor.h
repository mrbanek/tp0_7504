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
class NetSensor
{
	  string *name;
	  int **data;
public:
	  void readDataBase(ifstream &); //lee y carga los datos en una matriz
};






#endif /* TP0_7504_NETSENSOR_H_ */
