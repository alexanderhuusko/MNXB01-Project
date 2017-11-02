#include "tempTrender.h"
#include <string>

using namespace std; 

void project() {
	string dataPathLulea = "/home/courseuser/project/datasets/smhi-opendata_Lulea.csv"; 
	int startingLineLulea = 11;
	string dataPathKarlstad = "/home/courseuser/project/datasets/smhi-opendata_Karlstad.csv";
	int startingLineKarlstad = 12;
	string dataPathBoras = "/home/courseuser/project/datasets/smhi-opendata_Boras.csv";
	int startingLineBoras = 11;
	string dataPathFalsterbo = "/home/courseuser/project/datasets/smhi-opendata_Falsterbo.csv";
	int startingLineFalsterbo = 11;		
	string dataPathFalun = "/home/courseuser/project/datasets/smhi-opendata_Falun.csv";
	int startingLineFalun = 13;				
	string dataPathLund = "/home/courseuser/project/datasets/smhi-opendata_Lund.csv";
	int startingLineLund = 13;
	string dataPathSoderarm = "/home/courseuser/project/datasets/smhi-opendata_Soderarm.csv";
	int startingLineSoderarm = 12;
	string dataPathUmea = "/home/courseuser/project/datasets/smhi-opendata_Umea.csv";
	int startingLineUmea = 13;
	string dataPathVisby = "/home/courseuser/project/datasets/smhi-opendata_Visby.csv"; 
	int startingLineVisby = 11;
	
	tempTrender lulea(dataPathLulea, startingLineLulea);
	lulea.readDataFile();
	
	tempTrender karlstad(dataPathKarlstad, startingLineKarlstad);
	karlstad.readDataFile();

	tempTrender boras(dataPathBoras, startingLineBoras);
	boras.readDataFile();
		
	tempTrender falsterbo(dataPathFalsterbo, startingLineFalsterbo);
	falsterbo.readDataFile();
			
	tempTrender falun(dataPathFalun, startingLineFalun);
	falun.readDataFile();
	
	tempTrender lund(dataPathLund, startingLineLund);
	lund.readDataFile();
	
	tempTrender soderarm(dataPathSoderarm, startingLineSoderarm);
	soderarm.readDataFile();
		
	tempTrender umea(dataPathUmea, startingLineUmea);
	umea.readDataFile();
	
	tempTrender visby(dataPathVisby, startingLineVisby);
	visby.readDataFile();
	
	cout << lulea.GetYear(0) << endl;
	cout << lulea.GetMonth(0) << endl;
	cout << lulea.GetDay(30000)<< endl;
	cout << lulea.GetHour(11000)<< endl;
	cout << umea.GetTemperature(1000) << endl;
	cout << visby.GetDate(150) << endl;
	
	cout << karlstad.GetYear(0) << endl;
	cout << boras.GetMonth(0) << endl;
	cout << falsterbo.GetDay(30000)<< endl;
	cout << falun.GetHour(11000)<< endl;
	cout << lund.GetTemperature(1000) << endl;
	cout << soderarm.GetDate(150) << endl;
}
