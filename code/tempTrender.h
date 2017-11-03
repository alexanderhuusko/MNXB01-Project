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

#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h>  // style object
#include <TMath.h>   // math functions
#include <TCanvas.h> // canvas object
	
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
		//printf("%f\n", tempDate);

		return tempDate;
	}
	
	int convertMonthToDays(int l) {
		int monthDaysNormal[13] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
		int monthDaysLeap[13] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };
		
		if((year.at(k) % 4 == 0) && (year.at(k) % 100 != 0)){
			daysMonth = monthDaysLeap[l];
		}
		else if(year.at(k) % 100 == 0){
			daysMonth = monthDaysNormal[l];
		}
		else if(year.at(k) % 400 == 0){
			daysMonth = monthDaysLeap[l];
		}
		else{
			daysMonth = monthDaysNormal[l];
		}
		return daysMonth;
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
	
	int GetYear(int dataPoint){return year.at(dataPoint);}
	int GetMonth(int dataPoint){return month.at(dataPoint);}
	int GetDay(int dataPoint){return day.at(dataPoint);}
	int GetHour(int dataPoint){return hour.at(dataPoint);}
	float GetTemperature(int dataPoint){return temperature.at(dataPoint);}
	double GetDate(int dataPoint){return decimalYear.at(dataPoint);}
	
	void hotCold() {
		int currentYear = year.at(0);
		float coldest = 100;
		float hottest = 0;
		
		TH1D* hotHist = new TH1D("Hot", "Histogram of hottest days over all years; day; Counts", 
			366, 0, 366);
		TH1D* coldHist = new TH1D("Cold", "Histogram of coldest days over all years; day; Counts", 
			366, 0, 366);
		//TH1D* hotColdHist = new TH1D("hotCold", "Histogram of hottest and coldest days over all years; day; Counts", 
		//	366, 0, 366);
		
		for (k = 0; (unsigned)k < (year.size() -1); k++) {
			if (temperature.at(k) > hottest){
				hottest = temperature.at(k);
				hottestDay = day.at(k);
				hottestMonth = month.at(k);
			}
			
			if (temperature.at(k) < coldest){
				coldest = temperature.at(k);
				coldestDay = day.at(k);
				coldestMonth = month.at(k);
			}
			
			if (currentYear != year.at(k+1)){
				currentYear = year.at(k+1);
				hotDays.push_back(convertMonthToDays(hottestMonth) + hottestDay);
				coldDays.push_back(convertMonthToDays(coldestMonth) + coldestDay);
				coldest = 100;
				hottest = 0;
			}
		}
		
		for (int j = 0; (unsigned)j < hotDays.size(); j++) {
			hotHist->Fill(hotDays.at(j));
			coldHist->Fill(coldDays.at(j));
		}
		TCanvas* hc = new TCanvas("hc", "Hot cold canvas", 900, 600); // Create canvas for plot
		
		hotHist->SetLineColor(2);
		hotHist->SetFillColor(2);
		hotHist->Draw(); // Draw the histogram containing hot days
		
		coldHist->SetLineColor(4);
		coldHist->SetFillColor(4);
		coldHist->Draw("SAME"); //Draw the histogram containing cold days in the same canvas as hot days
		gPad->RedrawAxis(); // Redraw axis because it became same color as coldHist

	}

		
	
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
	int startingLine;
	int i;
	int k;
	int hottestDay;
	int hottestMonth;
	int coldestDay;
	int coldestMonth;
	vector<int> hotDays;
	vector<int> coldDays;
	int daysMonth;
	
	
	//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	//void tempPerDay(); //Make a histogram of the average temperature of each day of the year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year

};

#endif
