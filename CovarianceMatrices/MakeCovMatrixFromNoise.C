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

void MakeCovMatrixFromNoise(
			    TString baseDir="/afs/cern.ch/work/j/jlawhorn/public/CMSSW_9_2_10/src/MAHI",
			    TString fn="NonZS_304797"
			    ) {

  TTree *it;

  TFile *f = new TFile(baseDir+"/SkimmedData/"+fn+"_small.root");
  it = (TTree*) f->Get("cor");
  if (it == 0) return;

  uint bx=0, evt=0, ls=0, orb=0, run=0;
  int ieta=0, iphi=0, depth=0;
  double sumQ=0;
  double fc[10];
  uint tdc[10];
  double ts[10];

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

  double avgTS[10];
  double rmsTS[10];
  double covTS[10][10];
  double corTS[10][10];

  for (int i=0; i<10; i++) { 
    avgTS[i]=0;
    rmsTS[i]=0;

    for (int j=0; j<10; j++) {
      covTS[i][j]=0;
      corTS[i][j]=0;
    }
  }

  TFile *of = new TFile(baseDir+"/CovarianceMatrixFiles/"+fn+".root","recreate");
  TTree *t = new TTree("cor","");
  
  t->Branch("nHits",&nHits,"nHits/D");
  t->Branch("avgTS",&avgTS,"avgTS[10]/D");
  t->Branch("rmsTS",&rmsTS,"rmsTS[10]/D");
  t->Branch("covTS",&covTS,"covTS[10][10]/D");
  t->Branch("corTS",&corTS,"corTS[10][10]/D");

  for (Long64_t ii=0; ii<nEntries;ii++) {
    it->GetEntry(ii);
    
    nHits++;
      
    for (int i=0; i<10; i++) {
      
      Double_t qi=fc[i];
      avgTS[i]+=qi;
      rmsTS[i]+=qi*qi;
      
      for (int j=0; j<i+1; j++) {
	Double_t qj=fc[j];
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
      covTS[j][i] = covTS[i][j];
      //make correlation matrix
      corTS[i][j]=covTS[i][j]/(rmsTS[i]*rmsTS[j]);

      corTS[j][i] = corTS[i][j];
      
      cout << "array[" << i << "][" << j << "] = " << covTS[i][j] << ";" <<endl;
      cout << "array[" << j << "][" << i << "] = " << covTS[i][j] << ";" <<endl;
      
    }
  }

  t->Fill();
  of->Write();
  of->Close();

}
