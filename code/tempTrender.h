
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
#include "TGraph.h"
#include "TCanvas.h"
#include "TH1.h"

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
      //int mycounter = 1;   
      if (((year.at(p) % 4 == 0) && (year.at(p) % 100 != 0)) || (year.at(p) % 400 == 0) ){
	//cout<< "I do not want this shit year to many days! \n";
	leap_year_counter ++;
	p++;
      }
      
      else{
	//while (year.at(p) == year.at(p+1)){
	//cout<< day.at(p)<< endl;
	
	if(day.at(p) == day.at(p+1)){
	  do{
	    tempday += temperature.at(p);
	    mycounter++;
	    //cout<<"c2 " <<mycounter<< endl;
	    p++;
	  }while(day.at(p) == day.at(p+1));
	  
	  
	  
	}
	else{
	  tempday += temperature.at(p);
	  mycounter +=1;
	  tempavg = tempday /mycounter;
	  //cout<<" c1 "<<mycounter<<endl;
	  //cout<<"day = "<< day.at(p)<< endl;
	  if(tempavg >40){
	    cout << "avg temp = "<<tempavg<< endl;
	    cout << mycounter<< endl;
	    
	    cout<<year.at(p)<<" , "<< month.at(p)<< " , "<< day.at(p)<< endl;
	  }
	  mycounter = 0;
	  tempday = 0;
	  temp_avg.push_back(tempavg);
	  //cout<< mycounter << endl;
	  //cout<< temperature.at(p)<< endl;
	  //cout<<year.at(p)<< endl;
	  p++;
	}
	
      }
    }
    
    int k=0;
    int l;
    
    for ( l = year.front(); l <= (year.back()-15); l++){
      for (int j = 0; j < 365; j++){
	temp_every_day[j] += temp_avg.at(k);
	
	//if(temp_every_day[j] > 700){
	//cout<< temp_every_day[j]<<endl;
	k++;
      }  
    }
    
    for(int j = 0; j<365; j++){
      temp_avg_all_days[j] = temp_every_day[j]/38;
      //cout<<temp_avg_all_days[j]<< endl;
      days[j]=j;
    }
    
    cout<<temp_avg_all_days[364]<<endl;

    TH1F h("h","example histogram",365,0.,365)
    /* TGraph *gr  = new TGraph(365,days,temp_avg_all_days);
    TCanvas *c1 = new TCanvas("c1","Graph Draw Options",200,10,600,400);
    gr->GetStdDev();
    gr->Draw();*/

    

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
  vector<float> temp_avg;
  float temp_avg_all_days[365] = {};
  float temp_every_day [365] = {};
  float days [365] = {};
  int startingLine;
  int i;
  int k = 0;
  int p = 0;
  int mycounter= 0;
  int l = 0;
  double tempday;
  double tempavg;
  int leap_year_counter;
  //void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
  //void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
  
  //void hotCold(); //Make a histogram of the hottest and coldest day of the year
  //void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year

};

#endif
