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

void makeRecHitTree_ByLS(TString infile="root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_10.root", TString outfile="test2.root") {

  TChain *chain = new TChain("hcalTupleTree/tree");
  chain->AddFile(infile);
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_1.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_31.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_50.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_69.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_10.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_32.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_51.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_70.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_11.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_33.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_52.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_71.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_12.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_34.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_53.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_72.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_13.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_35.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_54.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_73.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_14.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_36.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_55.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_74.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_15.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_37.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_56.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_75.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_16.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_39.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_57.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_76.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_17.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_4.root ");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_58.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_77.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_18.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_40.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_59.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_78.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_19.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_41.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_6.root");   
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_79.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_2.root");   
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_42.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_60.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_8.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_20.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_43.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_61.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_80.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_21.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_44.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_62.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_81.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_22.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_45.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_63.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_82.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_23.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_46.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_64.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_83.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_26.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_47.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_65.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_9.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_28.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_48.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_66.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_3.root");   
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_49.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_67.root");
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_30.root");  
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_5.root");   
  //chain->AddFile("root://eoscms//store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170607_062653/170607_042824/0000/HcalTupleMaker_68.root");
  
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

  //for (uint i=0; i<breakPhaseMaster.size(); i++) {
  // cout << breakPhaseMaster.at(i) << ", ";
  //}
  //cout << endl << endl;

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


  TH1D *foo = new TH1D("foo", "foo",100, -50, 50);
  TProfile2D *foo1 = new TProfile2D("test1","test1",12,17.5,29.5,4,62.5,66.5);
  TProfile2D *foo2 = new TProfile2D("test2","test2",12,17.5,29.5,4,62.5,66.5);
  TProfile2D *foo3 = new TProfile2D("test3","test3",12,17.5,29.5,4,62.5,66.5);
  TProfile2D *foo4 = new TProfile2D("test4","test4",12,17.5,29.5,4,62.5,66.5);
  TProfile2D *foo5 = new TProfile2D("test5","test5",12,17.5,29.5,4,62.5,66.5);
  TProfile2D *foo6 = new TProfile2D("test6","test6",12,17.5,29.5,4,62.5,66.5);
  TProfile2D *foo7 = new TProfile2D("test7","test7",12,17.5,29.5,4,62.5,66.5);

  vector<TProfile2D *> vec1;
  vector<TProfile2D *> vec2;
  vector<TProfile2D *> vec3;
  vector<TProfile2D *> vec4;
  vector<TProfile2D *> vec5;
  vector<TProfile2D *> vec6;
  vector<TProfile2D *> vec7;

  for (uint xx=0; xx<breakPhaseMaster.size(); xx++) {
    char pname[50];
    sprintf(pname,"depth_1_%i",breakPhaseMaster.at(xx));
    vec1.push_back(new TProfile2D(pname,pname,12,17.5,29.5,4,62.5,66.5));
    sprintf(pname,"depth_2_%i",breakPhaseMaster.at(xx));
    vec2.push_back(new TProfile2D(pname,pname,12,17.5,29.5,4,62.5,66.5));
    sprintf(pname,"depth_3_%i",breakPhaseMaster.at(xx));
    vec3.push_back(new TProfile2D(pname,pname,12,17.5,29.5,4,62.5,66.5));
    sprintf(pname,"depth_4_%i",breakPhaseMaster.at(xx));
    vec4.push_back(new TProfile2D(pname,pname,12,17.5,29.5,4,62.5,66.5));
    sprintf(pname,"depth_5_%i",breakPhaseMaster.at(xx));
    vec5.push_back(new TProfile2D(pname,pname,12,17.5,29.5,4,62.5,66.5));
    sprintf(pname,"depth_6_%i",breakPhaseMaster.at(xx));
    vec6.push_back(new TProfile2D(pname,pname,12,17.5,29.5,4,62.5,66.5));
    sprintf(pname,"depth_7_%i",breakPhaseMaster.at(xx));
    vec7.push_back(new TProfile2D(pname,pname,12,17.5,29.5,4,62.5,66.5));

  }


  for (uint ii=0; ii<chain->GetEntries(); ii++) {
  //for (uint ii=0; ii<10000; ii++) {
    chain->GetEntry(ii);
    //cout << ii << endl;

    if (HBHERecHitEnergy->size()==0) continue;

    uint code=(run-294000)*1000+ls;

    int p0=-1;
    for (uint xx=0; xx<breakCode.size(); xx++) {
      if (p0==-1 && code<breakCode.at(xx)) {
	if (xx!=0 && code==breakCode.at(xx-1)) break;
	p0=xx-1;
	break;
      }
    }
    if (p0==-1) continue;
    if (breakPhase.at(p0)==0) continue;
    
    if (ii%10000==0) cout << 100*ii/float(chain->GetEntries()) << endl;                                                                                            
    for (uint i=0; i<HBHERecHitEnergy->size(); i++) {

      if (HBHERecHitEnergy->at(i)<2) continue;
      //cout << HBHERecHitEnergy->at(i) << endl;
      int k = map2master.at(p0);

      foo->Fill(HBHERecHitTime->at(i));

      if (HBHERecHitDepth->at(i)==1) foo1->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==2) foo2->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==3) foo3->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==4) foo4->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==5) foo5->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==6) foo6->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );
      else if (HBHERecHitDepth->at(i)==7) foo7->Fill( HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i) );

      if (HBHERecHitDepth->at(i)==1) vec1.at(k)->Fill(HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i));
      else if (HBHERecHitDepth->at(i)==2) vec2.at(k)->Fill(HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i));
      else if (HBHERecHitDepth->at(i)==3) vec3.at(k)->Fill(HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i));
      else if (HBHERecHitDepth->at(i)==4) vec4.at(k)->Fill(HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i));
      else if (HBHERecHitDepth->at(i)==5) vec5.at(k)->Fill(HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i));
      else if (HBHERecHitDepth->at(i)==6) vec6.at(k)->Fill(HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i));
      else if (HBHERecHitDepth->at(i)==7) vec7.at(k)->Fill(HBHERecHitIEta->at(i), HBHERecHitIPhi->at(i), HBHERecHitTime->at(i));

    }
    
  }
    
  outf->Write();
  outf->Close();

}
