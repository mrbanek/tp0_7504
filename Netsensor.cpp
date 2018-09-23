/*
 * Netsensor.cpp
 *
 *  Created on: 15/09/2018
 *      Author: raul
 */
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include<cstdlib>
#include"Netsensor.h"
#define LONG_ARRAY 8
#define LONG_MATRIX 18
void NetSensor::readDataBase(ifstream & dataBaseFile)
{
	size_t i,fin;
	char c;
	string aux,line;
	size_t k;
	name=new string[LONG_ARRAY];
	data=new int*[LONG_MATRIX];		//falta agrandar el resize() de la matriz

	for(i=0;i<LONG_ARRAY &&  !isdigit(c) ;i++) // leo la primer linea hasta encontrar la cantidad
	{										  // de sensores en la base de datos
		dataBaseFile>>name[i];					//se puede mejorar.
		if(name[i][name[i].length()-1]==',')
			name[i].erase(name[i].length()-1);
		else
			dataBaseFile>>c;   //leo la coma por separado
		std::cout<<name[i]<<"   ";
	}
	std::cout<<"\n";
	column=i;
	getline(dataBaseFile,aux,',');
	aux=c+aux;
	for(i=0;i<LONG_MATRIX && !dataBaseFile.eof();i++)  //empiezo a cargar los datos
	{
		data[i]=new int[column];
		for(size_t j=0;j<column;j++)
		{
			if(j==0 && i==0)
			{
				data[i][j]=atoi(aux.c_str());
				std::cout<<data[i][j]<<"\t";
				j++;
			}
			if(j==(column-1))
				getline(dataBaseFile,line);
			else
				getline(dataBaseFile,line,',');
			fin=line.length();
			for(k=0;k<fin && line[k]==' ';k++);
			stringstream str_st(line);
			if(k==line.length() && line[k-1]== ' ')
				data[i][j]=-274;
			else
				str_st>>data[i][j];
			std::cout<<data[i][j]<<"\t";
		}
		std::cout<<"\n";
	}
	row=i;
}



