#include "tempTrender.h"
#include <string>

using namespace std; 

void project() {
	string iniDataPath = "/home/courseuser/project/datasets/smhi-opendata_Lulea.csv"; //Put the path to your data file here
	int iniStartingLine = 11;
	tempTrender tempy(iniDataPath, iniStartingLine); //Instantiate your analysis object
	tempy.readDataFile();
	//t.tempOnDay(8, 23); //Call some functions that you've implemented
	//t.tempOnDay(235);
	//t.tempPerDay();
	t.hotCold();
	//t.tempPerYear(2050);
	/*
	cout<< tempy.GetYear(0) << endl;
	cout<<tempy.GetMonth(0) << endl;
	cout<<tempy.GetDay(30000)<< endl;
	cout<<tempy.GetHour(11000)<< endl;
	cout << tempy.GetTemperature(1000) << endl;
	*/
	cout << tempy.GetDate(0) << endl;
	cout << tempy.GetDate(1) << endl;
	cout << tempy.GetDate(150) << endl;
}
