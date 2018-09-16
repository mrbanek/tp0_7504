/*
 * Netsensor.cpp
 *
 *  Created on: 15/09/2018
 *      Author: raul
 */
#include<fstream>
#include<string>
#include<iostream>
#include<cstdlib>
#include"Netsensor.h"
#define LONG_ARRAY 8
#define LONG_MATRIX 8
void NetSensor::readDataBase(ifstream & dataBaseFile)
{
	int i,sizeArray;
	char c;
	string aux;
	name=new string[LONG_ARRAY];
	data=new int*[LONG_MATRIX];

	for(i=0;i<LONG_ARRAY &&  !isdigit(c) ;i++)
	{
		dataBaseFile>>name[i];
		if(name[i][name[i].length()-1]==',')
			name[i].erase(name[i].length()-1);
		else
			dataBaseFile>>c;   //leo la coma por separado
		std::cout<<name[i]<<"\t";
	}
	std::cout<<"\n";
	sizeArray=i;
	aux=c;
	for(i=0;i<LONG_MATRIX;i++)
	{
		data[i]=new int[sizeArray];
		for(int j=0;j<sizeArray;j++)
		{
			if(j==0)
			{
				data[i][j]=atoi(aux.c_str());
				std::cout<<data[i][j]<<"\t";
				j++;
				dataBaseFile>>aux;
			}

			dataBaseFile>>data[i][j];
			dataBaseFile>>aux;
			std::cout<<data[i][j]<<"\t";

		}
		std::cout<<"\n";
	}



}



