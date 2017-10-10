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
#include <fstream> 
#include <sstream> 
#include <iomanip>

#include "tree.h"

#endif

void makeSummaryTree_ByLS(TString outfile="foobie.root") {


  TChain *chain = new TChain("hcalTupleTree/tree");
  chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias1.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias2.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias3.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias4.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias5.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias6.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias7.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias8.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias9.root");

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

  vector<int> breakRun;
  vector<int> breakLS;
  vector<int> breakCode;
  vector<int> breakPhase;
  vector<int> breakPhaseMaster;

  TH1D *hPhase = new TH1D("h","h",100,0,100);

  ifstream ifs;
  ifs.open("phaseScanInfo.txt");
  assert(ifs.is_open());
  string line;
  while(getline(ifs,line)) {
    if (line[0]=='#') continue;

    int RUN; 
    int LS;
    int CODE;
    int PHASE;
    stringstream ss(line);
    ss >> RUN >> LS >> CODE >> PHASE;
    breakRun.push_back(RUN);
    breakLS.push_back(LS);
    breakCode.push_back(CODE);
    breakPhase.push_back(PHASE);
    hPhase->Fill(PHASE);

  }

  vector<int> map2master;

  for (uint xx=0; xx<breakPhase.size(); xx++) {
    if (breakPhase.at(xx)==0) continue;

    else if (breakPhaseMaster.size()==0) breakPhaseMaster.push_back(breakPhase.at(xx));
    else {
      int found=0;
      for (uint yy=0; yy<breakPhaseMaster.size(); yy++) {
	if (breakPhase.at(xx) == breakPhaseMaster.at(yy)) {
	  found=1;
	  break;
	}
      }
      if (found==0) breakPhaseMaster.push_back(breakPhase.at(xx));
    }
  }

  sort( breakPhaseMaster.begin(), breakPhaseMaster.end() );

  for (uint i=0; i<breakPhaseMaster.size(); i++) {
    cout << breakPhaseMaster.at(i) << ", ";
  }
  cout << endl << endl;

  for (uint i=0; i<breakPhase.size(); i++) {
    if (breakPhase.at(i)==0) map2master.push_back(-1);
    else {
      for (uint j=0; j<breakPhaseMaster.size(); j++) {
	if (breakPhase.at(i)==breakPhaseMaster.at(j)) {
	  map2master.push_back(j);
	  break;
	}
      }
    }
  }

  vector<TProfile *> vec;
  vector<TH1D *> vecTDC;
  vector<TH1D *> vecM0T;
  vector<TH1D *> vecQ;

  for (uint xx=0; xx<breakPhaseMaster.size(); xx++) {
    char pname[50];
    sprintf(pname,"avgPulse_%i",breakPhaseMaster.at(xx));
    vec.push_back(new TProfile(pname,pname,10,-0.5,9.5));
    sprintf(pname,"distTDC_%i",breakPhaseMaster.at(xx));
    vecTDC.push_back(new TH1D(pname,pname,120,-50,70));
    sprintf(pname,"distM0T_%i",breakPhaseMaster.at(xx));
    vecM0T.push_back(new TH1D(pname,pname,100,4,6));
    sprintf(pname,"distCharge_%i",breakPhaseMaster.at(xx));
    vecQ.push_back(new TH1D(pname,pname,100,0,50000));

  }

  for (uint i=0; i<chain->GetEntries(); i++) {
    //for (uint i=10000; i<10100; i++) {
    chain->GetEntry(i);
    if (i%1000000==0) cout << 100*i/float(chain->GetEntries()) << endl;                                                                                            
    if (QIE11DigiIEta->size()==0) continue;

    for (uint i=0; i<QIE11DigiFC->size(); i++) {

      double sumFC=0;
      double m0T=0;
      for (uint j=0; j<QIE11DigiFC->at(i).size(); j++) {
	sumFC+=QIE11DigiFC->at(i).at(j);
	m0T+=j*QIE11DigiFC->at(i).at(j);
      }
      m0T/=sumFC;

      if (sumFC<5000) continue;

      //cout << "-----" << endl;

      uint code=(run-294000)*1000+ls;
      //cout << run << ", " << ls << ", " << code << endl;

      int p0=-1;
      for (uint xx=0; xx<breakCode.size(); xx++) {
	//cout <<"!!!!! " << xx << " " << code << " " << breakCode.at(xx)  << endl;
	if (p0==-1 && code<breakCode.at(xx)) {
	  if (xx!=0 && code==breakCode.at(xx-1)) break;
	  //cout << "!!!!! " << xx << " " << code << " " << breakCode.at(xx) << endl;
	  p0=xx-1;
	  break;
	}
      }
      //cout<< "i survivvvvvved " << p0 << endl;
      if (p0==-1) continue;
      if (breakPhase.at(p0)==0) continue;

      //if (breakPhase.at(p0)==34) continue;//cout << code << ", " << run << ", " << ls << endl;

      //cout << p0 << ", " << breakPhase.at(p0) << endl;

      int k = map2master.at(p0);
      //cout << k << endl;
      for (uint j=0; j<QIE11DigiFC->at(i).size(); j++) {
	vec.at(k)->Fill(j,QIE11DigiFC->at(i).at(j)/sumFC);
      }

      int tdc_time=-100;
      if (QIE11DigiTDC->at(i).at(4)!=62) tdc_time=QIE11DigiTDC->at(i).at(4);
      else if (QIE11DigiTDC->at(i).at(3)<60) tdc_time=QIE11DigiTDC->at(i).at(3)-50;

      vecTDC.at(k)->Fill(tdc_time);
      vecM0T.at(k)->Fill(m0T);
      vecQ.at(k)->Fill(sumFC);

    }

  }

  outf->Write();
  outf->Close();

}
