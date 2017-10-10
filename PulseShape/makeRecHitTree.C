#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraphErrors.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <vector>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <iomanip>

//#include "tree.h"

#endif

void makeRecHitTree(TString infile="/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias/Run2017B-v1_RAW_20170621_162843/170621_142916/0000/HcalTupleMaker_100.root", TString outfile="aligned.root") {

  TChain *chain = new TChain("hcalTupleTree/tree");
  chain->AddFile(infile);
  
  cout << chain->GetEntries() << endl;

  vector<float>   *HBHERecHitEnergy=0;
  vector<float>   *HBHERecHitTime=0;
  vector<int>     *HBHERecHitDepth=0;
  vector<int>     *HBHERecHitIEta=0;
  vector<int>     *HBHERecHitIPhi=0;
  UInt_t          bx=0;
  UInt_t          event=0;
  UInt_t          ls=0;
  UInt_t          orbit=0;
  UInt_t          run=0;

  chain->SetBranchAddress("HBHERecHitEnergy", &HBHERecHitEnergy);
  chain->SetBranchAddress("HBHERecHitTime", &HBHERecHitTime);
  chain->SetBranchAddress("HBHERecHitDepth", &HBHERecHitDepth);
  chain->SetBranchAddress("HBHERecHitIEta", &HBHERecHitIEta);
  chain->SetBranchAddress("HBHERecHitIPhi", &HBHERecHitIPhi);
  chain->SetBranchAddress("bx", &bx);
  chain->SetBranchAddress("event", &event);
  chain->SetBranchAddress("ls", &ls);
  chain->SetBranchAddress("orbit", &orbit);
  chain->SetBranchAddress("run", &run);

  TFile *outf = new TFile(outfile,"recreate");

  TH1D* alltiming = new TH1D("alltiming", "alltiming", 50, -25, 25);
  TH1D* alltiming2 = new TH1D("alltiming2", "alltiming2", 50, -25, 25);

  TProfile2D *foo1 = new TProfile2D("depth1","depth1",15,14.5,29.5,4,62.5,66.5);
  TProfile2D *foo2 = new TProfile2D("depth2","depth2",15,14.5,29.5,4,62.5,66.5);
  TProfile2D *foo3 = new TProfile2D("depth3","depth3",15,14.5,29.5,4,62.5,66.5);
  TProfile2D *foo4 = new TProfile2D("depth4","depth4",15,14.5,29.5,4,62.5,66.5);
  TProfile2D *foo5 = new TProfile2D("depth5","depth5",15,14.5,29.5,4,62.5,66.5);
  TProfile2D *foo6 = new TProfile2D("depth6","depth6",15,14.5,29.5,4,62.5,66.5);
  TProfile2D *foo7 = new TProfile2D("depth7","depth7",15,14.5,29.5,4,62.5,66.5);

  for (uint ii=0; ii<chain->GetEntries(); ii++) {
  //for (uint ii=0; ii<10000; ii++) {
    chain->GetEntry(ii);
    //cout << ii << endl;

    if (run!=297101) continue;
    if (bx!=1709) continue; //isolated bunch in run 297101

    if (HBHERecHitEnergy->size()==0) continue;

    if (ii%10000==0) cout << 100*ii/float(chain->GetEntries()) << endl;                                                                                            
    for (uint i=0; i<HBHERecHitEnergy->size(); i++) {

      if (HBHERecHitEnergy->at(i)<5) continue;

      alltiming->Fill(HBHERecHitTime->at(i));

      if (HBHERecHitEnergy->at(i)>10) alltiming2->Fill(HBHERecHitTime->at(i));

      if (HBHERecHitDepth->at(i)==1)      foo1->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==2) foo2->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==3) foo3->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==4) foo4->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==5) foo5->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==6) foo6->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==7) foo7->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );

    }
    
  }
    
  outf->Write();
  outf->Close();

}
