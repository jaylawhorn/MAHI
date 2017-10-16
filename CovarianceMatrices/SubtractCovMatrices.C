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

void SubtractCovMatrices() {
  
  TFile *f1 = new TFile("/afs/cern.ch/work/j/jlawhorn/public/CMSSW_9_2_10/src/MAHI/CovarianceMatrixFiles/Data_ZeroBias_2017A_Collisions.root");
  TTree *t1 = (TTree*) f1->Get("cor");
  
  double AvgTS1[10];
  double RmsTS1[10];
  double CovTS1[10][10];
  t1->SetBranchAddress("avgTS",&AvgTS1);
  t1->SetBranchAddress("rmsTS",&RmsTS1);
  t1->SetBranchAddress("covTS",&CovTS1);
  t1->GetEntry(0);
  
  TFile *f2 = new TFile("/afs/cern.ch/work/j/jlawhorn/public/CMSSW_9_2_10/src/MAHI/CovarianceMatrixFiles/MC_ZS_NuGun_Collisions.root");
  TTree *t2 = (TTree*) f2->Get("cor");
  
  double AvgTS2[10];
  double RmsTS2[10];
  double CovTS2[10][10];
  t2->SetBranchAddress("avgTS",&AvgTS2);
  t2->SetBranchAddress("rmsTS",&RmsTS2);
  t2->SetBranchAddress("covTS",&CovTS2);
  t2->GetEntry(0);
  
  TFile *f3 = new TFile("test2.root","recreate");
  TTree *t3 = new TTree("cor","");
  
  double AvgTS3[10]={0};
  double RmsTS3[10]={0};
  double CovTS3[10][10]={{0}};
  double CorTS3[10][10]={{0}};
  
  t3->Branch("avgTS",&AvgTS3,"avgTS[10]/D");
  t3->Branch("rmsTS",&RmsTS3,"rmsTS[10]/D");
  t3->Branch("covTS",&CovTS3,"covTS[10][10]/D");
  t3->Branch("corTS",&CorTS3,"corTS[10][10]/D");
  
  for (int i=0; i<10; i++) {
    //cout << i << ": " << AvgTS1[i] << " - " << AvgTS2[i] << " = " << AvgTS1[i] - AvgTS2[i] << endl;
    AvgTS3[i] = AvgTS1[i] - AvgTS2[i];

    //cout << i << ": " << RmsTS1[i] << " - " << RmsTS2[i] << " = " << RmsTS1[i] - RmsTS2[i] << endl;
    RmsTS3[i] = sqrt(RmsTS1[i]*RmsTS1[i] - RmsTS2[i]*RmsTS2[i]);
    for (int j=0; j<i+1; j++) {
      //cout << i << ", " << j << ": " << CovTS1[i][j] << " - " << CovTS2[i][j] << " = " << CovTS1[i][j] - CovTS2[i][j] << endl;

      CovTS3[i][j] = CovTS1[i][j] - CovTS2[i][j];
      CovTS3[j][i] = CovTS1[i][j] - CovTS2[i][j];
    }
  }


  for (int i=0; i<10; i++) {
    cout << CovTS3[i][i] << ", " << RmsTS3[i]*RmsTS3[i] << endl;
	
    for (int j=0; j<i+1; j++) {
      CorTS3[i][j] = CovTS3[i][j]/RmsTS3[i]/RmsTS3[j];
      CorTS3[j][i] = CovTS3[i][j]/RmsTS3[i]/RmsTS3[j];

    }
  }
  
  t3->Fill();
  f3->Write();
  f3->Close();
  
}
