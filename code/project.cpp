#include "tempTrender.h"
#include <string>
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMath.h"
#include "TLegend.h"

using namespace std; 
void cityDeviation(tempTrender& lulea, tempTrender& karlstad, tempTrender& boras, tempTrender& falsterbo, tempTrender& falun, tempTrender& lund, tempTrender& soderarm, tempTrender& umea, tempTrender& visby){
	TCanvas * avgTempCanvas = new TCanvas();
	TLegend* legendary = new TLegend(0.6, 0.7, 0.85, 0.9);
	
	lulea.HottestDay();
	karlstad.HottestDay();
	boras.HottestDay();
	falsterbo.HottestDay();
	falun.HottestDay();
	lund.HottestDay();
	soderarm.HottestDay();
	umea.HottestDay();
	visby.HottestDay();
	//https://root-forum.cern.ch/t/tlegend-color-assignments/13379/2
	
	tempTrender *cityPointer = &lulea;
	for (int j = 0; j < 9; j++){
		
		switch(j) {
		
			case(0):
				cityPointer = &lulea;
				break;
			case(1):
				cityPointer = &karlstad;
				break;
			case(2):
				cityPointer = &boras;
				break;
			case(3):
				cityPointer = &falsterbo;
				break;
			case(4):
				cityPointer = &falun;
				break;
			case(5):
				cityPointer = &lund;
				break;
			case(6):
				cityPointer = &soderarm;
				break;
			case(7):
				cityPointer = &umea;
				break;
			case(8):
				cityPointer = &visby;
				break;
				
		}
		
		Double_t x[cityPointer->yearVector.size()];
		Double_t y[cityPointer->yearVector.size()];
		int n = cityPointer->yearVector.size();
		for(int i = 0; i < n; i++){
			x[i] = cityPointer->yearVector.at(i);
			y[i] = cityPointer->hottestTempVector.at(i);
		}
		
		switch(j) {
		
			case(0): {
			   TGraph * luleaGraph = new TGraph(n, x, y);
			   luleaGraph->SetLineColor(7);
			   luleaGraph->SetLineWidth(4);
			   luleaGraph->SetMarkerColor(7);
			   luleaGraph->SetMarkerSize(1);
			   luleaGraph->SetName("Lulea");
			   luleaGraph ->Draw("apl");
			   legendary->AddEntry("luleaGraph","Lulea", "lp");
			   break;
			}
		   
			case(1): {
				TGraph * karlstadGraph = new TGraph(n, x, y);
				karlstadGraph ->SetLineColor(3);
				karlstadGraph ->Draw("pl same");
				break;
			}
			
			case(2): {
				TGraph * borasGraph = new TGraph(n, x, y);
				borasGraph ->SetLineColor(4);
				borasGraph->SetLineWidth(4);
				borasGraph->SetMarkerColor(7);
				borasGraph->SetMarkerSize(1);
				borasGraph->SetName("boras");
				borasGraph ->Draw("pl same");
				legendary->AddEntry("borasGraph","boras", "lp");
				break;
			}
			
			case(3): {
				TGraph * falsterboGraph = new TGraph(n, x, y);
				falsterboGraph ->SetLineColor(5);
				falsterboGraph ->Draw("pl same");
				break;
			}
				
			case(4): {
				TGraph * falunGraph = new TGraph(n, x, y);
				falunGraph ->SetLineColor(6);
				falunGraph ->Draw("pl same");
				break;
			}
			
			case(5): {
				TGraph * lundGraph = new TGraph(n, x, y);
				lundGraph ->SetLineColor(7);
				lundGraph ->Draw("pl same");
				break;
			}
			
			case(6): {
				TGraph * soderarmGraph = new TGraph(n, x, y);
				soderarmGraph ->SetLineColor(28);
				soderarmGraph ->Draw("pl same");
				break;
			}
			
			case(7): {
				TGraph * umeaGraph = new TGraph(n, x, y);
				umeaGraph ->SetLineColor(9);
				umeaGraph ->Draw("pl same");
				break;
			}
			
			case(8): {
				TGraph * visbyGraph = new TGraph(n, x, y);
				visbyGraph ->SetLineColor(12);
				visbyGraph ->Draw("pl same");
				break;
			}
				
		}
		legendary->SetHeader ("City");
		legendary->Draw();   
	   
	}
	

void hotCold(tempTrender& lulea, tempTrender& karlstad, tempTrender& boras, tempTrender& falsterbo, tempTrender& falun, tempTrender& lund, tempTrender& soderarm, tempTrender& umea, tempTrender& visby){
	lund.hotCold();
}

void project(int choice) {

	string dataPathLulea = "../datasets/smhi-opendata_Lulea.csv"; 
	int startingLineLulea = 11;
	string dataPathKarlstad = "../datasets/smhi-opendata_Karlstad.csv";
	int startingLineKarlstad = 12;
	string dataPathBoras = "../datasets/smhi-opendata_Boras.csv";
	int startingLineBoras = 11;
	string dataPathFalsterbo = "../datasets/smhi-opendata_Falsterbo.csv";
	int startingLineFalsterbo = 11;		
	string dataPathFalun = "../datasets/smhi-opendata_Falun.csv";
	int startingLineFalun = 13;				
	string dataPathLund = "../datasets/smhi-opendata_Lund.csv";
	int startingLineLund = 13;
	string dataPathSoderarm = "../datasets/smhi-opendata_Soderarm.csv";
	int startingLineSoderarm = 12;
	string dataPathUmea = "../datasets/smhi-opendata_Umea.csv";
	int startingLineUmea = 13;
	string dataPathVisby = "../datasets/smhi-opendata_Visby.csv"; 
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
	
	switch(choice){
		case 1 : cout << "Lisas arbete" << endl;
				 break;
		case 2 : cout << "Davids arbete" << endl;
				 break;
		case 3 : hotCold(lulea, karlstad, boras, falsterbo, falun, lund, soderarm, umea, visby);
				 break;
		case 4 : cout << "Alexanders arbete" << endl;
	}

	cityDeviation(lulea, karlstad, boras, falsterbo, falun, lund, soderarm, umea, visby);

	lund.hotCold();

}
