/*
	profilV(): profil de vitesse des fragments de fission, et autres calculs intermédiaires
	Cible fine cylindrique
	Nécessite donnees SRIM
	Auteur : Corentin Hiver
*/
#include "./profilV_2.h"
#include <fstream>

static double rayonTarget = 1*cm;

static double massFF = 150*amu;
static double light_massFF = 85*amu;

static double energy_FF = 65*MeV;
static double light_energy_FF = 110*MeV;

void profilV_2()
{
	std::string fileName = "150Ce_in_UO3.txt";
	std::string lightFileName = "92Sr_in_UO3.txt";

	Double_t density = loadDensity(fileName);
	Double_t lightDensity = loadDensity(lightFileName);

	gRandom = new TRandom(time(0));

	//const char *name = "Raw_energy_profile";
	//const char *name = "Raw_speed_profile";
	//const char *name = "Range_and_Spline";
	//const char *name = "Energy_profile_8um";
	//const char *name = "Energy_profiles";
	//const char *name = "Speed_profiles";
	//const char *name = "Range_left_profile";
	//const char *name = "Range_left_profile_85Se";
	const char *name = "Stopped_Yield_2_fragments";

	auto c1 = new TCanvas(name,name);

	std::array<std::vector<Double_t>,2> rangeData = loadData(fileName);
	std::array<std::vector<Double_t>,2> lightRangeData = loadData(lightFileName);

	//! converting the vectors into arrays : 
	Double_t *Energy = &(rangeData[0][0]);
	Double_t *Range = &(rangeData[1][0]);
	Int_t nb_Range_data = rangeData[0].size();

	Double_t *lightEnergy = &(lightRangeData[0][0]);
	Double_t *lightRange = &(lightRangeData[1][0]);
	Int_t light_Nb_Range_data = lightRangeData[0].size();

	// TGraph *gr2 = new TGraph (light_Nb_Range_data,lightEnergy,lightRange);
	// gr2 -> Draw("ap");
	// gr2 -> SetMarkerColor(kGreen);
	// gr2 -> SetMarkerStyle(kMultiply);
	// gr2 -> GetXaxis() -> SetTitle("MeV");
	// gr2 -> GetYaxis() -> SetTitle("Range (m)");

	// TGraph *gr = new TGraph (nb_Range_data,Energy,Range);
	// gr -> SetMarkerColor(kBlue);
	// gr -> SetMarkerStyle(kPlus);
	// gr -> GetYaxis() -> SetTitleSize(0.008);
	// gr -> GetXaxis() -> SetTitle("MeV");
	// gr -> GetYaxis() -> SetTitle("Range (m)");
	// gr -> GetXaxis() -> SetTitleSize(0.008);
	// gr -> GetXaxis() -> SetTitleOffset(1.2);
	// gr -> SetTitle(name);	
	// gr -> Draw("p same");

	TSpline5 *rangeSpline5  = new TSpline5("Data_Spline",Energy,Range,nb_Range_data);// Range = f(Energy)
	//TSpline5 *energySpline  = new TSpline5("Data_Spline2",Range,Energy,nb_Range_data);// Energy = f(Range)
	TSpline3 *energySpline  = new TSpline3("Data_Spline2",Range,Energy,nb_Range_data);// Energy = f(Range)

	TSpline5 *lightRangeSpline5  = new TSpline5("Data_Spline_light",lightEnergy,lightRange,light_Nb_Range_data);// Range = f(Energy)
	TSpline5 *lightEnergySpline  = new TSpline5("Data_Spline2_light",lightRange,lightEnergy,light_Nb_Range_data);// Energy = f(Range)

	// rangeSpline5 -> Draw("same");
	// rangeSpline5 -> SetLineColor(kGreen);
	// rangeSpline5 -> SetLineWidth(1); 


	// gPad -> SetLogx();
	// gPad -> SetLogy();

	// auto *legend123 = new TLegend(0.25,0.6,0.45,0.9);
	// legend123 -> AddEntry(gr,"Heavy fragment {}^{150}Ce");
	// legend123 -> AddEntry(gr2,"Light fragment {}^{92}Sr");
	// legend123 -> Draw();
	


	//! Determines the range of the FF at the given energy :
	double range = rangeSpline5 -> Eval(energy_FF);
	double light_range = lightRangeSpline5 -> Eval(light_energy_FF);
	//printD(range);printD(light_range);

	/*! Calcule le nombre de fragments lourds arrêtés pour différentes épaisseurs de cible :

	
	std::vector<Double_t> epaisseurs ;
	double min = 0.01; double max = 40; double step=0.5;
	for (int i = 0; i< 1+(max-min)/step;i++) epaisseurs.push_back(min+i*step);

	Double_t stopped[epaisseurs.size()];	Double_t thickness[epaisseurs.size()];

	Double_t stoppedLFF[epaisseurs.size()];	Double_t thicknessLFF[epaisseurs.size()];

	int i = 0;
	int nbShoots = 1e6;		
	for (Double_t &dx : epaisseurs)
	{
		double thicknessTarget = dx*µm;
		int nbStopped = nbFFstopped(range, thicknessTarget, nbShoots);
		int nbStoppedLight = nbFFstopped(light_range, thicknessTarget, nbShoots);

		std::cout << "thickness : " << dx*0.1*density << " mg/cm^{3} --> dx = " << dx << " µm ---> " << 100.*nbStopped/nbShoots << "%" << " arretes" << std::endl;
		std::cout << "thickness : " << dx*0.1*density << " mg/cm3 --> dx = " << dx << " µm ---> " << 100.*nbStoppedLight/nbShoots << "%" << " arretes" << std::endl;
		
		stopped[i] = 100.*nbStopped/nbShoots;
		thickness[i] = dx*0.1*density;

		stoppedLFF[i] = 100.*nbStoppedLight/nbShoots;
		thicknessLFF[i] = dx*0.1*density;
		i++;
	}
	
	auto *legend0 = new TLegend(0.25,0.6,0.45,0.9);

	TGraph *graph = new TGraph(epaisseurs.size(),thickness,stopped);
	graph -> SetTitle("#splitline{Fraction of {}^{92}Se at 110 MeV and {}^{150}Ce at 60 MeV}{stopped in target}"); 
	graph -> SetMarkerStyle(20);
	graph -> GetYaxis() -> SetTitle("Fragments arretes dans la cible [%]");
	graph -> GetXaxis() -> SetTitle("Epaisseur [mg/cm^{3}]");
	graph -> GetYaxis() -> SetRangeUser(0,100);
	graph -> Draw("apc");
	legend0 -> AddEntry(graph,"Heavy fragment {}^{150}Ce");
	
	TGraph *graph2 = new TGraph(epaisseurs.size(),thicknessLFF,stoppedLFF);
	graph2 -> SetMarkerStyle(23);
	graph2 -> GetYaxis() -> SetTitle("Fragments arretes dans la cible %");
	graph2 -> GetXaxis() -> SetTitle("Epaisseur mg/cm^{3}");
	graph2 -> GetYaxis() -> SetRangeUser(0,100);
	graph2 -> Draw("SAME PC");	

	legend0 -> AddEntry(graph2,"Light fragment {}^{92}Sr");
	legend0 -> Draw();
	//*/


//*! Determines the speed/rangeLeft profile :

	std::vector<Double_t> epaisseurs ;
	double min = 1; double max = 20; double step=1;
	for (int i = 0; i< 1+(max-min)/step;i++) epaisseurs.push_back(min+i*step);

	auto *legend = new TLegend(0.25,0.6,0.45,0.9,"Thickness");

	TH1D **h = new TH1D*[epaisseurs.size()];

	std::vector<Double_t> thck,integral; 
	Double_t borneMax = 0.4 ; //In the X axis unit

	int itr = 0;

	std::vector<Int_t> nbStopped;

	for(Double_t &thicknessTarget : epaisseurs)
	{
		TString histoName = DoubleToTString (thicknessTarget*0.1*density, 2, "", " mg.cm^{-2}");

		Int_t nb_pts = 1000; Double_t borne_min = 0.; Double_t borne_max = 2.;

		h[itr] = new TH1D(histoName, "", nb_pts, borne_min, borne_max);

		int nbShoots = 1e6;
		std::cout << "Calculs pour " << thicknessTarget << "um" << std::endl;
		Int_t nb_stopped = 0;
		for (int i = 0; i<nbShoots; i++) 
		{
			double path = shootPath(thicknessTarget*µm);
			double rangeLeft = (range-path);
			if (rangeLeft < 0) {rangeLeft = 0.;nb_stopped++;}
			else
			{	
				//h[itr] -> Fill(path/µm);			
				//h[itr] -> Fill(energySpline -> Eval(rangeLeft)); // en MeV, fonctionne
				//h[itr] -> Fill(energySpline -> FindX(rangeLeft));

				//printD(energySpline -> Eval(10*µm));
				//printD(rangeLeft/µm);

				Double_t energy = energySpline -> Eval(rangeLeft)/J; // en Joule

				h[itr] -> Fill(sqrt(2*(energy)/massFF) * (ns/cm) ); //en cm/ns, fonctionne

				//h[itr] -> Fill(rangeLeft/µm);
			}
		}	
		h[itr] -> Scale(100./h[itr] -> Integral());
		h[itr] -> Draw("same hist");
		h[itr] -> SetLineColor(itr+1);
		legend -> AddEntry(h[itr],histoName);
		//std::cout << h[itr] -> GetMean() << std::endl;
		//h -> GetXaxis() -> SetTitle("um");
		//h[itr] -> GetXaxis() -> SetTitle("MeV");
		h[itr] -> GetXaxis() -> SetTitle("cm/ns");
		//h[itr] -> GetXaxis() -> SetTitle("#mum");
		h[itr] -> GetYaxis() -> SetTitle("[%]");
		h[itr] -> SetTitle(name);

		thck.push_back(thicknessTarget);
		//integral.push_back((double)(nb_stopped)/nbShoots);//only stopped nuclei
		//integral.push_back((double)((h[itr] -> Integral(0.,borneMax * nb_pts / (borne_max - borne_min)))/nbShoots));//not including stopped nuclei
		integral.push_back((double)((h[itr] -> Integral(0.,borneMax * nb_pts / (borne_max - borne_min))+nb_stopped)/nbShoots));//including stopped nuclei

		itr++;
	}
	legend -> Draw();
	gPad -> SetTitle(name);
	gPad -> SetLogy(false);
	gPad -> SetLogx(false);
	gStyle->SetOptStat(0);

	//*/

	/*
	Double_t *thck_array = &thck[0];
	Double_t *integral_array = &integral[0];
	TGraph *graph = new TGraph(thck.size(),thck_array,integral_array);
	//TString titleGraphIntegral = "Yield of fragments below " + boost::lexical_cast<std::string>(borneMax) + "MeV";
	TString titleGraphIntegral = "Yield of fragments stopped";
	graph -> SetTitle(titleGraphIntegral); 
	graph -> SetMarkerStyle(8);
	graph -> GetYaxis() -> SetTitle("%");
	graph -> GetXaxis() -> SetTitle("Epaisseur um");
	auto c2 = new TCanvas(titleGraphIntegral,titleGraphIntegral);
	graph -> Draw("ap");

	//*/
}

