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
	ranStart=ranEnd=min=max=average=N=0;
	good=bad=false;
	name="";
}
void Sensor::queryTemp(istream *&iss,ostream *&oss,ifstream &dataBaseFile)
{
	 Sensor s;
	 NetSensor   net;   // Red de sensores
	 net.readDataBase(dataBaseFile);  //leo los datos en una matiz
	 bool  allSensor=false;
	 size_t   npos;
	 string firstLine;          //primer linea de la base de datos que tiene los sesnores
	 getline(dataBaseFile,firstLine);
	 while(*iss>>s)
	 {
		 if(s.good)
		 {
			 npos=firstLine.find(s.name);
			 if(npos>firstLine.length())  //si no encuentro el sensor
				 *oss<<"UNKNOWN "<<endl;
			 else
			 {
				 if(s.name.length())
				 {
					 allSensor=true;
					 searchAverage(allSensor,s);
				 }
				 else
					 searchAverage(allSensor,s);

			 }
		 }
		 if(s.bad)
			 *oss<<"BAD QUERY"<<endl;


	 }



}
void Sensor::searchAverage(bool & allSensor,Sensor &s)
{
	if(allSensor)
	{
		std::cout<<"Todos los sensores"<<endl;
		allSensor=false;
	}
	else
		std::cout<<"Solo un sensor"<<endl;
}
istream &operator>>(istream &is,Sensor &s)
{
	char c;
	string str;
	getline(is,str,',');
	stringstream str_st(str);
	str_st>>s.name;
	if(is>>s.ranStart && is>>c && c==',' && is>>s.ranEnd)
		s.good=true;
	else
		s.bad=true;
	return is;
}

