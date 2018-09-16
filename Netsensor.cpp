/*
 * Netsensor.cpp
 *
 *  Created on: 15/09/2018
 *      Author: raul
 */
#include<fstream>
#include"Netsensor.h"
#define LONG_ARRAY 2
#define LONG_MATRIX 4
using namespace std;
void NetSensor::readDataBase(ifstream & dataBaseFile)
{
	int i;
	char c;
	name=new string[LONG_ARRAY];
	*data=new int[LONG_MATRIX];
	for(i=0;i<LONG_MATRIX;i++)
			data[i]=new int[LONG_ARRAY];
	for(i=0;i<LONG_ARRAY;i++)
	{
		dataBaseFile>>name[i];
		dataBaseFile>>c;
	}


}



