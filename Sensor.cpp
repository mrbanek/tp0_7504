/*
 * Sensor.cpp
 *
 *  Created on: 09/09/2018
 *      Author: raul
 */
#include<string>
#include<sstream>
#include "Sensor.h"
#include "Netsensor.h"


Sensor::Sensor()   //constructor sin argumentos
{
	ranStart=ranEnd=min=max=N=0;
	average=0;
	good=bad=false;
	name="";
}
void Sensor::queryTemp(istream *&iss,ostream *&oss,ifstream &dataBaseFile)
{
	 size_t posSen;  // Posicion del sensor en la matriz
	 NetSensor   net;   // Red de sensores
	 net.readDataBase(dataBaseFile);  //leo los datos en una matiz
	 bool  allSensor=false;  //flag que me indica si busco entre todos los sensores
	 while(*iss>>*this)   //operador sobre cargado
	 {
		if(good)  // es correcto el formato de lectura
		{
			good=false;
			if(!name.length())  // si es una consulta sin nombre elijo todos los sensores
			{
				allSensor=true;
				searchAverage(allSensor,net,posSen);  //busco promedio entre todos los sensores
				*oss<<*this;
			}
			else
			{
				for( posSen=0;name!=net.name[posSen] && posSen<net.column ;posSen++);// busco la posición del sensor
				if(posSen==net.column)
					*oss<<"UNKNOW ID"<<endl;
				else
					{
						searchAverage(allSensor,net,posSen);
						*oss<<*this;
					}

			}
		}
		if(bad)  // mala consulta
		{
			*oss<<"BAD QUERY"<<endl;
			bad=false;
		}
	 }
}

void Sensor::searchAverage(bool & allSensor,NetSensor &net,size_t &col) // a mejorar
{
	float acum=0;
	float *allAverage;
	int m;
	size_t i;
	if(allSensor)
	{
		allAverage=new float[net.row];
		for(size_t j=ranStart;j<ranEnd;j++)
		{
			for(i=0,m=0,acum=0;i<net.column;i++)
			{
				if(net.data[j][i]!=-274)   // si no es un dato en blanco
					acum+=net.data[j][i];
				else
					m++;
			};
			allAverage[j]=acum/(i-m);
		}
		getAverage(allAverage);  //calculo el promedio de todos los sensores
		delete []allAverage;
		allSensor=false;
	}
	else     //busco promedio para solo el sensor seleccionado
		getAverage(net.data[col]);
}

void  Sensor::getAverage(float *arrayData)
{
	float w;  //acumulador de la suma de los datos
	size_t i,noData;
	max=min=arrayData[ranStart];  //tomo el primero como el maximo y minimo
	for(i=ranStart,noData=0,w=0;i<ranEnd;i++)
	{
		if(arrayData[i]!=-274)       //-274 representa un dato del sensor en blanco
		{						     // ya que es imposible alcanzar esa temperatura en °C
			if(arrayData[i]>max)
				max=arrayData[i];
			if(arrayData[i]<min)
				min=arrayData[i];
			w+=arrayData[i];
		}
		else
			noData++;				// Si es un dato en blanco, no lo cuento para el promedio
	}
	N=ranEnd-ranStart-noData;
	average=w/N;
}
istream &operator>>(istream &is,Sensor &s)
{
	size_t k,fin;   //l"fin" longitud del string
	char c;
	string str;
	getline(is,str,',');
	fin=str.length();
	for(k=0;k<fin && str[k]==' ';k++);
	if(k==str.length() && str[k-1]== ' ')
		s.name="";
	else
	{
		stringstream str_st(str);
	str_st>>s.name;
	}
	if(is>>s.ranStart && is>>c && c==',' && is>>s.ranEnd)
	{
		s.good=true;	//lectura en formato correcto
		getline(is,str);  // leo hasta el final de linea para saltar a la siguiente

	}
	else		//si es malo elf formato
	{	s.bad=true;
		is.clear();
		getline(is,str,'\n');
	}
	return is;
}
ostream &operator<<(ostream &os,const Sensor &s)
{
	os<<s.average<< " "<<s.min<< " "<<s.max<<" "<<s.N<<endl;
	return os;
}

