void Parcours_2_fragments()
{
//=========Macro generated from canvas: Parcours/Parcours
//=========  (Tue Nov  9 13:01:08 2021) by ROOT version 6.22/02
   TCanvas *Parcours = new TCanvas("Parcours", "Parcours",10,61,700,500);
   Parcours->Range(-1.630079,-12.93801,14.8597,115.3639);
   Parcours->SetFillColor(0);
   Parcours->SetBorderMode(0);
   Parcours->SetBorderSize(2);
   Parcours->SetTopMargin(0.1197479);
   Parcours->SetFrameBorderMode(0);
   Parcours->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1[21] = {
   0.006,
   0.606,
   1.206,
   1.806,
   2.406,
   3.006,
   3.606,
   4.206,
   4.806,
   5.406,
   6.006,
   6.606,
   7.206,
   7.806,
   8.406,
   9.006,
   9.606,
   10.206,
   10.806,
   11.406,
   12.006};
   Double_t Graph0_fy1[21] = {
   0.034,
   3.23,
   6.318,
   9.366,
   12.441,
   15.743,
   19.262,
   22.756,
   26.48,
   30.56,
   34.895,
   40.479,
   45.691,
   49.354,
   53.303,
   56.432,
   59.059,
   61.455,
   63.612,
   65.803,
   67.164};
   TGraph *graph = new TGraph(21,Graph0_fx1,Graph0_fy1);
   graph->SetName("Graph0");
   graph->SetTitle("#splitline{Fraction of 85Se at 110 MeV and 150Ce at 60 MeV}{stopped in target}");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(20);
   
   TH1F *Graph_Graph01 = new TH1F("Graph_Graph01","#splitline{Fraction of 85Se at 110 MeV and 150Ce at 60 MeV}{stopped in target}",100,0,13.206);
   Graph_Graph01->SetMinimum(0);
   Graph_Graph01->SetMaximum(100);
   Graph_Graph01->SetDirectory(0);
   Graph_Graph01->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph01->SetLineColor(ci);
   Graph_Graph01->GetXaxis()->SetTitle("Epaisseur [mg/cm^{3}]");
   Graph_Graph01->GetXaxis()->SetLabelFont(42);
   Graph_Graph01->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01->GetXaxis()->SetTitleFont(42);
   Graph_Graph01->GetYaxis()->SetTitle("Fragments arretes dans la cible [%]");
   Graph_Graph01->GetYaxis()->SetLabelFont(42);
   Graph_Graph01->GetYaxis()->SetTitleFont(42);
   Graph_Graph01->GetZaxis()->SetLabelFont(42);
   Graph_Graph01->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph01);
   
   graph->Draw("apc");
   
   Double_t Graph1_fx2[21] = {
   0.006,
   0.606,
   1.206,
   1.806,
   2.406,
   3.006,
   3.606,
   4.206,
   4.806,
   5.406,
   6.006,
   6.606,
   7.206,
   7.806,
   8.406,
   9.006,
   9.606,
   10.206,
   10.806,
   11.406,
   12.006};
   Double_t Graph1_fy2[21] = {
   0.026,
   2.264,
   4.662,
   6.945,
   9.144,
   11.409,
   13.849,
   16.117,
   18.827,
   21.088,
   23.836,
   26.583,
   29.408,
   32.452,
   36.161,
   40.103,
   43.973,
   47.263,
   50.437,
   52.722,
   55.169};
   graph = new TGraph(21,Graph1_fx2,Graph1_fy2);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1000);
   graph->SetMarkerStyle(23);
   
   TH1F *Graph_Graph12 = new TH1F("Graph_Graph12","Graph",100,0,13.206);
   Graph_Graph12->SetMinimum(0);
   Graph_Graph12->SetMaximum(100);
   Graph_Graph12->SetDirectory(0);
   Graph_Graph12->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph12->SetLineColor(ci);
   Graph_Graph12->GetXaxis()->SetTitle("Epaisseur mg/cm^{3}");
   Graph_Graph12->GetXaxis()->SetLabelFont(42);
   Graph_Graph12->GetXaxis()->SetTitleOffset(1);
   Graph_Graph12->GetXaxis()->SetTitleFont(42);
   Graph_Graph12->GetYaxis()->SetTitle("Fragments arretes dans la cible %");
   Graph_Graph12->GetYaxis()->SetLabelFont(42);
   Graph_Graph12->GetYaxis()->SetTitleFont(42);
   Graph_Graph12->GetZaxis()->SetLabelFont(42);
   Graph_Graph12->GetZaxis()->SetTitleOffset(1);
   Graph_Graph12->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph12);
   
   graph->Draw(" pc");
   
   TLegend *leg = new TLegend(0.09885387,0.6638655,0.4512894,0.8802521,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","thicknesses","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph0","Heavy fragment {}^{150}Ce","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1","Light fragment {}^{92}Sr","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(23);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(0.15,0.8714706,0.85,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("#splitline{Fraction of 85Se at 110 MeV and 150Ce at 60 MeV}{stopped in target}");
   pt->Draw();
   Parcours->Modified();
   Parcours->cd();
   Parcours->SetSelected(Parcours);
}
