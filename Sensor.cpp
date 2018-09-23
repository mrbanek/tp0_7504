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


Sensor::Sensor()   //constructor copia
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
	float    *allAverage;
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
		max=min=allAverage[ranStart];  //tomo el primer elemento como el maximo y minimo
		for(i=ranStart,acum=0;i<ranEnd;i++)
		{
			if(allAverage[i]>max)
				max=allAverage[i];
			if(allAverage[i]<min)
				min=allAverage[i];
			acum+=allAverage[i];
		}
		N=ranEnd-ranStart;
		average=acum/N;
		allSensor=false;
	}
	else     //busco promedio para solo un sensor
	{
		max=min=net.data[ranStart][col];  //tomo el primero como el maximo y minimo
		for(i=ranStart,m=0;i<ranEnd;i++)
		{
			if(net.data[i][col]!=-274)
			{
				if(net.data[i][col]>max)
					max=net.data[i][col];
				if(net.data[i][col]<min)
					min=net.data[i][col];
				acum+=net.data[i][col];
			}
			else
				m++;
		}
		average=acum/(i-m-1);
			N=ranEnd-ranStart-m;
	}

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

