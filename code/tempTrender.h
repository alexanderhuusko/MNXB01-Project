#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <fstream>

	
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
		
			/*
			dataFile >> year >> stringDummy >> month >> stringDummy >> day 
			>> stringDummy >> hour >> stringDummy >> intDummy >>
			stringDummy >> intDummy >> stringDummy >> temperatureDummy >> stringDummy;
			*/
			string segment;
			
			while(getline(dataFile, segment))
			{
				vector<string> stringSeparationVector;
				split(segment, stringSeparationVector, ';');
				cout << segment << endl;
				cout << stringSeparationVector.at(0) << endl;
				cout << stringSeparationVector.at(1) << endl;
				cout << stringSeparationVector.at(2) << endl;
				temperature.push_back(stringSeparationVector.at(2));
				
			}
			
			//splitter(dataFile&, vectorYearMonthDayHour&, ";"); 
			//splitter(stringSeparationVector.at(0)&, vectorDummy, "-");
		
		dataFile.close();
	}
	
	//void tempOnDay(int monthToCalculate, int dayToCalculate); //Make a histogram of the temperature on this day
	//void tempOnDay(int dateToCalculate); //Make a histogram of the temperature on this date
	//void tempPerDay(); //Make a histogram of the average temperature of each day of the year
	//void hotCold(); //Make a histogram of the hottest and coldest day of the year
	//void tempPerYear(int yearToExtrapolate); //Make a histogram of average temperature per year, then fit and extrapolate to the given year

	private:
	
	string dataPath;
	string stringDummy;
	int intDummy;
	float temperatureDummy;
	vector<float> temperature; //in celsius
	vector<float> date; //in years
	int year, month, day, hour;
	int maxDataPoints;
	bool keepGoing;
	int startingLine;
	int i;
	vector<string> vectorDummy;
	vector<string> vectorYearMonthDayHour;
	
	
};

#endif
