#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
#include <TSystem.h>                      // interface to OS
#include <TStyle.h>                       // class to handle ROOT plotting styles
#include <TFile.h>                        // file handle class
#include <TTree.h>                        // class to access ntuples
#include <TChain.h>                        // class to access ntuples
#include <TH1D.h>
#include <TH2D.h>
#include <TProfile2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TBenchmark.h>                   // class to track macro running statistics
#include <vector>                         // STL vector class
#include <iostream>                       // standard I/O
#include <iomanip>                        // functions to format standard I/O
#include <fstream>                        // functions for file I/O
#include <string>                         // C++ string class
#include <sstream>                        // class for parsing strings
#endif

void DrawCorrelationMatrix(
			   TString infile = "pulse_plain.root", 
			   TString label = "pulse_nosub"
			   ) {

  TFile *inf = new TFile(infile,"read");
  TTree *t = (TTree*) inf->Get("cor");

  double nHits=0;

  double avgTS[10];
  double rmsTS[10];
  double corTS[10][10];

  t->SetBranchAddress("nHits", &nHits);
  t->SetBranchAddress("avgTS",&avgTS);
  t->SetBranchAddress("rmsTS",&rmsTS);
  t->SetBranchAddress("corTS",&corTS);

  t->GetEntry(0);

  TCanvas *c = new TCanvas("c","",800, 800);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(55);
  gStyle->SetPaintTextFormat("2.2f");

  TH2D* corr_matrix = new TH2D("corr_matrix","",10,-0.5,9.5,10,-0.5,9.5);
  TH1D* avg_hist = new TH1D("avg_hist","",10,-0.5,9.5);
  TH1D* rms_hist = new TH1D("rms_hist","",10,-0.5,9.5);


  for (int i=0; i<10; i++) {
    avg_hist->SetBinContent(i+1,avgTS[i]);
    rms_hist->SetBinContent(i+1,rmsTS[i]);
  }


  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {

      corr_matrix->SetBinContent( 
				    corr_matrix->GetBin(i+1, j+1),
				    corTS[i][j]);

      corr_matrix->SetBinContent( 
				    corr_matrix->GetBin(j+1, i+1),
				    corTS[i][j]);

    }
  }

  corr_matrix->GetZaxis()->SetRangeUser(-1,1);
  corr_matrix->GetXaxis()->SetTitle("Time Slice");
  corr_matrix->GetYaxis()->SetTitle("Time Slice");
  corr_matrix->Draw("colz text");

  c->SaveAs(label+"_cor.png");

  /*  avg_hist->GetXaxis()->SetTitle("Time Slice");
  avg_hist->GetYaxis()->SetTitle("Average");
  avg_hist->Draw("hist");

  c->SaveAs(label+"_avg.png");

  rms_hist->GetXaxis()->SetTitle("Time Slice");
  rms_hist->GetYaxis()->SetTitle("RMS");
  rms_hist->Draw("hist");

  c->SaveAs(label+"_rms.png");*/

}
