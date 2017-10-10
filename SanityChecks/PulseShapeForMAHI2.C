#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
#include <TSystem.h>                      // interface to OS
#include <TStyle.h>                       // class to handle ROOT plotting styles
#include <TFile.h>                        // file handle class
#include <TTree.h>                        // class to access ntuples
#include <TChain.h>                        // class to access ntuples
#include <TH1D.h>
#include <TProfile.h>
#include <TH2D.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TMath.h>
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

class pulse {
  
public:
  double t_;
  double q_;
  double v_[10];

  pulse(double t, double q, double sigh) {
    t_=t;
    q_=q;

    v_[0] = 0;
    v_[1] = 0;
    v_[2] = 0;
    v_[3] = 0.000665497 + 0.00129145 * t_; 
    v_[4] = 0.740754 + 0.0136219 * t_;
    v_[5] = 0.173375 + -0.0121246 * t_;
    v_[6] = 0.0464181 + -0.00187305 * t_; 
    v_[7] = 0.0203793 + -0.000561543 * t_; 
    v_[8] = 0.0112839 + -0.000235044 * t_; 
    v_[9] = 0.00712438 + -0.000119167 * t_; 
    
    TRandom3 gen(sigh);
    double temp_=0;
    for (int i=0; i<10; i++) temp_+=v_[i];

    for (int i=0; i<10; i++) {
      v_[i] = gen.Gaus(q_ * v_[i] / temp_ , noise( q_ * v_[i] / temp_) );
      
    }

  };

    double noise(double ifC) {
      double sigma = 0;
      if(ifC < 75) sigma = (0.577 + 0.0686*ifC)/3.; 
      else sigma = (2.75  + 0.0373*ifC + 3e-6*ifC*ifC)/3.; 

      double sigma2 = ifC/sqrt(ifC/0.3305);
      if (ifC<1) sigma2=1/sqrt(1/0.3305);

      return sqrt(1 + sigma*sigma + sigma2*sigma2);
    };

};


void PulseShapeForMAHI2() {

  TCanvas *c = new TCanvas("c","",800, 800);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(55);
  gStyle->SetPaintTextFormat("2.2f");

  int n=10000000;

  double avgTS[10]={0};
  double rmsTS[10]={0};
  double covTS[10][10]={{0}};
  
  TH1D *q = new TH1D("q","q",40, 4000, 12000);

  TH2D* h = new TH2D("h","h",10,-0.5,9.5,10,-0.5,9.5);

  TRandom3 * gen = new TRandom3(479);

  for (int x=0; x<n; x++) {

    double a=gen->Rndm();

    pulse temp(gen->Gaus(0, 1), a*a*5000+5000, gen->Rndm()*1000);

    double sumQ = 0;
    for (int i=0; i<10; i++) sumQ+=temp.v_[i]; 

    q->Fill(sumQ);

    for (int i=0; i<10; i++) {
      double qi = temp.v_[i]/sumQ;

      //dumb->Fill(i, qi*qi);
    
      avgTS[i]+=qi;
      rmsTS[i]+=qi*qi;

      for (int j=0; j<10; j++) {
	double qj = temp.v_[j]/sumQ;
	covTS[i][j]+=qi*qj;
      }
    }
  }

  for (int i=0; i<10; i++) {
    avgTS[i]/=n;
    rmsTS[i]/=n;
    rmsTS[i]-=avgTS[i]*avgTS[i];
    rmsTS[i]=sqrt(rmsTS[i]);
  }
  
  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {
      covTS[i][j]/=n;
      covTS[i][j]-=avgTS[i]*avgTS[j];
      
      //cout << covTS[i][j] << endl;

      if (i==j) cout << covTS[i][j] << ", " << sqrt(rmsTS[i]*rmsTS[j]) << endl;

      h->SetBinContent(h->GetBin(i+1,j+1),covTS[i][j]/rmsTS[i]/rmsTS[j]);
      h->SetBinContent(h->GetBin(j+1,i+1),covTS[i][j]/rmsTS[i]/rmsTS[j]);
      
    }
  }
  
  //TCanvas *c = new TCanvas("c", "c", 800, 600);
  
  //dumber1->SetLineColor(kRed);
  //dumbest1->SetLineColor(kBlue);

  //dumb->Draw();

  //q->Draw("hist");
  h->GetZaxis()->SetRange(-1,1);

  h->Draw("colz text");
  //dumber1->Draw("hist same");
  //dumbest1->Draw("hist same");

}
