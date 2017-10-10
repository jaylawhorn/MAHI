#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TMath.h>
#include <TF1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraphErrors.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <vector>
#include <iostream>
#include <iomanip>

#endif

void doStatistics(TString infile="/afs/cern.ch/work/j/jlawhorn/QCD_Pt-15to7000_TuneCUETP8M1_Flat_13TeV_pythia8/All_HCALTree.root") {

  TFile *f = new TFile(infile, "read");
  TTree *t = (TTree*) f->Get("Values");

  float cuts[21] = { 5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 125, 150, 175, 200, 250, 300, 400, 500, 1000, 3000 }; 
  float ycuts[51] = { 0 };
  for (int i=0; i<51; i++) ycuts[i] = 0.02*i;

  float ycuts2[101] = { 0 };
  for (int i=0; i<101; i++) ycuts2[i] = 0.01*i;

  TH2D *h3 = new TH2D("h3", "", 20, &cuts[0], 100, &ycuts2[0]);
  TH2D *h4 = new TH2D("h4", "", 20, &cuts[0], 50, &ycuts[0]);
  TH2D *h5 = new TH2D("h5", "", 20, &cuts[0], 50, &ycuts[0]);
  TH2D *h6 = new TH2D("h6", "", 20, &cuts[0], 100, &ycuts2[0]);

  TGraphErrors *g3 = new TGraphErrors();
  TGraphErrors *g4 = new TGraphErrors();
  TGraphErrors *g5 = new TGraphErrors();
  TGraphErrors *g6 = new TGraphErrors();

  TCanvas *c = new TCanvas("c","c",800, 600);

  t->Draw("nTS3:TS4>>h3");
  t->Draw("nTS4:TS4>>h4");
  t->Draw("nTS5:TS4>>h5");
  t->Draw("nTS6:TS4>>h6");

  for (int i=0; i<h4->GetNbinsX(); i++) {

    int binx, biny, binz;
    h4->GetXaxis()->SetRange(i+1, i+1);
    h4->GetBinXYZ(h4->GetMaximumBin(), binx, biny, binz);

    double maxV = h4->GetMaximum();

    g4->SetPoint(i, h4->GetXaxis()->GetBinCenter(i+1), h4->GetYaxis()->GetBinCenter(biny));
    g4->SetPointError(i, 0, h4->GetRMS(2));

    h3->GetXaxis()->SetRange(i+1, i+1);
    h3->GetBinXYZ(h3->GetMaximumBin(), binx, biny, binz);
    maxV = h3->GetMaximum();
    g3->SetPoint(i, h3->GetXaxis()->GetBinCenter(i+1), h3->GetYaxis()->GetBinCenter(biny));
    g3->SetPointError(i, 0, h3->GetRMS(2));

    h5->GetXaxis()->SetRange(i+1, i+1);
    h5->GetBinXYZ(h5->GetMaximumBin(), binx, biny, binz);
    maxV = h5->GetMaximum();
    g5->SetPoint(i, h5->GetXaxis()->GetBinCenter(i+1), h5->GetYaxis()->GetBinCenter(biny));
    g5->SetPointError(i, 0, h5->GetRMS(2));

    h6->GetXaxis()->SetRange(i+1, i+1);
    h6->GetBinXYZ(h6->GetMaximumBin(), binx, biny, binz);
    maxV = h6->GetMaximum();
    g6->SetPoint(i, h6->GetXaxis()->GetBinCenter(i+1), h6->GetYaxis()->GetBinCenter(biny));
    g6->SetPointError(i, 0, h6->GetRMS(2));

  }

  c->SetLogx();

  g4->Draw("ap");

  g4->GetXaxis()->SetTitle("Charge in TS4");
  g4->GetYaxis()->SetTitle("Fraction in TS4");

  TF1 *fu4 = new TF1("fu4","[0]+[1]*log(x)+[2]*log(x)*log(x)",0,3000);
  g4->Fit("fu4","R");

  c->SaveAs("ts4.png");

  g3->Draw("ap");

  g3->GetXaxis()->SetTitle("Charge in TS3");
  g3->GetYaxis()->SetTitle("Fraction in TS3");

  TF1 *fu3 = new TF1("fu3","[0]+[1]*log(x)+[2]*log(x)*log(x)",0,3000);
  g3->Fit("fu3","R");

  c->SaveAs("ts3.png");

  g5->Draw("ap");

  g5->GetXaxis()->SetTitle("Charge in TS5");
  g5->GetYaxis()->SetTitle("Fraction in TS5");

  TF1 *fu5 = new TF1("fu5","[0]+[1]*log(x)+[2]*log(x)*log(x)",0,3000);
  g5->Fit("fu5","R");

  c->SaveAs("ts5.png");

  g6->Draw("ap");

  g6->GetXaxis()->SetTitle("Charge in TS6");
  g6->GetYaxis()->SetTitle("Fraction in TS6");

  TF1 *fu6 = new TF1("fu6","[0]+[1]*log(x)+[2]*log(x)*log(x)",0,3000);
  g6->Fit("fu6","R");

  c->SaveAs("ts6.png");


  cout << "nTS3 = " << fu3->GetParameter(0) << " + " << fu3->GetParameter(1) << " * log(x) + " << fu3->GetParameter(2) << " * (log(x))^2" << endl;
  cout << "nTS4 = " << fu4->GetParameter(0) << " + " << fu4->GetParameter(1) << " * log(x) + " << fu4->GetParameter(2) << " * (log(x))^2" << endl;
  cout << "nTS5 = " << fu5->GetParameter(0) << " + " << fu5->GetParameter(1) << " * log(x) + " << fu5->GetParameter(2) << " * (log(x))^2" << endl;
  cout << "nTS6 = " << fu6->GetParameter(0) << " + " << fu6->GetParameter(1) << " * log(x) + " << fu6->GetParameter(2) << " * (log(x))^2" << endl;

}
