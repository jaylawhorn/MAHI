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



  pulse(double t, double q) {
    t_=t;
    q_=q;
    
    //TRandom3 gen(sigh);

    for (int i=0; i<10; i++) {
      v_[i]=0;
      for (int j=0; j<25; j++) {
	v_[i] += q_ * TMath::Landau( 25*i + j, 109.78 - t_, 3.82 );
      }
      //v_[i]+=gen.Gaus(10,10);
    }
  };
  
};


void PulseShape2() {

  double covTSP[10][10]={{0}};
  double covTSM[10][10]={{0}};
  double covTSA[10][10]={{0}};
  
  TH2D* h = new TH2D("h","h",10,0,10,10,0,10);

  pulse cent(0, 100);
  pulse minu(-2, 5000);
  pulse plus(+2, 5000);

  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {

      covTSP[i][j] += ( plus.v_[i] - cent.v_[i] ) * ( plus.v_[j] - cent.v_[j] );
      covTSP[j][i] += ( plus.v_[i] - cent.v_[i] ) * ( plus.v_[j] - cent.v_[j] );

      covTSM[i][j] += ( cent.v_[i] - minu.v_[i] ) * ( cent.v_[j] - minu.v_[j] );
      covTSM[j][i] += ( cent.v_[i] - minu.v_[i] ) * ( cent.v_[j] - minu.v_[j] );

      covTSA[i][j] += 0.5 * ( ( plus.v_[i] - cent.v_[i] ) * ( plus.v_[j] - cent.v_[j] ) +
			      ( cent.v_[i] - minu.v_[i] ) * ( cent.v_[j] - minu.v_[j] ) );
      covTSA[j][i] += 0.5 * ( ( plus.v_[i] - cent.v_[i] ) * ( plus.v_[j] - cent.v_[j] ) +
			      ( cent.v_[i] - minu.v_[i] ) * ( cent.v_[j] - minu.v_[j] ) );
    }
  }

  for (int i=0; i<10; i++) {
    for (int j=0; j<i+1; j++) {

      if (covTSA[i][i]==0 || covTSA[j][j]==0) {
	h->SetBinContent(h->GetBin(i+1,j+1), 0);
	h->SetBinContent(h->GetBin(j+1,i+1), 0);
      }
      else {
	h->SetBinContent(h->GetBin(i+1,j+1),covTSA[i][j]/sqrt(covTSA[i][i])/sqrt(covTSA[j][j]) );
	h->SetBinContent(h->GetBin(j+1,i+1),covTSA[j][i]/sqrt(covTSA[i][i])/sqrt(covTSA[j][j]) );
      }
      
    }
  }
  
  //TCanvas *c = new TCanvas("c", "c", 800, 600);
  
  //dumber1->SetLineColor(kRed);
  //dumbest1->SetLineColor(kBlue);

  //dumb->Draw();

  //h->GetZaxis()->SetRange(-1,1);

  h->Draw("colz text");
  //dumber1->Draw("hist same");
  //dumbest1->Draw("hist same");

}
