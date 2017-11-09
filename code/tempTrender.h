
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
#include "TGraphErrors.h"
#include "TAxis.h"
//#include "TH1.h"

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
  
  //Make a histogram of the average temperature of each day of the year
  void tempPerDay(){ 
    
    for (p=0;(unsigned)p < year.size()-1;){
      //Ignoring the leap years  
      if (((year.at(p) % 4 == 0) && (year.at(p) % 100 != 0)) || (year.at(p) % 400 == 0) ){
	p++;
      }
      
      else{
	//sum up the temperatures if it is the same day.
	if(day.at(p) == day.at(p+1)){
	  do{
	    tempday += temperature.at(p);
	    mycounter++;
	    p++;
	  }while(day.at(p) == day.at(p+1));
	  
	}
	else{
	  // The last day will not be included in the statement above thus add the last measurement
	  // to the vector. The temp for the day is also calculated here.
	  tempday += temperature.at(p);
	  mycounter +=1;
	  tempavg = tempday /mycounter;
	  
	  mycounter = 0;
	  tempday = 0;
	  temp_avg.push_back(tempavg);
	  
	  p++;
	}
      }
    }
    
    
    //counting how many years are leap years
    for ( l = year.front(); l <= (year.back()); l++){
      if (((l % 4 == 0) && (l % 100 != 0)) || (l % 400 == 0) ){
	leap_year_counter ++;
      }
    }
    
    // looping ove all years and all days of a year and add the same of the diffent year togther.
    for ( l = year.front(); l <= (year.back()-leap_year_counter); l++){
      for (int j = 0; j < 365; j++){
	temp_every_day[j] += temp_avg.at(k);
	k++;
      }  
      Nr_year++;
    }
    
    //Taking the avarage of all the temperatures
    for(int j = 0; j<365; j++){
      temp_avg_all_days[j] = temp_every_day[j]/Nr_year;
      days[j]=j;
    }
    
    // Doing the standard deviation calculation based on the formula.
    for ( m = 0; m < 365; m++){
      for (t = m; t< temp_avg.size(); t += 365){
	std[m] +=pow( temp_avg[t]- temp_avg_all_days[m], 2)/Nr_year;
	}
      std[m]=sqrt(std[m]);
    }
    
    // Drawing the graph.
    TGraph *gr  = new TGraphErrors(365,days,temp_avg_all_days, 0 ,std);
    
    gr->SetTitle("Avarage temperature all days and years");
    gr->GetYaxis()->SetTitle("Temperature [C]");
    gr->GetXaxis()->SetTitle("Days");
    
    TCanvas *c1 = new TCanvas("c1","Avarage temperature all days and years",200,10,800,365);
    gr->Draw();
    
    
    
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
  vector <float> temporary_vector;
  float temp_avg_all_days[365] = {};
  float temp_every_day [365] = {};
  float days [365] = {};
  float std [365] = {};
  int startingLine;
  int i;
  int k = 0;
  int p = 0;
  int mycounter= 0;
  int l = 0;
  double tempday;
  double tempavg;
  int leap_year_counter = 1;
  int Nr_year = 0;
  int m;
  int t;
  
  //void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
  //void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
  
  //void hotCold(); //Make a histogram of the hottest and coldest day of the year
  //void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year

};

#endif
