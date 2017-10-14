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
  double p_[10];

  pulse(double t, double q, double sigh) {
    t_=t;
    q_=q;
    
    TRandom3 gen(sigh);

    double temp_=0;

    double tempPed_[10]={0};

    for (int j=0; j<10; j++) {
      tempPed_[j]=gen.Gaus(1,1);
      p_[j]=0;
    }

    for (int i=0; i<10; i++) {
      p_[i]+=15*tempPed_[i];
      if (i!=0) p_[i]+=3.2*tempPed_[i-1];
      //if (i!=9) p_[i]+=3.2*tempPed_[i+1];
      
      if (p_[i]<0) p_[i]=0;
    }
    
    for (int i=0; i<10; i++) {
      v_[i]=0;
      for (int j=0; j<25; j++) {
	v_[i] += TMath::Landau( 25*i + j, 109.78 - t_, 3.82 );
	temp_ += TMath::Landau( 25*i + j, 109.78 - t_, 3.82 );
      }
      //v_[i]+=p_[i];
      //temp_+=p_[i];
      //q_+=p_[i];
    };
    for (int i=0; i<10; i++) {
      v_[i] = gen.Gaus(q_ * v_[i] / temp_ , noise( q_ * v_[i] / temp_) ) + p_[i];
      //if (v_[i]<0) v_[i]=0;
      //cout << p_[i] << ", " << v_[i] << endl;
    }
    
  };

  double noise(double ifC) {
    double quantErr=10; //quantization error
    
    //dark current
    double mu=0.01*25/40;
    double dcErr=sqrt(mu/pow(1-0.17, 3))*40;
    
    double pedErr=10;
    
    double photoErr=sqrt(ifC*40);
    //if (ifC>0) photoErr=sqrt(ifC*40);
    
    //cout << ifC << ", " << quantErr << ", " << dcErr << ", " << pedErr << ", " << photoErr << endl;
    
    return sqrt( quantErr*quantErr + dcErr*dcErr + pedErr*pedErr + photoErr*photoErr );
    
  };
  
};


void PulseShape() {

  TCanvas *c = new TCanvas("c","",800, 800);
  gStyle->SetOptStat(0);
  gStyle->SetPalette(55);
  gStyle->SetPaintTextFormat("2.2f");

  int n=10000000;

  double avgTS[10]={0};
  double rmsTS[10]={0};
  double covTS[10][10]={{0}};
  //double corTS[10][10]={0};
  
  TH1D *q = new TH1D("q","q",40, 4000, 12000);

  TH2D* h = new TH2D("h","h",10,-0.5,9.5,10,-0.5,9.5);

  TRandom3 * gen = new TRandom3(47);

  for (int x=0; x<n; x++) {

    double a=gen->Rndm();

    pulse temp(gen->Gaus(0, 3), a*5000+5000, gen->Rndm()*1000);

    double sumQ = 0;
    for (int i=0; i<10; i++) sumQ+=temp.v_[i]; 

    q->Fill(sumQ);

    for (int i=0; i<10; i++) {
      //double qi = temp.v_[i]/sumQ;
      double qi = temp.v_[i];
      //double qi = temp.p_[i];

      q->Fill(qi);
    
      avgTS[i]+=qi;
      rmsTS[i]+=qi*qi;

      for (int j=0; j<10; j++) {
	//double qj = temp.v_[j]/sumQ;
	double qj = temp.v_[j];
	//double qj = temp.p_[j];
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

      if (i==j) cout << covTS[i][j] << ", " << rmsTS[i]*rmsTS[j] << endl;

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
