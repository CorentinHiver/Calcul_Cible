/*
	profilV(): profil de vitesse des fragments de fission, et autres calculs intermédiaires
	Cible fine cylindrique
	Nécessite donnees SRIM
	Auteur : Corentin Hiver
*/
#include "./profilV.h"
#include <fstream>

static double rho = 19.;
static double rayonTarget = 1*cm;

static double massFF = 92*amu;

void profilV()
{
	gRandom = new TRandom(time(0));
	//const char *name = "Raw_energy_profile";
	//const char *name = "Raw_speed_profile";
	//const char *name = "Range_and_Spline";
	//const char *name = "Energy_profile_8um";
	//const char *name = "Energy_profiles";
	//const char *name = "Speed_profiles";
	//const char *name = "Range_left_profile";
	const char *name = "Range_left_profile_85Se";
	//const char *name = "parcours";


	auto c1 = new TCanvas(name,name);


	//std::map<double,double> rangeMap = loadData("Strontium_in_Uranium_0-1GeV.txt",false,false,"range");
	std::map<double,double> rangeMap = loadData("85Se_in_UO5.txt",false,false,"range");
	displayStdDoubleMap(rangeMap,"Range","Energy MeV","Range (m)", true,true,"ap*");

	int n_data = rangeMap.size();
	Double_t Energy[n_data],Range[n_data];
	int i = 0;
	for (std::pair<double,double> itr : rangeMap)
	{
		Energy[i] = itr.first;
		Range[i] = itr.second;
		i++;
	}
	
	TGraph *graph = new TGraph(n_data,Energy,Range);
	graph -> Draw("ap*");
	graph -> SetTitle("Range");

	graph -> GetXaxis() -> SetTitle("Energy MeV");
	graph -> GetYaxis() -> SetTitle("Range (m)");
	
	gPad -> SetTitle("TESTD");
	gPad -> SetLogx(true);
	gPad -> SetLogy(true);

	TSpline3 *energySpline = new TSpline3("test_spline",Energy,Range,n_data);


	//displayStdDoubleMap(loadData("Strontium_in_Uranium_0-1GeV.txt",false,false,"range(um)"), "Range", "Energy MeV", "Range (um)", true, true, "ap*");
	//displayStdDoubleMap(loadData("85Se_in_UO5",false,false,"range(um)"), "Range", "Energy MeV", "Range (um)", true, true, "ap*");

	//TSpline3 *energySpline = new TSpline3(getSpline3FromStdMap(rangeMap,true));  // energy = f(range)
	//TSpline5 *energySpline5 = new TSpline5(getSpline5FromStdMap(rangeMap,true));
	TSpline3 *rangeSpline = new TSpline3(getSpline3FromStdMap(rangeMap,false));// range = f(energy)

	energySpline -> Draw("aCsame");
	energySpline -> SetLineColor(kGreen);

	double range = rangeSpline -> Eval(110);

	printD(range);
	printD(energySpline -> Eval(10));

	//! Differents ways to calculate MeV/(mg/cm2) : one by reading data in SRIM, another from the range map
	/*reading the dE/dx data in SRIM file : 
	std::map<double,double> stopPowerMapFile = loadData("Strontium_in_Uranium_0-1GeV.txt",false,false,"stoppower");
	displayStdDoubleMap(stopPowerMapFile,"Stopping Power","Energy MeV", "dE/dx  MeV/ (mg/cm2)", true,false,"apC*");
	//*/
	//*calculate effective (delta E /delta x) from range data : 
	//std::map<double,double> stopPowerMapRange = rangeToStopPower(rangeMap);
	//displayStdDoubleMap(stopPowerMapRange,"Stopping Power","Energy MeV", "DE/Dx  MeV/ (mg/cm2)", true,false,"p*");
	//*/

	//This allowed me to calculate the difference between the to above stopping powers
	//displayStdDoubleMap(substractStdDoubleMapSameAbsciss(stopPowerMapRange,stopPowerMapFile),"Diff between 2 stop power","Energy MeV", "Diff dE/dx  MeV/ (mg/cm2)", true,false,"ap*");

	/*! Calcule le nombre de fragments arrêtés pour différentes épaisseurs de cible

	std::vector<Double_t> epaisseurs ;
	double min = 0.5; double max = 10; double step=0.25;
	for (int i = 0; i< 1+(max-min)/step;i++) epaisseurs.push_back(min+i*step);
	Double_t stopped[epaisseurs.size()];
	Double_t thickness[epaisseurs.size()];
	int i = 0;
	for (auto &dx : epaisseurs)
	{
		int nbShoots = 1e6;		

		double thicknessTarget = dx*µm;
		int nbStopped = nbFFstopped(range, thicknessTarget, nbShoots);

		std::cout << "dx = " << dx << " µm ---> " << 100.*nbStopped/nbShoots << "%" << " arretes" << std::endl;
		
		stopped[i] = 100.*nbStopped/nbShoots;
		thickness[i] = dx;
		i++;
	}
	
	TGraph *graph = new TGraph(epaisseurs.size(),thickness,stopped);
	graph -> SetTitle("Fraction 92Sr stopped in target"); 
	//graph -> SetTitle("Fraction 85Se stopped in target"); 
	graph -> SetMarkerStyle(8);
	graph -> GetYaxis() -> SetTitle("Fragments arretes dans la cible %");
	graph -> GetXaxis() -> SetTitle("Epaisseur um");
	graph -> Draw("apc");
	//*/

/* Determines the speed/rangeLeft profile :

	//TH1D *h = new TH1D("Range left profile" , "", 1000,0,10);
	//TH1D *h = new TH1D(name, "", 10000,1e-3,1.);
	std::vector<Double_t> epaisseurs ;
	double min = 5; double max = 10; double step=1.;
	for (int i = 0; i< 1+(max-min)/step;i++) epaisseurs.push_back(min+i*step);

	auto *legend = new TLegend(0.25,0.6,0.45,0.9,"thicknesses");

	TH1D **h = new TH1D*[epaisseurs.size()];

	std::vector<Double_t> thck,integral; Double_t borneMax = 0.4 ; //In the X axis unit

	int itr = 0;

	std::vector<Int_t> nbStopped;

	for(Double_t &thicknessTarget : epaisseurs)
	{
		//TH1D *h = new TH1D(name, "", 1000, 0.1, 2.e2);
		TString histoName = (TString) boost::lexical_cast<std::string>(thicknessTarget) + " um";

		Int_t nb_pts = 1000; Double_t borne_min = 0.; Double_t borne_max = 10.;

		h[itr] = new TH1D(histoName, "", nb_pts, borne_min, borne_max);

		int nbShoots = 1e7;
		//double thicknessTarget = 8*µm;
		std::cout << "Calculs pour " << thicknessTarget << "um" << std::endl;
		Int_t nb_stopped = 0;
		for (int i = 0; i<nbShoots; i++) 
		{
			//std::cout << i << std::endl;
			double path = shootPath(thicknessTarget*µm);
			double rangeLeft = (range-path);
			if (rangeLeft < 0) {rangeLeft = 0.;nb_stopped++;}
			else
			{	
				h[itr] -> Fill(path/µm);
				//h -> Fill(rangeLeft/µm); //range left profile entry
				//h -> Fill(Energy); // energy profile entry
				//h -> Fill(energySpline -> Eval(rangeLeft));				
				//h[itr] -> Fill(energySpline -> Eval(rangeLeft));
				//h[itr] -> Fill(energySpline5 -> Eval(rangeLeft));
				//h[itr] -> Fill(energySpline -> FindX(rangeLeft));

				//printD(energySpline -> Eval(1));
				//printD(rangeLeft/µm);

				//h[itr] -> Fill(sqrt(2*(energySpline -> Eval(rangeLeft)/J)/massFF)*ns/cm);// en cm/ns, fonctionne
				//h[itr] -> Fill(rangeLeft/µm);

			}
		}	
		h[itr] -> Draw("same");
		h[itr] -> SetLineColor(itr+1);
		legend -> AddEntry(h[itr],histoName);
		//std::cout << h[itr] -> GetMean() << std::endl;
		//h -> GetXaxis() -> SetTitle("um");
		//h[itr] -> GetXaxis() -> SetTitle("MeV");
		//TString name_legend = std::to_string(thicknessTarget)+" µm";
		//legend -> AddEntry(h[i],name_legend);
		//h[itr] -> GetXaxis() -> SetTitle("cm/ns");
		h[itr] -> GetXaxis() -> SetTitle("um");
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
	double angle = gRandom -> Uniform(0,1)*PI/2;
	double path = creationDeep/cos(angle);

	if (path < 1*cm) return path;
	else return 1*cm;
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
}

std::map<double,double> rangeToStopPower(std::map<double,double> rangeMap)
{
	std::map<double,double> stopPowerMap;

	double previousRange = 0;
	double previousEnergy = 0;

	//if ("MeV/(g/cm2)")

	for (std::pair<double,double> itr : rangeMap)
	{
		stopPowerMap[itr.first] = (itr.first-previousEnergy)*µm/((itr.second-previousRange)*(rho/10.));
		previousEnergy = itr.first;
		previousRange = itr.second;
		//std::cout << "E : " << itr.first << "  dx : " <<  stopPowerMap[itr.first] << std::endl;
	}
	return stopPowerMap;
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

//!!! 1 : déterminer la pente entre deux points du range = f(energy)

/ 	double previousRange = 0;
		// 	double ReadenRange = 0;
		// 	double previousEnergy = 0;
		// 	double ReadenEnergy = 0;

		// 	double slope = 0;

		// 	for (auto &itr : rangeMap)
		// 	{
		// 		if (itr.second > rangeLeft) 
		// 		{
		// 			//h -> Fill(itr.first); //Raw energy profile entry
		// 			h -> Fill( sqrt(2*(itr.first*1.6e-16)/(massFF))*1.e-7); //Raw speed profile entry
		// 			slope = (previousEnergy-itr.first)/(previousRange-itr.second);				
		// 			break;
		// 		}
		// 		previousEnergy = itr.first;
		// 		previousRange = itr.second;
		// 	}
		// 	double Energy = rangeLeft*slope;
		// 	double Speed = sqrt(2*(Energy*1.6e-19)/(massFF*1.66e-24))*1.e-7;
		// 	std::cout << energySpline.Eval(rangeLeft) << std::endl;
		// 	h -> Fill(energySpline.Eval(rangeLeft));
		// }


		*/
