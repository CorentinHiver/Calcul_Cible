//-------------------------------------------------
//!-----------  Some useful constants  ------------
//-------------------------------------------------

//Distance
double  A = 1.E-10;
double nm = 1.E-9;
double um = 1.E-6;
double µm = 1.E-6;
double cm = 1.E-2;
double  m = 1.E+0;

//Time
double ns =  1.E-9;

//Mass
double amu= 1.66E-27;
double mg = 1E-6;
double  g = 1E-3;

//Energy
double keV = 1.E-3;
double MeV = 1.E+0;
double GeV = 1.E+3;
double   J = 6.242E+12;

//Constants
double PI = 3.14159;

enum class Ejectile{Gamma,Neutron,Proton,Deuteron,Triton,Helium3,Alpha};

//--------------------------------------------------
//!-------------  Useful includes  -----------------
//--------------------------------------------------

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

//--------------------------------------------------
//!-------------  Useful functions  ----------------
//--------------------------------------------------

//  Prints integers numbers :

void printI(int i)
{
	std::cout << i << std::endl;
}


//  Prints double precision numbers :

void printD(double d)
{
	std::cout << d << std::endl;
}


// Prints TStrings: 

void printStr(TString str)
{
	std::cout << str << std::endl;
}

// Prints bool: 

void printBool(bool b)
{
	std::cout << b << std::endl;
}

//  Removes blank spaces from std strings: 

std::string removeBlankSpace(std::string str)
{
	int pos = 0;
	while ( (pos = (int)str.find(" ")) != -1) 
	{
		str = str.substr(0,pos) + str.substr(pos+1,str.size()-pos-1);//replaces all commas with dots
	} 
	return str;
}


//  Replaces all commas of a string with dots
std::string replaceCommasWithDots(std::string str)
{
	int pos = 0;
	while ( (pos = (int)str.find(",")) != -1) 
	{
		str = str.substr(0,pos) + "." + str.substr(pos+1,str.size()-pos-1);
	} 
	return str;
}


//  Returns the unit readen in the input string :

double findUnit(std::string unit = "")
{
	//std::cout << "'" << unit << "'" << "  --->  '" << removeBlankSpace(unit) << "'" << std::endl;

	unit = removeBlankSpace(unit);

	if (unit == "keV") return keV;
	else if (unit == "MeV") return MeV;
	else if (unit == "GeV") return GeV;

	else if (unit == " A") return A;//Angstrom
	else if (unit == "A") return A;//Angstrom
	else if (unit == "A ") return A;//Angstrom
	else if (unit == "um") return µm;
	else if (unit == "µm") return µm;
	else if (unit == "")
	{
		std::cout << "no unit read !" << std::endl;
		return -1.;
	} 	

	else 
	{
		std::cout << "unkown unit : " << unit <<std::endl;
		return 0.;
	}
}


//  Creates of TGraph with the keys as X axis and the values as Y axis :

void displayStdDoubleMap(const std::map<double,double>& map, const char *Title = "", const char *XLabel = "", const char *YLabel = ""
												, bool logx = false, bool logy = false, const char *graphOptions = "")
{
	int n = map.size();
	Double_t x[n],y[n];
	int i = 0;
	for (std::pair<double,double> itr : map)
	{
		x[i] = itr.first;
		y[i] = itr.second;
		i++;
	}
	
	TGraph *graph = new TGraph(n,x,y);
	graph -> Draw(graphOptions);
	graph -> SetTitle(Title);

	graph -> GetXaxis() -> SetTitle(XLabel);
	graph -> GetYaxis() -> SetTitle(YLabel);
	
	gPad -> SetTitle("Map Visualiser v1");
	gPad -> SetLogx(logx);
	gPad -> SetLogy(logy);
}


//  To be used with caution. The two maps must have exactly the same keys. Returns a map with the difference of the two key's values : 

