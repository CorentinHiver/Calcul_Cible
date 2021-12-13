#include "../profilV.h"

void shootRange()
{

	int nbStopped = 0;

	double thicknessTarget = 5*µm;
	TH1D *creationDeepHist = new TH1D("creationDeep","",1000,0,thicknessTarget/µm+1);
	TH1D *angleHist = new TH1D("angleHist","",1000,0,91);
	TH1D *cosAlphaHist = new TH1D("cosAlphaHist","",1000,1e-3,1);
	TH1D *inverseCosAlphaHist = new TH1D("inverseCosAlphaHist","",1000,1,11);

	Int_t nbShoots = 1e6;

	for (int i = 0; i<nbShoots; i++) 
	{
		//Profondeur de l'interaction
		double creationDeep = gRandom -> Uniform(0,1)*thicknessTarget;
		creationDeepHist -> Fill(creationDeep/µm);

		//Determination de l'angle de création et du parcours de l'ion
		double angle = gRandom -> Uniform(0,1)*PI/2;
		angleHist -> Fill(angle*180/PI);		
		cosAlphaHist -> Fill(cos(angle));
		inverseCosAlphaHist -> Fill(1./cos(angle));
		double path = creationDeep/cos(angle);
	}

	/*
	auto c1 = new TCanvas("CreationDeep","CreationDeep");
	creationDeepHist -> Draw();
	cosAlphaHist -> SetStats(false);
	creationDeepHist -> Scale(100./creationDeepHist -> Integral());
	creationDeepHist -> GetXaxis() -> SetTitle("CreationDeep [um]");
	creationDeepHist -> GetYaxis() -> SetTitle("Yield [%]");
	angleHist -> GetYaxis() -> SetRangeUser(0,1);
	//*/

	/*
	auto c2 = new TCanvas("Angle","Angle");
	angleHist -> Draw();
	cosAlphaHist -> SetStats(false);
	angleHist -> GetXaxis() -> SetTitle("Angle [#circ]");
	angleHist -> GetYaxis() -> SetTitle("Yield [%]");
	angleHist -> Scale(100./angleHist -> Integral());
	angleHist -> GetYaxis() -> SetRangeUser(0,1);
	//*/

	/*
	auto c3 = new TCanvas("cos(alpha)","cos(alpha)");
	cosAlphaHist -> Draw();
	cosAlphaHist -> SetStats(false);
	cosAlphaHist -> GetXaxis() -> SetTitle("cos(#alpha)");
	cosAlphaHist -> GetYaxis() -> SetTitle("Yield [%]");
	cosAlphaHist -> Scale(100./cosAlphaHist -> Integral());
	cosAlphaHist -> GetYaxis() -> SetRangeUser(0,1);
	//*/

	/*
	auto c4 = new TCanvas("1/cos(alpha)}","1/cos(alpha)}");
	inverseCosAlphaHist -> Draw("hist");
	inverseCosAlphaHist -> SetStats(false);
	inverseCosAlphaHist -> GetXaxis() -> SetTitle("#frac{1}{cos(#alpha)}");
	inverseCosAlphaHist -> GetYaxis() -> SetTitle("Yield [%]");	
	inverseCosAlphaHist -> Scale(100./inverseCosAlphaHist -> Integral());
	//inverseCosAlphaHist -> GetYaxis() -> SetRangeUser(0,100);
	//*/
}