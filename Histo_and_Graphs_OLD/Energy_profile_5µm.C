void Energy_profile_5µm()
{
//=========Macro generated from canvas: Energy_profile_5µm/Energy_profile_5µm
//=========  (Tue Nov  2 16:36:02 2021) by ROOT version 6.22/02
   TCanvas *Energy_profile_5µm = new TCanvas("Energy_profile_5µm", "Energy_profile_5µm",543,351,700,500);
   Energy_profile_5µm->Range(3.75,20.22754,11.25,70.10925);
   Energy_profile_5µm->SetFillColor(0);
   Energy_profile_5µm->SetBorderMode(0);
   Energy_profile_5µm->SetBorderSize(2);
   Energy_profile_5µm->SetFrameBorderMode(0);
   Energy_profile_5µm->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[21] = {
   5,
   5.25,
   5.5,
   5.75,
   6,
   6.25,
   6.5,
   6.75,
   7,
   7.25,
   7.5,
   7.75,
   8,
   8.25,
   8.5,
   8.75,
   9,
   9.25,
   9.5,
   9.75,
   10};
   Double_t Graph0_fy1[21] = {
   28.54116,
   30.27865,
   32.12408,
   34.09179,
   36.32402,
   38.89735,
   41.258,
   43.40971,
   45.42487,
   47.28462,
   49.0797,
   50.72417,
   52.24921,
   53.70767,
   55.07356,
   56.3501,
   57.56904,
   58.71958,
   59.79258,
   60.81786,
   61.79563};
   TGraph *graph = new TGraph(21,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("Fraction 92Sr stopped in target");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(8);
   
   TH1F *Graph_Graph01 = new TH1F("Graph_Graph01","Fraction 92Sr stopped in target",100,4.5,10.5);
   Graph_Graph01->SetMinimum(25.21571);
   Graph_Graph01->SetMaximum(65.12108);
   Graph_Graph01->SetDirectory(0);
   Graph_Graph01->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01->SetLineColor(ci);
   Graph_Graph01->GetXaxis()->SetTitle("Epaisseur um");
   Graph_Graph01->GetXaxis()->SetLabelFont(42);
   Graph_Graph01->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01->GetXaxis()->SetTitleFont(42);
   Graph_Graph01->GetYaxis()->SetTitle("Fragments arretes dans la cible %");
   Graph_Graph01->GetYaxis()->SetLabelFont(42);
   Graph_Graph01->GetYaxis()->SetTitleFont(42);
   Graph_Graph01->GetZaxis()->SetLabelFont(42);
   Graph_Graph01->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph01);
   
   graph->Draw("apc");
   
   TPaveText *pt = new TPaveText(0.235702,0.9344958,0.764298,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Fraction 92Sr stopped in target");
   pt->Draw();
   Energy_profile_5µm->Modified();
   Energy_profile_5µm->cd();
   Energy_profile_5µm->SetSelected(Energy_profile_5µm);
}
