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
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <cmath>

#endif

class PulseShape
{
public:
  
  PulseShape() {};
  ~PulseShape() {};

  uint nBinsSiPM_=250;
  double A1_, sigma1_shape_, theta1_loc_, m1_scale_;
  double A2_, sigma2_shape_, theta2_loc_, m2_scale_;

  void setValues(double A1, double sigma1_shape, double theta1_loc, double m1_scale, 
		 double A2, double sigma2_shape, double theta2_loc, double m2_scale) {
    A1_=A1;
    sigma1_shape_=sigma1_shape;
    theta1_loc_=theta1_loc;
    m1_scale_=m1_scale;
    A2_=A2;
    sigma2_shape_=sigma2_shape;
    theta2_loc_=theta2_loc;
    m2_scale_=m2_scale;
  }

  double analyticPulseShapeSiPMHE(double t) {
    // taken from fit to laser measurement taken by Iouri M. in Spring 2016.                                                
    //double A1(5.204/6.94419), sigma1_shape(0.5387), theta1_loc(-0.3976), m1_scale(4.428);
    //double A2(1.855/6.94419), sigma2_shape(0.8132), theta2_loc(7.025),   m2_scale(12.29);
    return
      onePulse(t,A1_,sigma1_shape_,theta1_loc_,m1_scale_) +
      onePulse(t,A2_,sigma2_shape_,theta2_loc_,m2_scale_);
  }
  
  double Y11TimePDF(double t) {
    return exp(-0.0635-0.1518*t)*pow(t, 2.528)/2485.9;
  }
  
  double onePulse(double t, double A, double sigma, double theta, double m) {
    return (t<theta) ? 0 : A*TMath::LogNormal(t,sigma,theta,m);
  }

  std::vector<double> convolve() {
    std::vector<double> result(2*nBinsSiPM_-1,0.);
    for(unsigned i = 0; i < 2*nBinsSiPM_-1; ++i){
      for(unsigned j = 0; j < std::min(i+1,nBinsSiPM_); ++j){
	double tmp = analyticPulseShapeSiPMHE(j)*Y11TimePDF(i-j);
	if(std::isnan(tmp) or std::isinf(tmp)) continue;
	result[i] += tmp;
      }
    }
    return result;
  }

};

void fitPulse() {

  const int nBinsSiPM_ = 250;

  TH1D* h = new TH1D("sipmShape","sipmShape",nBinsSiPM_, 0, nBinsSiPM_);

  PulseShape theShape = PulseShape();
  //theShape.setValues(5.204/6.94419, 0.5387, -0.3976, 4.428,
  //1.855/6.94419, 0.8132, 7.025,   12.29);
  theShape.setValues(4.59863e-01, 

  //numerical convolution of SiPM pulse + WLS fiber shape                                                                 
  std::vector<double> nt = theShape.convolve();


  //skip first bin, always 0                                                                                              
  double norm = 0.;
  for (unsigned int j = 1; j <= nBinsSiPM_; ++j) {
    norm += (nt[j]>0) ? nt[j] : 0.;
  }

  for (unsigned int j = 1; j <= nBinsSiPM_; ++j) {
    nt[j] /= norm;
    h->SetBinContent(j,nt[j]);
    //siPMShape2017_.setShapeBin(j,nt[j]);
  }

  h->Draw();

}

