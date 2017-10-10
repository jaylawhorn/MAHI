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
#include <TCanvas.h>
#include <TLegend.h>
#include <vector>
#include <iostream>
#include <iomanip>

//#include "tree.h"

#endif

void makeSummaryTree_ByTDC(TString outfile="sortedByTDC.root") {


  TChain *chain = new TChain("hcalTupleTree/tree");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias10.root");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias1.root");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias2.root");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias3.root");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias4.root");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias5.root");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias6.root");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias7.root");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias8.root");
  chain->AddFile("/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/processed/ZeroBias9.root");

  vector<vector<double> > *QIE11DigiFC=0;
  Int_t           laserType=0;
  vector<int>     *QIE11DigiCapIDError=0;
  vector<int>     *QIE11DigiDepth=0;
  vector<int>     *QIE11DigiFlags=0;
  vector<int>     *QIE11DigiIEta=0;
  vector<int>     *QIE11DigiIPhi=0;
  vector<int>     *QIE11DigiLinkError=0;
  vector<int>     *QIE11DigiRawID=0;
  vector<int>     *QIE11DigiSubdet=0;
  vector<vector<int> > *QIE11DigiADC=0;
  vector<vector<int> > *QIE11DigiCapID=0;
  vector<vector<int> > *QIE11DigiSOI=0;
  vector<vector<int> > *QIE11DigiTDC=0;
  UInt_t          bx=0;
  UInt_t          event=0;
  UInt_t          ls=0;
  UInt_t          orbit=0;
  UInt_t          run=0;

  chain->SetBranchAddress("QIE11DigiFC", &QIE11DigiFC);
  chain->SetBranchAddress("laserType", &laserType);
  chain->SetBranchAddress("QIE11DigiCapIDError", &QIE11DigiCapIDError);
  chain->SetBranchAddress("QIE11DigiDepth", &QIE11DigiDepth);
  chain->SetBranchAddress("QIE11DigiFlags", &QIE11DigiFlags);
  chain->SetBranchAddress("QIE11DigiIEta", &QIE11DigiIEta);
  chain->SetBranchAddress("QIE11DigiIPhi", &QIE11DigiIPhi);
  chain->SetBranchAddress("QIE11DigiLinkError", &QIE11DigiLinkError);
  chain->SetBranchAddress("QIE11DigiRawID", &QIE11DigiRawID);
  chain->SetBranchAddress("QIE11DigiSubdet", &QIE11DigiSubdet);
  chain->SetBranchAddress("QIE11DigiADC", &QIE11DigiADC);
  chain->SetBranchAddress("QIE11DigiCapID", &QIE11DigiCapID);
  chain->SetBranchAddress("QIE11DigiSOI", &QIE11DigiSOI);
  chain->SetBranchAddress("QIE11DigiTDC", &QIE11DigiTDC);
  chain->SetBranchAddress("bx", &bx);
  chain->SetBranchAddress("event", &event);
  chain->SetBranchAddress("ls", &ls);
  chain->SetBranchAddress("orbit", &orbit);
  chain->SetBranchAddress("run", &run);

  TFile *outf = new TFile(outfile,"recreate");

  vector<TProfile *> v_p4;
  vector<TProfile *> v_p3;

  for (int i=0; i<50; i++) {
    char pname[10];
    sprintf(pname,"p4_%i",i);
    v_p4.push_back(new TProfile(pname,pname,10,-0.5,9.5,"e")); v_p4[i]->Sumw2();
    sprintf(pname,"p3_%i",i);
    v_p3.push_back(new TProfile(pname,pname,10,-0.5,9.5,"e")); v_p3[i]->Sumw2();
  }

  for (UInt_t i=0; i<chain->GetEntries(); i++) {
  //for (UInt_t i=0; i<10000; i++) {
    chain->GetEntry(i);

    if (i%1000000==0) cout << 100*i/float(chain->GetEntries()) << endl;

    if (QIE11DigiIEta->size()==0) continue;

    for (uint i=0; i<QIE11DigiFC->size(); i++) {

      double sumFC=0;
      for (uint j=0; j<QIE11DigiFC->at(i).size(); j++) {
	sumFC+=QIE11DigiFC->at(i).at(j);
      }
      if (sumFC<5000) continue;
      //if (sumFC<10000) continue;

      if (QIE11DigiTDC->at(i).at(4)<60) {	
	int tdc_time=QIE11DigiTDC->at(i).at(4);
	for (uint j=0; j<QIE11DigiFC->at(i).size(); j++) {
	  v_p4.at(tdc_time)->Fill(j,QIE11DigiFC->at(i).at(j)/sumFC);
	  //v_p4.at(tdc_time)->Fill(j,QIE11DigiFC->at(i).at(j));
	}
      }
      else if (QIE11DigiTDC->at(i).at(4)==62 && QIE11DigiTDC->at(i).at(3)<60) {
	int tdc_time=QIE11DigiTDC->at(i).at(3);
        for (uint j=0; j<QIE11DigiFC->at(i).size(); j++) {
          v_p3.at(tdc_time)->Fill(j,QIE11DigiFC->at(i).at(j)/sumFC);
	}
	
      }
    }

  }


  outf->Write();
  outf->Close();

}
