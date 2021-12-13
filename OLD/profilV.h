#include "./coROOTlib.h"

std::array<std::vector<Double_t>,2> loadData (std::string file = "");
Double_t loadDensity(TString filename = "");
std::map<double,double> rangeToStopPower(std::map<double,double> rangeMap);
double shootPath(double thicknessTarget);
int nbFFstopped(double range = 0.*µm, double thicknessTarget = 1.e-20, int nbShoots = 100,bool print = false);

