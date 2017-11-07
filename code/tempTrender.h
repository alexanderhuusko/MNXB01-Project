#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>

using namespace std; 

class tempTrender {
 public:
  tempTrender(string iniDataPath, int iniStartingLine); //Construct using the specified file
  ~tempTrender() {} //Destructor
  
  
  void split(string stringToSplit, vector<string>& container, char delimiter){
    stringstream sts(stringToSplit);
    string token;
    while (getline(sts, token, delimiter)){
      container.push_back(token);
    }
    
  }
  double convertDateToYear(int i){
    double tempDate = 0.0;
    double normalYear = 365.0000000000; //days
    double leapYear = 366.0000000000; //days
    double hourToDay = 24.0;
    if((year.at(i) % 4 == 0) && (year.at(i) % 100 != 0)){
      tempDate = hour.at(i) / (hourToDay * leapYear) + day.at(i)/leapYear + month.at(i)/12 + year.at(i);
    }
    else if(year.at(i) % 100 == 0){
      tempDate = hour.at(i)/ (hourToDay * normalYear) + day.at(i)/normalYear + month.at(i)/12 + year.at(i);
    }
    else if(year.at(i) % 400 == 0){
      tempDate = hour.at(i) / (hourToDay * leapYear) + day.at(i)/leapYear + month.at(i)/12 + year.at(i);
    }
    else{
      tempDate = hour.at(i) / (hourToDay * normalYear) + day.at(i)/normalYear + month.at(i)/12 + year.at(i);
    }
    return tempDate;
  }
  void readDataFile(){
    ifstream dataFile(dataPath.c_str());
    
    for(int j = 1; j < startingLine; j++){
      getline(dataFile, stringDummy);
    }
    string segment;
    
    while(getline(dataFile, segment))
      {
	vector<string> stringSeparationVector;
	vector<string> dateDummy;
	vector<string> hourDummy;
	split(segment, stringSeparationVector, ';');
	
	//Splits the date yyyy-mm-dd into three vectors (year, month, day) with yyyy, mm, dd
	split(stringSeparationVector.at(0), dateDummy,'-');
	year.push_back(strtof(dateDummy.at(0).c_str(), 0));
	month.push_back(strtof(dateDummy.at(1).c_str(), 0));
	day.push_back(strtof(dateDummy.at(2).c_str(), 0));
	
	//Splits the time hh:mm:ss into hh only vector (no minutes and seconds are recorded in files)
	split(stringSeparationVector.at(1), hourDummy,'-');
	hour.push_back(strtof(hourDummy.at(0).c_str(), 0));
	
	//Writes the temperature into the vector
	temperature.push_back(strtod(stringSeparationVector.at(2).c_str(), 0));
	
	//Creates year in decimal and stores in a vector
	decimalYear.push_back(convertDateToYear(i));
	i++;
      }
    
    dataFile.close();
  }
  
  
  void tempPerDay(){ //Make a histogram of the average temperature of each day of the year
    
    for (p=0;(unsigned)p < year.size()-1;){
      //int l = 0;
      if (((year.at(p) % 4 == 0) && (year.at(p) % 100 != 0)) || (year.at(p) % 400 == 0) ){
	cout<< "I do not want this shit year to many days! \n";
	p++;
      }
      
      else{
	//while (year.at(p) == year.at(p+1)){
	//cout<< day.at(p)<< endl;
	  mycounter = 1;
	  if(day.at(p) == day.at(p+1)){
	    do{
	      tempday += temperature.at(p);
	      // cout<<mycounter<< endl;
	    mycounter++;
	    p++;
	    }while(day.at(p) == day.at(p+1));
	    
	  
	  
	  }
	  else{
	    tempday += temperature.at(p);
	    mycounter++;
	    tempavg = tempday /mycounter;
	    cout<<"day = "<< day.at(p)<< endl;
	    cout << "avg temp = "<<tempavg<< endl;
	    tempday = 0;
	    //cout<< mycounter << endl;
	    //cout<< temperature.at(p)<< endl;
	    //cout<<year.at(p)<< endl;
	    p++;
	  }
	  //if (day.at(p) == day.at(p+1)){
	  //  cout<< temperature.at(p)<<", " <<temperature.at(p+1)<<endl;

	  //}
	    
	  //}
	//p++;
      }
    }
  }
  
  
  
  
    
  int GetYear(int dataPoint){return year.at(dataPoint);}
  int GetMonth(int dataPoint){return month.at(dataPoint);}
  int GetDay(int dataPoint){return day.at(dataPoint);}
  int GetHour(int dataPoint){return hour.at(dataPoint);}
  float GetTemperature(int dataPoint){return temperature.at(dataPoint);}
  double GetDate(int dataPoint){return decimalYear.at(dataPoint);}
  
 private:
  
  string dataPath;
  string stringDummy;
  int intDummy;
  float temperatureDummy;
  vector<float> temperature; //in celsius
  vector<double> decimalYear;
  vector<int> year;
  vector<int> month;
  vector<int> day;
  vector<int> hour;
  vector<float>sum_of_temp;
  int startingLine;
  int i;
  int k = 0;
  int p = 0;
  int mycounter= 0;
  int l = 0;
  double tempday;
  double tempavg;
//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date

//void hotCold(); //Make a histogram of the hottest and coldest day of the year
//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year

};

#endif
