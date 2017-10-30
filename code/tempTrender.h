#ifndef TEMPTRENDER_H
#define TEMPTRENDER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std; 

class tempTrender {
	public:
	tempTrender(string iniDataPath, bool iniKeepGoing, int iniStartingLine, int iniMaxDataPoints); //Construct using the specified file
	~tempTrender() {} //Destructor
	
	void readDataFile(){
		ifstream dataFile(dataPath.c_str());
		
		for(int j = 1; j < startingLine; j++){
			getline(dataFile, stringDummy);
			//dataFile.ignore(1000, "\n");
		}
		
		while(i < maxDataPoints && keepGoing){
			/*
			dataFile >> year >> stringDummy >> month >> stringDummy >> day 
			>> stringDummy >> hour >> stringDummy >> intDummy >>
			stringDummy >> intDummy >> stringDummy >> temperatureDummy >> stringDummy;
			*/
			string segment;
			vector<string> stringSeparationVector;

			while(getline(dataFile, segment, ';'))
			{
			   stringSeparationVector.push_back(segment);
			}
			getline(dataFile, stringDummy);
			temperature.push_back(temperatureDummy);
			cout << stringSeparationVector.at(0) << endl;
			i++;
		}
		
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
};

#endif
