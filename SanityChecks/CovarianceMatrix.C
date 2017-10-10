#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>                        // access to gROOT, entry point to ROOT system
#include <TSystem.h>                      // interface to OS
#include <TStyle.h>                       // class to handle ROOT plotting styles
#include <TFile.h>                        // file handle class
#include <TTree.h>                        // class to access ntuples
#include <TChain.h>                        // class to access ntuples
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TBenchmark.h>                   // class to track macro running statistics
#include <vector>                         // STL vector class
#include <iostream>                       // standard I/O
#include <iomanip>                        // functions to format standard I/O
#include <fstream>                        // functions for file I/O
#include <string>                         // C++ string class
#include <sstream>                        // class for parsing strings

#include <TRandom3.h>

#endif

void CovarianceMatrix() {


  TRandom3 *gen = new TRandom3(479);

  double n=1000000;
  
  double ano[4] = {0};
  double ano2[4] = {0};
  double asi[4] = {0};
  double ato[4] = {0};

  double vno[4] = {0};
  double vno2[4] = {0};
  double vsi[4] = {0};
  double vto[4] = {0};

  double cno[4][4] = {{0}};
  double cno2[4][4] = {{0}};
  double csi[4][4] = {{0}};
  double cto[4][4] = {{0}};

  for (int i=0; i<n; i++) {
    double p= gen->Gaus(4,0.5);
    double pm[4] = {p, -p, p, 0};
    pm[3]=pm[0]+pm[1]+pm[2];

    for (int j=0; j<4; j++) {
      ano2[j]+=pm[j];
      vno2[j]+=pm[j]*pm[j];

      for (int k=0; k<4; k++) {
	cno2[j][k]+=pm[j]*pm[k];
      }      
    }
  }

  for (int j=0; j<4; j++) {
    ano2[j]/=n; vno2[j]/=n; vno2[j]-=ano2[j]*ano2[j];
  }

  for (int j=0; j<4; j++) {
    for (int k=0; k<4; k++) {
      cno2[j][k]/=n; cno2[j][k]-=ano2[j]*ano2[k];
    }
  }


  for (int i=0; i<n; i++) {
    double p= gen->Gaus(4,0.5);
    double pm[4] = {p, -p, p, 0};
    pm[3]=pm[0]+pm[1]+pm[2];

    double q = gen->Gaus(10,1);
    double qm[4] = {gen->Poisson(q), gen->Poisson(3*q), gen->Poisson(2*q),0};
    qm[3]=qm[0]+qm[1]+qm[2];

    double tm[4] = {qm[0]+p-ano2[0], qm[1]-p-ano2[1], qm[2]+p-ano2[2], 0};
    tm[3]=tm[0]+tm[1]+tm[2];

    //tm[0]/=tm[3]; tm[1]/=tm[3]; tm[2]/=tm[3];

    //tm[0]/=totval; tm[1]/=totval; tm[2]/=totval;

    for (int j=0; j<4; j++) {
      ano[j]+=pm[j]; asi[j]+=qm[j]; ato[j]+=tm[j];
      vno[j]+=pm[j]*pm[j]; vsi[j]+=qm[j]*qm[j]; vto[j]+=tm[j]*tm[j];

      for (int k=0; k<4; k++) {
	cno[j][k]+=pm[j]*pm[k];
	csi[j][k]+=qm[j]*qm[k];
	cto[j][k]+=tm[j]*tm[k];
      }
    }
  }

  for (int j=0; j<4; j++) {
    ano[j]/=n; vno[j]/=n; vno[j]-=ano[j]*ano[j];
    asi[j]/=n; vsi[j]/=n; vsi[j]-=asi[j]*asi[j];
    ato[j]/=n; vto[j]/=n; vto[j]-=ato[j]*ato[j];
  }

  for (int j=0; j<4; j++) {
    for (int k=0; k<4; k++) {
      cno[j][k]/=n; cno[j][k]-=ano[j]*ano[k];
      csi[j][k]/=n; csi[j][k]-=asi[j]*asi[k];
      cto[j][k]/=n; cto[j][k]-=ato[j]*ato[k];
    }
  }


  cout << " noise cov matrix: " << endl;
  for (int j=0; j<4; j++) {
    for (int k=0; k<4; k++) {
      cout << cno[j][k] << ", ";
    }
    cout << endl;
  }

  cout << " signal cov matrix: " << endl;
  for (int j=0; j<4; j++) {
    for (int k=0; k<4; k++) {
      cout << csi[j][k] << ", ";
    }
    cout << endl;
  }

  cout << " total cov matrix: " << endl;
  for (int j=0; j<4; j++) {
    for (int k=0; k<4; k++) {
      cout << cto[j][k] << ", ";
    }
    cout << endl;
  }


  cout << endl;
  for (int j=0; j<4; j++) {
    for (int k=0; k<4; k++) {
      cout << 100*(cto[j][k] - csi[j][k]-cno[j][k])/cto[j][k] << ", ";
    }
    cout << endl;
  }

}
