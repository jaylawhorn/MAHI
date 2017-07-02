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

void MakeCovMatrixFromData() {

  TFile *pedf = new TFile("pedestal.root");
  TTree *pedt = (TTree*) pedf->Get("cor");

  double pedAvgTS[10];
  double pedRmsTS[10];
  double pedCovTS[10][10];
  pedt->SetBranchAddress("avgTS",&pedAvgTS);
  pedt->SetBranchAddress("rmsTS",&pedRmsTS);
  pedt->SetBranchAddress("covTS",&pedCovTS);
  pedt->GetEntry(0);

  TFile *f = new TFile("/afs/cern.ch/work/j/jlawhorn/public/Candidacy/CMSSW_9_2_3_patch2/src/MAHI/SkimmedData/Run2017A_ZeroBiasAll.root");
  TTree *it = (TTree*) f->Get("cor");
  if (it == 0) return;

  int bx=0, evt=0, ls=0, orb=0, run=0;
  uint ieta=0, iphi=0, depth=0;
  double sumQ=0;
  double fc[10]={0};
  uint tdc[10]={0};
  double ts[10]={0};

  it->SetBranchAddress("bx",   &bx);
  it->SetBranchAddress("event",&evt);
  it->SetBranchAddress("ls",   &ls);
  it->SetBranchAddress("orbit",&orb);
  it->SetBranchAddress("run",  &run);
  it->SetBranchAddress("ieta", &ieta);
  it->SetBranchAddress("iphi", &iphi);
  it->SetBranchAddress("depth",&depth);
  it->SetBranchAddress("sumQ", &sumQ);
  it->SetBranchAddress("fc",   &fc);
  it->SetBranchAddress("tdc",  &tdc);
  it->SetBranchAddress("ts",   &ts);

  Long64_t nEntries = it->GetEntries();

  Long64_t nHits=0;

  double avgTS[10]={0};
  double rmsTS[10]={0};
  double covTS[10][10]={0};
  double corTS[10][10]={0};

  /*for (int i=0; i<10; i++) { 
    avgTS[i]=0;
    rmsTS[i]=0;

    for (int j=0; j<10; j++) {
      covTS[i][j]=0;
      corTS[i][j]=0;
    }
    }*/

  TFile *of = new TFile("pulse_plain.root","recreate");
  TTree *t = new TTree("cor","");
  
  t->Branch("nHits",&nHits,"nHits/D");
  t->Branch("avgTS",&avgTS,"avgTS[10]/D");
  t->Branch("rmsTS",&rmsTS,"rmsTS[10]/D");
  t->Branch("covTS",&covTS,"covTS[10][10]/D");
  t->Branch("corTS",&corTS,"corTS[10][10]/D");

  for (Long64_t ii=0; ii<nEntries;ii++) {
  //for (Long64_t ii=0; ii<100;ii++) {
    it->GetEntry(ii);

    if (sumQ<20000 || sumQ>25000) continue;

    nHits++;
      
    for (int i=0; i<10; i++) {
      //Double_t qi=fc[i]-pedAvgTS[i];
      Double_t qi=fc[i]/sumQ;
      //cout << "TS" << i << ": " << fc[i] << " - " << pedAvgTS[i] << " = " << qi << endl;
      avgTS[i]+=qi;
      rmsTS[i]+=qi*qi;
      
      for (int j=0; j<i+1; j++) {
	//Double_t qj=fc[j]-pedAvgTS[j];
	Double_t qj=fc[j]/sumQ;
	covTS[i][j]+=qi*qj;
      }
    }
  }
  
  for (int i=0; i<10; i++) {
    avgTS[i]/=nHits;
    rmsTS[i]/=nHits;
    rmsTS[i]=sqrt(rmsTS[i]-avgTS[i]*avgTS[i]);
    cout << i << ": " << avgTS[i] << ", " << rmsTS[i] << endl;
  }

  cout << endl;
  
  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {
      
      covTS[i][j]/=nHits;
      covTS[i][j]-=avgTS[i]*avgTS[j];
      //make correlation matrix
      corTS[i][j]=covTS[i][j]/(rmsTS[i]*rmsTS[j]);
      //if (i==4 || j==4) covTS[i][j]=0;

      covTS[j][i]=covTS[i][j];
      corTS[j][i]=corTS[i][j];

      cout << "array[" << i << "][" << j << "] = " << covTS[i][j] << ";" <<endl;
      cout << "array[" << j << "][" << i << "] = " << covTS[i][j] << ";" <<endl;
      
    }
  }

  t->Fill();
  of->Write();
  of->Close();

}
