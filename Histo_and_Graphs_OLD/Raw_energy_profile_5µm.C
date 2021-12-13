void Raw energy profile()
{
//=========Macro generated from canvas: Raw energy profile/Map Visualiser v1
//=========  (Tue Nov  2 11:25:44 2021) by ROOT version 6.22/02
   TCanvas *Raw energy profile = new TCanvas("Raw energy profile", "Map Visualiser v1",206,314,700,500);
   Raw energy profile->Range(-3.375,1.303296,0.375,4.60502);
   Raw energy profile->SetFillColor(0);
   Raw energy profile->SetBorderMode(0);
   Raw energy profile->SetBorderSize(2);
   Raw energy profile->SetLogx();
   Raw energy profile->SetLogy();
   Raw energy profile->SetFrameBorderMode(0);
   Raw energy profile->SetFrameBorderMode(0);
   
   TH1D *RawsPenergysPprofile__1 = new TH1D("RawsPenergysPprofile__1","",10000,0.001,1);
   RawsPenergysPprofile__1->SetBinContent(91,2109);
   RawsPenergysPprofile__1->SetBinContent(101,204);
   RawsPenergysPprofile__1->SetBinContent(111,104);
   RawsPenergysPprofile__1->SetBinContent(121,114);
   RawsPenergysPprofile__1->SetBinContent(131,99);
   RawsPenergysPprofile__1->SetBinContent(141,126);
   RawsPenergysPprofile__1->SetBinContent(151,126);
   RawsPenergysPprofile__1->SetBinContent(161,86);
   RawsPenergysPprofile__1->SetBinContent(171,128);
   RawsPenergysPprofile__1->SetBinContent(191,222);
   RawsPenergysPprofile__1->SetBinContent(216,279);
   RawsPenergysPprofile__1->SetBinContent(241,223);
   RawsPenergysPprofile__1->SetBinContent(266,274);
   RawsPenergysPprofile__1->SetBinContent(291,222);
   RawsPenergysPprofile__1->SetBinContent(316,225);
   RawsPenergysPprofile__1->SetBinContent(341,289);
   RawsPenergysPprofile__1->SetBinContent(366,210);
   RawsPenergysPprofile__1->SetBinContent(391,259);
   RawsPenergysPprofile__1->SetBinContent(441,435);
   RawsPenergysPprofile__1->SetBinContent(491,486);
   RawsPenergysPprofile__1->SetBinContent(541,481);
   RawsPenergysPprofile__1->SetBinContent(591,461);
   RawsPenergysPprofile__1->SetBinContent(641,440);
   RawsPenergysPprofile__1->SetBinContent(691,457);
   RawsPenergysPprofile__1->SetBinContent(791,847);
   RawsPenergysPprofile__1->SetBinContent(891,868);
   RawsPenergysPprofile__1->SetBinContent(991,871);
   RawsPenergysPprofile__1->SetBinContent(1092,915);
   RawsPenergysPprofile__1->SetBinContent(1192,942);
   RawsPenergysPprofile__1->SetBinContent(1292,883);
   RawsPenergysPprofile__1->SetBinContent(1392,886);
   RawsPenergysPprofile__1->SetBinContent(1492,828);
   RawsPenergysPprofile__1->SetBinContent(1592,877);
   RawsPenergysPprofile__1->SetBinContent(1692,926);
   RawsPenergysPprofile__1->SetBinContent(1792,833);
   RawsPenergysPprofile__1->SetBinContent(1992,1735);
   RawsPenergysPprofile__1->SetBinContent(2243,2071);
   RawsPenergysPprofile__1->SetBinContent(2493,2145);
   RawsPenergysPprofile__1->SetBinContent(2743,2072);
   RawsPenergysPprofile__1->SetBinContent(2993,2156);
   RawsPenergysPprofile__1->SetBinContent(3244,2138);
   RawsPenergysPprofile__1->SetBinContent(3494,2261);
   RawsPenergysPprofile__1->SetBinContent(3744,2282);
   RawsPenergysPprofile__1->SetBinContent(3994,2208);
   RawsPenergysPprofile__1->SetBinContent(4495,4553);
   RawsPenergysPprofile__1->SetBinContent(4995,4551);
   RawsPenergysPprofile__1->SetBinContent(5496,4667);
   RawsPenergysPprofile__1->SetBinContent(5996,4742);
   RawsPenergysPprofile__1->SetBinContent(6497,4634);
   RawsPenergysPprofile__1->SetBinContent(6997,4828);
   RawsPenergysPprofile__1->SetBinContent(7998,9846);
   RawsPenergysPprofile__1->SetBinContent(8999,9938);
   RawsPenergysPprofile__1->SetBinContent(10001,7061450);
   RawsPenergysPprofile__1->SetEntries(7146012);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("Raw energy profile");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 7146012");
   ptstats_LaTex = ptstats->AddText("Mean  = 0.4761");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.2817");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   RawsPenergysPprofile__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(RawsPenergysPprofile__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   RawsPenergysPprofile__1->SetLineColor(ci);
   RawsPenergysPprofile__1->GetXaxis()->SetTitle("MeV");
   RawsPenergysPprofile__1->GetXaxis()->SetLabelFont(42);
   RawsPenergysPprofile__1->GetXaxis()->SetTitleOffset(1);
   RawsPenergysPprofile__1->GetXaxis()->SetTitleFont(42);
   RawsPenergysPprofile__1->GetYaxis()->SetLabelFont(42);
   RawsPenergysPprofile__1->GetYaxis()->SetTitleFont(42);
   RawsPenergysPprofile__1->GetZaxis()->SetLabelFont(42);
   RawsPenergysPprofile__1->GetZaxis()->SetTitleOffset(1);
   RawsPenergysPprofile__1->GetZaxis()->SetTitleFont(42);
   RawsPenergysPprofile__1->Draw("");
   Raw energy profile->Modified();
   Raw energy profile->cd();
   Raw energy profile->SetSelected(Raw energy profile);
}
