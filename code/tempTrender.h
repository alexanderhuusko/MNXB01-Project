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
	
using namespace std; 

class tempTrender {
	public:
	tempTrender(string iniDataPath, bool iniKeepGoing, int iniStartingLine, int iniMaxDataPoints); //Construct using the specified file
	~tempTrender() {} //Destructor
		
		
	void split(string stringToSplit, vector<string>& container, char delimiter){
		stringstream sts(stringToSplit);
		string token;
		while (getline(sts, token, delimiter)){
			container.push_back(token);
		}

	}
	
	void readDataFile(){
		ifstream dataFile(dataPath.c_str());
		
		for(int j = 1; j < startingLine; j++){
			getline(dataFile, stringDummy);
			//dataFile.ignore(1000, "\n");
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
				//cout << stringSeparationVector.at(2).c_str() << endl;
				
				//Splits the time hh:mm:ss into hh only vector (no minutes and seconds are recorded in files)
				split(stringSeparationVector.at(1), hourDummy,'-');
				hour.push_back(strtof(hourDummy.at(0).c_str(), 0));

				//Writes the temperature into the vector
				temperature.push_back(strtod(stringSeparationVector.at(2).c_str(), 0));
			}
		
		dataFile.close();
	}
	
	int GetYear(int dataPoint){return year.at(dataPoint);}
	int GetMonth(int dataPoint){return month.at(dataPoint);}
	int GetDay(int dataPoint){return day.at(dataPoint);}
	int GetHour(int dataPoint){return hour.at(dataPoint);}
	float GetTemperature(int dataPoint){return temperature.at(dataPoint);}
	
	private:
	
	string dataPath;
	string stringDummy;
	int intDummy;
	float temperatureDummy;
	vector<float> temperature; //in celsius
	vector<float> date; //in years
	vector<int> year;
	vector<int> month;
	vector<int> day;
	vector<int> hour;
	int maxDataPoints;
	bool keepGoing;
	int startingLine;
	int i;
	vector<string> vectorDummy;
	vector<string> vectorYearMonthDayHour;
	
	//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	//void tempPerDay(); //Make a histogram of the average temperature of each day of the year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year

};

#endif
