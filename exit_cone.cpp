#include "./profilV_2.h"

Double_t loadDensity(TString filename = "")
{
	gRandom = new TRandom(time(0));


	if (filename == "")	return -1;
	else
	{
		std::ifstream dataFile (filename);	
		if (dataFile)
		{
			std::string line ;
			bool read = false;
			while (std::getline(dataFile,line)) 
			{
				line = replaceCommasWithDots(line);
				if (line.substr(1,6) == "Target") return stod(line.substr(19,10));
			}
		}
	}
	return 0;
}

std::array<std::vector<Double_t>,2> loadData (std::string file = "")
{
	std::vector<Double_t> Energy, Range;

	std::ifstream dataFile (file);	
	if (dataFile)
	{
		std::string line ;
		bool read = false;
		while (std::getline(dataFile,line)) 
		{
			if (line.substr(0,1) == "-") read = false;//tags the end of the data
			if (read)	
			{
				line = replaceCommasWithDots(line);
				Energy.push_back(stod(line.substr(0,7))*findUnit(line.substr(8,3)));
				Range.push_back(stod(line.substr(37,5))*findUnit(line.substr(43,2)));
			}
			if (line.substr(0,3) == "  -") read = true;//tags the begginning of the data
		}
	}
	else {printStr("File not found !!");}

	std::array<std::vector<Double_t>,2> ret = {Energy,Range};
	return ret;
}

void exit_cone()
{

	std::string fileName = "92Sr_in_UO3.txt";

	Double_t density = loadDensity(fileName);

	Double_t energy_FF = 110*MeV;

	std::array<std::vector<Double_t>,2> rangeData = loadData(fileName);

	//! converting the vectors into arrays : 
	Double_t *Energy = &(rangeData[0][0]);
	Double_t *Range = &(rangeData[1][0]);
	Int_t nb_Range_data = rangeData[0].size();

	if ((bool) nb_Range_data)
	{
		TSpline5 *rangeSpline5  = new TSpline5("Data_Spline",Energy,Range,nb_Range_data);// Range = f(Energy)
		TSpline5 *energySpline  = new TSpline5("Data_Spline2",Range,Energy,nb_Range_data);// Energy = f(Range)

		double range = rangeSpline5 -> Eval(energy_FF);

		std::cout << "range : " << range/µm << " µm" << std::endl;

		Double_t thickness = 40*µm;

		TH2D *h = new TH2D("exit_cone","exit_cone",500,0,thickness/µm,180,0,180);

		//TH1D *h1 = new TH1D("angle","angle",100, 0,3.1415);
		TH1D *h1 = new TH1D("angle","angle",100, -1,1);

		Int_t nbShoots = 1e7;

		for (Int_t i = 0; i<nbShoots; i++)
		{
			Double_t creationDeep = gRandom -> Uniform(0,1)*thickness;

			Double_t angle = gRandom -> Uniform(0,1)*PI;

			//h1 -> Fill(angle);

			Double_t path = creationDeep/cos(angle);

			if (abs(path)>range)
			{
				h -> Fill(creationDeep/µm,angle*180/PI);
				//h -> Fill(cos(angle),angle*180/PI);
				//h1 -> Fill(angle);
			}
		}

		TCanvas *c1 = new TCanvas("cone","cone");
		h -> Draw("colz");
		h -> SetTitle("Exit cone;creationDeep(#mum);Angle(#circ);Number");
		gStyle -> SetOptStat(0);
		gPad -> SetLogz(true);

		// TCanvas *c2 = new TCanvas("angle","angle");
		// h1 -> SetTitle("Angle;Number;Angle");
		// gStyle -> SetOptStat(0);
		// gPad -> SetLogy(true);
		// h1 -> Draw("pl");

	} 
	else {printStr("Pas de données lues");}
}