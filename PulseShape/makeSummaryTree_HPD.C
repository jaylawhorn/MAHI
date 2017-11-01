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

//#include "tree.h"

#endif

void makeSummaryTree_HPD(TString infile="/eos/cms/store/user/jlawhorn/October27_PhaseScans/ZeroBias/Run2017F-v1_RAW_20171027_105203/171027_085305/0000/PhaseScan_70.root", 
			 TString outfile="foobie.root") {

  TChain *chain = new TChain("hcalTupleTree/tree");
  chain->AddFile(infile);
  
  vector<vector<float> > *HBHEDigiFC=0;
  vector<int>     *HBHEDigiDepth=0;
  vector<int>     *HBHEDigiIEta=0;
  vector<int>     *HBHEDigiIPhi=0;
  vector<int>     *HBHEDigiSubdet=0;
  vector<vector<int> > *HBHEDigiADC=0;
  UInt_t          bx=0;
  UInt_t          event=0;
  UInt_t          ls=0;
  UInt_t          orbit=0;
  UInt_t          run=0;

  chain->SetBranchAddress("HBHEDigiFC", &HBHEDigiFC);
  chain->SetBranchAddress("HBHEDigiDepth", &HBHEDigiDepth);
  chain->SetBranchAddress("HBHEDigiIEta", &HBHEDigiIEta);
  chain->SetBranchAddress("HBHEDigiIPhi", &HBHEDigiIPhi);
  chain->SetBranchAddress("HBHEDigiSubdet", &HBHEDigiSubdet);
  chain->SetBranchAddress("HBHEDigiADC", &HBHEDigiADC);
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

  TH1D *hPhase = new TH1D("h","h",40,-10,30);

  ifstream ifs;
  ifs.open("phaseScanInfo_HPD.txt");
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
    if (breakPhase.at(xx)==100) continue;

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
    if (breakPhase.at(i)==100) map2master.push_back(-1);
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
    vecM0T.push_back(new TH1D(pname,pname,150,3,6));
    sprintf(pname,"distCharge_%i",breakPhaseMaster.at(xx));
    vecQ.push_back(new TH1D(pname,pname,100,0,500));

  }

  for (uint i=0; i<chain->GetEntries(); i++) {
  //for (uint i=0; i<100; i++) {
    chain->GetEntry(i);
    if (i%1000==0) cout << 100*i/float(chain->GetEntries()) << endl;                                                                                            
    //if (i%100==0) cout << i << endl;
    if (HBHEDigiIEta->size()==0) continue;

    for (uint i=0; i<HBHEDigiFC->size(); i++) {

      double sumFC=0;
      double m0T=0;
      for (uint j=0; j<HBHEDigiFC->at(i).size(); j++) {
	sumFC+=HBHEDigiFC->at(i).at(j);
	m0T+=j*HBHEDigiFC->at(i).at(j);
      }
      m0T/=sumFC;

      if (sumFC<20) continue;

      //cout << "-----" << endl;

      //745015
      uint code=(run-305000)*1000+ls;
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
      if (breakPhase.at(p0)==100) continue;

      if (breakPhase.at(p0)==20) cout << code << " found it!" << endl;

      //if (breakPhase.at(p0)==34) continue;//cout << code << ", " << run << ", " << ls << endl;

      //cout << p0 << ", " << breakPhase.at(p0) << endl;

      int k = map2master.at(p0);
      //cout << k << endl;
      for (uint j=0; j<HBHEDigiFC->at(i).size(); j++) {
	vec.at(k)->Fill(j,HBHEDigiFC->at(i).at(j)/sumFC);
      }

      int tdc_time=-100;

      vecTDC.at(k)->Fill(tdc_time);
      vecM0T.at(k)->Fill(m0T);
      vecQ.at(k)->Fill(sumFC);

    }

  }

  outf->Write();
  outf->Close();

}