double shootPath(double thicknessTarget)
{
	//Profondeur de l'interaction
	double creationDeep = gRandom -> Uniform(0,1)*thicknessTarget;

	//Determination de l'angle de création et du parcours de l'ion
	//double angle = gRandom -> Uniform(0,1)*PI/2;
	double path = creationDeep/cos(gRandom -> Uniform(0,1)*PI/2);

	return path;
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

Double_t loadDensity(TString filename = "")
{
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

int nbFFstopped(double range = 0.*µm, double thicknessTarget = 1.e-10*µm, int nbShoots = 100, bool print = false)
{
	//std::cout << "range = " << range << " thickness = " << thicknessTarget << "  rayon = " << rayonTarget << std::endl;
	int nbStopped = 0;
	for (int i = 0; i<nbShoots; i++) 
	{
		double path = shootPath(thicknessTarget) ;
		//std::cout << "path : " << path << "  range : " << range << std::endl;
		if (path > range) nbStopped++;
	}
	if (print) std::cout << "nb stopped : " << nbStopped << " for thickness = " << thicknessTarget << " µm" << std::endl;

	return nbStopped;
}

/*
A titre d'archivage : 

std::map<double,double> rangeToStopPower(std::map<double,double> rangeMap)
{
	std::map<double,double> stopPowerMap;

	double previousRange = 0;
	double previousEnergy = 0;

	for (std::pair<double,double> itr : rangeMap)
	{
		stopPowerMap[itr.first] = (itr.first-previousEnergy)*µm/((itr.second-previousRange)*(density/10.));
		previousEnergy = itr.first;
		previousRange = itr.second;
		//std::cout << "E : " << itr.first << "  dx : " <<  stopPowerMap[itr.first] << std::endl;
	}
	return stopPowerMap;
}

std::map<double,double> loadData (std::string file = "",bool print = false,bool show = false,std::string choix = "range")
{
	std::map<double,double> rangeMap;
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
				double energy = stod(line.substr(0,7))*findUnit(line.substr(8,3));
				if (choix == "range")
					rangeMap[energy]=stod(line.substr(37,5))*findUnit(line.substr(43,2));// range*rangeUnit
				else if (choix == "range(um)")
					rangeMap[energy]=stod(line.substr(37,5))*findUnit(line.substr(43,2))/µm;// range*rangeUnit in µm
				else if (choix == "stoppower"){
					rangeMap[energy]=stod(line.substr(14,9));+stod(line.substr(25,9));}// dE/dx electric + dE/dx nuclear
				else {
					std::cout << "choix inconnu" << std::endl;
					return rangeMap;}
			}
			if (line.substr(0,3) == "  -") read = true;//tags the begginning of the data
		}
	}
	if(print)
		for (std::pair<double,double> itr : rangeMap)  std::cout << itr.first << " : " << itr.second << std::endl;
	if (show)
		displayStdDoubleMap(rangeMap,"Range","","",true,true,"ap*");
	//std::cout << sizeof(the_energy) << " / " << sizeof(&range[0]) << "  test : " << *(&the_energy + 1) - the_energy << std::endl;

	return rangeMap;
}*/