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

class pulse  {
public:
  double t_;
  double q_;
  double v_[10];
  
  pulse(double t, double q) {
    t_=t;
    q_=q;
    
    double temp_=0;
    
    for (int i=0; i<10; i++) {
      v_[i]=0;
      for (int j=0; j<25; j++) {
	v_[i] += TMath::Landau( 25*i + j, 109.78 - t_, 3.82 );
	temp_ += TMath::Landau( 25*i + j, 109.78 - t_, 3.82 );
      }
    };
    for (int i=0; i<10; i++) {
      //v_[i] = q_ * v_[i] / temp_ ;
      v_[i] = v_[i] / temp_ ;
      
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

void PulseShapeForMAHI() {

  pulse cent(0, 5000);
  pulse minu(-1, 5000);
  pulse plus(+1, 5000);

  for (int i=0; i<10; i++) {
    cout << cent.v_[i] << " + " << 0.5*(plus.v_[i] - minu.v_[i]) << " * t " << endl;
  }

}