std::map<double,double> substractStdDoubleMapSameAbsciss(const std::map<double,double>& map1, const std::map<double,double> & map2)
{
	//! Les deux maps doivents avoir exactement la même taille et les mêmes clés

	std::map<double,double> diffMap;
	std::map<double,double> emptyMap;

	if (map1.size() == map2.size())
	{
		for (auto &itr : map1)
		{
			bool test = (bool) map2.count(itr.first); //check that keys are the same between the two maps
			if (test)
			{
				diffMap[itr.first] = itr.second-map2.at(itr.first);
				std::cout << itr.second << " - " << map2.at(itr.first) << " = " << diffMap[itr.first] << std::endl;
			}
			else
				{return emptyMap;}
		}
		
		return diffMap;
	}

	else
		{
			return emptyMap;
		}
}

TSpline3 getSpline3FromStdMap(std::map<double,double> data, bool invertAxis = false)
{
	std::vector<double> x;
	std::vector<double> y;

	for (auto &itr : data)
	{
		x.push_back( itr.first );
		y.push_back( itr.second );
	}
	Double_t *xx = &x[0];
	Double_t *yy = &y[0];

	if (!invertAxis)
	{
		TSpline3 retSpline ("Data_Spline",xx,yy,x.size());
		return retSpline;
	}
	
	else
	{
		TSpline3 retSpline ("Data_Spline",yy,xx,x.size());
		return retSpline;
	}	
}

TSpline5 getSpline5FromStdMap(std::map<double,double> data, bool invertAxis = false)
{
	std::vector<double> x;
	std::vector<double> y;

	for (auto &itr : data)
	{
		x.push_back( itr.first );
		y.push_back( itr.second );
	}
	Double_t *xx = &x[0];
	Double_t *yy = &y[0];

	if (!invertAxis)
	{
		TSpline5 retSpline ("Data_Spline",xx,yy,x.size());
		return retSpline;
	}

	else
	{
		TSpline5 retSpline ("Data_Spline",yy,xx,x.size());
		return retSpline;
	}
}

void printDataD(const Double_t *array1, const Double_t *array2, Int_t nb_values)
{
	for (unsigned int i = 0; i < nb_values; i++) 
	{
		std::cout << array1[i] << " --> " <<  array2[i] << std::endl;
	}
}

TString DoubleToTString(double value, int precision = 6, TString prependString = "", TString appendString = "")
{

	std::stringstream stream;
	if ((bool)precision) stream << std::fixed << std::setprecision(2) << value;
	else stream << std::fixed << value;
	return (TString) (prependString + (TString) stream.str() + appendString);
}


class myMultiGraph
{

public:
	myMultiGraph(TString nameCanvas, TString GraphTitle, TGraph *gr, TString GraphName, Option_t *options = "ac")
	{
		c -> SetName(nameCanvas);
		c -> SetTitle(nameCanvas);

		gr -> Draw(options);
		gr -> SetTitle(GraphTitle);
		gr -> SetLineColor(color[lineColor]);
		legend -> AddEntry(gr,GraphName);

		firstGraph = gr;
		lineColor ++;
	}

	void addEntry(TGraph *gr, TString name, TString options = "")
	{
		gr -> Draw("SAME"+options);
		gr -> SetLineColor(color[lineColor]);
		legend -> AddEntry(gr, name);
		legend -> Draw();
		lineColor++;
	}

	void addEntry(TGraph *gr, TString name, Int_t color, TString options = "")
	{
		gr -> Draw("SAME"+options);
		gr -> SetLineColor(color);
		legend -> AddEntry(gr, name);
		legend -> Draw();
	}

	void setXRange(Double_t min, Double_t max)
	{
		firstGraph -> GetXaxis() -> SetRangeUser(min,max);
	}

	void setYRange(Double_t min, Double_t max)
	{
		firstGraph -> GetYaxis() -> SetRangeUser(min,max);
	}

private:
	TGraph *firstGraph;
	TCanvas *c = new TCanvas();
	TLegend *legend = new TLegend();
	Int_t lineColor = 0;
	std::vector<Int_t> color = {kBlue,kRed,kCyan,kBlack,kMagenta};
};