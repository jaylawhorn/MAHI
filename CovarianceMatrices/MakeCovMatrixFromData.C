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

struct covStruct {
  covStruct() :
    nHits(0)
    //avgTS({0}), 
    //rmsTS({0}),
    //covTS({{0}}) 
  {
    for (int i=0; i<10; i++) {
      avgTS[i]=0; rmsTS[i]=0;
      for (int j=0; j<10; j++) {
	covTS[i][j]=0;
      }
    }
  }

  int nHits;
  double avgTS[10];
  double rmsTS[10];
  double covTS[10][10];

};

void MakeCovMatrixFromData(
			   TString baseDir="/afs/cern.ch/work/j/jlawhorn/public/CMSSW_9_2_10/src/MAHI",
			   TString fn="Data_ZeroBias_2017A_Collisions"
			   ) {

  TTree *it;

  cout << baseDir+"/SkimmedData/"+fn+"_skim.root" << endl;

  TFile *f = new TFile(baseDir+"/SkimmedData/"+fn+"_skim.root");
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

  double avgTS[10] = {0};
  double rmsTS[10] = {0};
  double covTS[10][10] = {{0}};

  TFile *of = new TFile(baseDir+"/CovarianceMatrixFiles/"+fn+".root","recreate");
  TTree *t = new TTree("cor","");
  
  t->Branch("nHits",&nHits,"nHits/D");
  t->Branch("avgTS",&avgTS,"avgTS[10]/D");
  t->Branch("rmsTS",&rmsTS,"rmsTS[10]/D");
  t->Branch("covTS",&covTS,"covTS[10][10]/D");

  const int nBins=5;

  double binBounds[nBins+1] = {0, 2000, 4000, 6000, 10000, 20000}; 

  std::vector<covStruct> binned;

  for (int i=0; i<nBins; i++) {
    binned.push_back(covStruct());
    //cout << binned[0].avgTS[0] << endl;
  }

  cout << nEntries << endl;

  for (Long64_t ii=0; ii<nEntries; ii++) {
    //for (Long64_t ii=0; ii<10000;ii++) {
    it->GetEntry(ii);

    //if (ii%100==0 && ii>3088000) {
    //  cout << ii << endl;
    //  cout << sumQ << endl;
    //}
    
    //if (sumQ<2000) continue;
    
    int iBin=-1;
    for (int j=0; j<nBins; j++) {
      if (sumQ>binBounds[j] && sumQ<binBounds[j+1]) iBin=j;  
    }
    //cout << sumQ << ", " << iBin << endl;
    if (iBin==-1) continue;

    binned[iBin].nHits++;
      
    for (int i=0; i<10; i++) {
      
      Double_t qi=fc[i];
      binned[iBin].avgTS[i]+=qi;
      binned[iBin].rmsTS[i]+=qi*qi;
      
      for (int j=0; j<i+1; j++) {
	Double_t qj=fc[j];
	binned[iBin].covTS[i][j]+=qi*qj;
      }
    }
  }
  //cout << "??" << endl;
  for (int iBin=0; iBin<nBins; iBin++) {
    for (int i=0; i<10; i++) {
      binned[iBin].avgTS[i]/=binned[iBin].nHits;
      binned[iBin].rmsTS[i]/=binned[iBin].nHits;
      binned[iBin].rmsTS[i]=sqrt(binned[iBin].rmsTS[i]-binned[iBin].avgTS[i]*binned[iBin].avgTS[i]);

      avgTS[i] = binned[iBin].avgTS[i];
      rmsTS[i] = binned[iBin].rmsTS[i];

      //cout << i << ": " << binned[iBin].avgTS[i] << ", " << binned[iBin].rmsTS[i] << endl;
    }
    //cout << endl;
  
    for (int i=0; i<10; i++) {
      for (int j=0; j<i+1; j++) {
	
	binned[iBin].covTS[i][j]/=binned[iBin].nHits;
	binned[iBin].covTS[i][j]-=binned[iBin].avgTS[i]*binned[iBin].avgTS[j];
	binned[iBin].covTS[j][i] = binned[iBin].covTS[i][j];

	covTS[i][j] = binned[iBin].covTS[i][j];
	covTS[j][i] = binned[iBin].covTS[j][i];
	//make correlation matrix
	//binned[iBin].corTS[i][j]=covTS[i][j]/(rmsTS[i]*rmsTS[j]);
	//corTS[j][i] = corTS[i][j];
	
	//cout << "array[" << i << "][" << j << "] = " << covTS[i][j] << ";" <<endl;
	//cout << "array[" << j << "][" << i << "] = " << covTS[i][j] << ";" <<endl;
      }
    }
    t->Fill();
  }

  of->Write();
  of->Close();

}
