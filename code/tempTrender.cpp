#include <iostream>
#include "tempTrender.h"

tempTrender::tempTrender(string iniDataPath, bool iniKeepGoing, int iniStartingLine, int iniMaxDataPoints) {
	dataPath = iniDataPath;
	keepGoing = iniKeepGoing;
	startingLine = iniStartingLine;
	maxDataPoints = iniMaxDataPoints;
	i = 0;
	
	
	
	/*
	cout << "The user supplied " << filePath << " as the path to the data file." << endl;
	cout << "You should probably store this information in a member variable of the class. Good luck with the project! :)" << endl;
	*/
}
