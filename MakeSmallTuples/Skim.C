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

void Skim(//TString ifn="/afs/cern.ch/work/j/jlawhorn/public/CMSSW_9_2_10/src/HCALPFG/HcalTupleMaker/pedestal.root",
	  //TString ofn="pedestal_small.root") {
	  TString ifn="/eos/cms/store/user/jlawhorn/HEP17_TIMED_IN/ZeroBias_2017A_part.root",
	  TString ofn="ZeroBias_2017A_small.root") {

  TTree *fChain;

  //TFile *f = new TFile("testHTMHT.root");
  TFile *f = new TFile(ifn);
  fChain = (TTree*) f->Get("hcalTupleTree/tree");
  if (fChain == 0) return;

  vector<vector<double> > *QIE11DigiFC=0;
  vector<int>     *QIE11DigiDepth=0;
  vector<int>     *QIE11DigiIEta=0;
  vector<int>     *QIE11DigiIPhi=0;
  vector<vector<int> > *QIE11DigiADC=0;
  vector<vector<int> > *QIE11DigiTDC=0;
  UInt_t          bx=0;
  UInt_t          event=0;
  UInt_t          ls=0;
  UInt_t          orbit=0;
  UInt_t          run=0;

  fChain->SetBranchAddress("QIE11DigiFC", &QIE11DigiFC);
  fChain->SetBranchAddress("QIE11DigiDepth", &QIE11DigiDepth);
  fChain->SetBranchAddress("QIE11DigiIEta", &QIE11DigiIEta);
  fChain->SetBranchAddress("QIE11DigiIPhi", &QIE11DigiIPhi);
  fChain->SetBranchAddress("QIE11DigiADC", &QIE11DigiADC);
  fChain->SetBranchAddress("QIE11DigiTDC", &QIE11DigiTDC);
  fChain->SetBranchAddress("bx", &bx);
  fChain->SetBranchAddress("event", &event);
  fChain->SetBranchAddress("ls", &ls);
  fChain->SetBranchAddress("orbit", &orbit);
  fChain->SetBranchAddress("run", &run);

  Long64_t nEntries = fChain->GetEntries();

  TFile *of = new TFile(ofn,"recreate");
  TTree *t = new TTree("cor","");

  uint bx1=0, evt1=0, ls1=0, orb1=0, run1=0;
  int ieta=0, iphi=0, depth=0;
  double sumQ=0;
  double fc[10];
  uint tdc[10];
  double ts[10];

  for (int i=0; i<10; i++) {
    fc[i]=0;
    tdc[i]=0;
    ts[i]=i;
  }
  
  t->Branch("bx",   &bx1,  "bx/i");
  t->Branch("event",&evt1, "evt/i");
  t->Branch("ls",   &ls1,  "ls/i");
  t->Branch("orbit",&orb1, "orbit/i");
  t->Branch("run",  &run1, "run/i");
  t->Branch("ieta", &ieta, "ieta/I");
  t->Branch("iphi", &iphi, "iphi/I");
  t->Branch("depth",&depth,"depth/I");
  t->Branch("sumQ", &sumQ, "sumQ/D");
  t->Branch("fc",   &fc,   "fc[10]/D");
  t->Branch("tdc",  &tdc,  "tdc[10]/I");
  t->Branch("ts",   &ts,   "ts[10]/D");

  for (Long64_t ii=0; ii<nEntries;ii++) {
  //for (Long64_t ii=0; ii<1000;ii++) {
    fChain->GetEntry(ii);
    
    for (uint k=0; k<QIE11DigiIEta->size(); k++) {

      sumQ=0;
      for (UInt_t j=0; j<10; j++) { sumQ+=QIE11DigiFC->at(k).at(j);}
      
      //if (sumQ<2000) continue;

      bx1=bx;
      evt1=event;
      ls1=ls;
      orb1=orbit;
      run1=run;
      ieta=QIE11DigiIEta->at(k);
      iphi=QIE11DigiIPhi->at(k);
      depth=QIE11DigiDepth->at(k);

      for (int i=0; i<10; i++) {
	fc[i] = QIE11DigiFC->at(k).at(i);
	tdc[i] = QIE11DigiTDC->at(k).at(i);
      }

      t->Fill();
    }
  }


  of->Write();
  of->Close();

}
