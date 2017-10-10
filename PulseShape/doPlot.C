#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TMath.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TLatex.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "CalStyleRemix.hh"
#endif

vector<float> getOld();

void doPlot() {

  TCanvas *c1 =MakeCanvas("c1","",800, 600);

  //gStyle->SetOptStat(0);

  TFile *f1 = new TFile("phaseScanPulse.root");

  TH1D* diff = (TH1D*) f1->Get("diff");
  //InitHist(diff, "Time [ns]", "Pulse fraction", kWhite);
  for (int i=1; i<diff->GetNbinsX(); i++) {
    cout << i << ", " << diff->GetBinContent(i) << endl;
  }

  diff->SetTitleSize  (0.055,"Y");
  diff->SetTitleOffset(1.600,"Y");
  diff->SetLabelOffset(0.014,"Y");
  diff->SetLabelSize  (0.050,"Y");
  diff->SetLabelFont  (42   ,"Y");
  diff->SetTitleSize  (0.055,"X");
  diff->SetTitleOffset(1.300,"X");
  diff->SetLabelOffset(0.014,"X");
  diff->SetLabelSize  (0.050,"X");
  diff->SetLabelFont  (42   ,"X");
  diff->GetYaxis()->SetTitleFont(42);
  diff->GetXaxis()->SetTitleFont(42);

  diff->GetXaxis()->SetTitle("Time [ns]");
  diff->GetYaxis()->SetTitle("Pulse Fraction");
  diff->SetTitle("");
  //diff->SetFillColor(0);
  diff->SetLineColor(kBlack);
  diff->SetLineWidth(3);
  diff->GetYaxis()->SetRangeUser(-0.01,0.025);


  TF1 *f2= new TF1 ("f2","[0]*TMath::Landau(x,[1],[2])",0.,250.);
  f2->SetLineColor(kMagenta);
  f2->SetLineWidth(2);
  f2->SetParName(0,"A1");
  f2->SetParName(1,"MP");
  f2->SetParName(2,"width");
  f2->SetParameters(0.2223/2,34.78+75,3.822);
 
  vector<float> nt = getOld();
  cout << nt.size() << endl;

  TGraph *gMC = new TGraph();
  gMC->SetLineColor(kRed);
  gMC->SetLineWidth(3);
  //InitGraph(gMC, "", "", kBlue);
  TGraph *gEmp = new TGraph();
  gEmp->SetLineColor(kBlue);
  gEmp->SetLineWidth(3);
  //InitGraph(gEmp, "", "", kRed);

  for (uint i=0; i<nt.size()-95; i++) {
    gMC->SetPoint(i,i+95,nt[i]/2);
  }
  for (uint i=0; i<250; i++) {
    gEmp->SetPoint(i,i,f2->Eval(i));
  }

  diff->GetXaxis()->SetRangeUser(75,250);

  diff->Draw("hist");
  //gMC->Draw("lsame");
  //gEmp->Draw("lsame");


  TLegend *leg = new TLegend(0.64, 0.6, 0.93, 0.9);
  leg->SetShadowColor(0);
  leg->SetLineColor(0);
  leg->AddEntry(diff, "Data","l");
  //leg->AddEntry(gMC,  "Current MC","l");
  //leg->AddEntry(gEmp, "New Fit","l");

  leg->Draw();

  //char land[500];
  //sprintf(land, "f(t) = %.2f * TMath::Landau(t, mpv=%.2f, sigma=%.2f)", f2->GetParameter(0), f2->GetParameter(1), f2->GetParameter(2));
  //
  ////cout << land << endl;
  //TLatex* latex = new TLatex;
  //latex->SetNDC();
  //latex->SetTextSize(0.035);
  //latex->SetTextColor(kBlue);
  //latex->DrawLatex(.22, .2, land);
  //latex->Draw();

  c1->SaveAs("new_pulse_shape_nofits.png");

}

vector<float> getOld() {

  std::vector<float> nt = {
    2.03644e-08,
    1.31271e-05,
    0.000104047,
    0.000396473,
    0.00101485,
    0.00203522,
    0.00347024,
    0.00527766,
    0.00737819,
    0.00967527,
    0.0120718,
    0.0144801,
    0.0168259,
    0.0190497,
    0.021106,
    0.0229621,
    0.0245962,
    0.025996,
    0.027157,
    0.0280809,
    0.0287747,
    0.0292488,
    0.0295167,
    0.0295937,
    0.0294966,
    0.0292426,
    0.0288491,
    0.0283336,
    0.0277129,
    0.0270028,
    0.0262187,
    0.0253747,
    0.0244838,
    0.0235579,
    0.0226078,
    0.0216431,
    0.0206725,
    0.0197035,
    0.0187426,
    0.0177953,
    0.0168665,
    0.0159601,
    0.0150793,
    0.0142267,
    0.0134044,
    0.0126138,
    0.0118559,
    0.0111314,
    0.0104404,
    0.00978306,
    0.00915898,
    0.00856766,
    0.00800843,
    0.00748045,
    0.00698277,
    0.00651434,
    0.00607406,
    0.00566077,
    0.00527327,
    0.00491036,
    0.00457083,
    0.00425349,
    0.00395714,
    0.00368063,
    0.00342282,
    0.00318263,
    0.00295898,
    0.00275087,
    0.00255732,
    0.00237739,
    0.00221021,
    0.00205493,
    0.00191076,
    0.00177693,
    0.00165275,
    0.00153754,
    0.00143068,
    0.00133157,
    0.00123966,
    0.00115444,
    0.00107542,
    0.00100215,
    0.000934208,
    0.000871209,
    0.000812786,
    0.000758599,
    0.000708335,
    0.000661701,
    0.000618427,
    0.000578262,
    0.000540972,
    0.000506344,
    0.000474177,
    0.000444286,
    0.000416502,
    0.000390667,
    0.000366635,
    0.000344272,
    0.000323452,
    0.000304062,
    0.000285995,
    0.000269153,
    0.000253446,
    0.00023879,
    0.000225109,
    0.00021233,
    0.000200389,
    0.000189225,
    0.000178781,
    0.000169007,
    0.000159854,
    0.000151278,
    0.000143239,
    0.000135699,
    0.000128622,
    0.000121978,
    0.000115735,
    0.000109867,
    0.000104348,
    9.91543e-05,
    9.42644e-05,
    8.96579e-05,
    8.5316e-05,
    8.12213e-05,
    7.73578e-05,
    7.37106e-05,
    7.02656e-05,
    6.701e-05,
    6.3932e-05,
    6.10202e-05,
    5.82644e-05,
    5.5655e-05,
    5.3183e-05,
    5.084e-05,
    4.86183e-05,
    4.65107e-05,
    4.45103e-05,
    4.26109e-05,
    4.08066e-05,
    3.90918e-05,
    3.74615e-05,
    3.59108e-05,
    3.44353e-05,
    3.30307e-05,
    3.16932e-05,
    3.04189e-05,
    2.92045e-05,
    2.80467e-05,
    2.69424e-05,
    2.58889e-05,
    2.48834e-05,
    2.39233e-05,
    2.30064e-05,
    2.21304e-05,
    2.12932e-05,
    2.04928e-05,
    1.97273e-05,
    1.89951e-05,
    1.82944e-05,
    1.76236e-05,
    1.69814e-05,
    1.63663e-05,
    1.5777e-05,
    1.52123e-05,
    1.46709e-05,
    1.41518e-05,
    1.3654e-05,
    1.31764e-05,
    1.27181e-05,
    1.22782e-05,
    1.18558e-05,
    1.14502e-05,
    1.10606e-05,
    1.06863e-05,
    1.03266e-05,
    9.98081e-06,
    9.64837e-06,
    9.32866e-06,
    9.02114e-06,
    8.72529e-06,
    8.44058e-06,
    8.16655e-06,
    7.90275e-06,
    7.64873e-06,
    7.40408e-06,
    7.16842e-06,
    6.94136e-06,
    6.72255e-06,
    6.51166e-06,
    6.30834e-06,
    6.11231e-06,
    5.92325e-06,
    5.74089e-06,
    5.56497e-06,
    5.39521e-06,
    5.23138e-06,
    5.07325e-06,
    4.92058e-06,
    4.77317e-06,
    4.63081e-06,
    4.49331e-06,
    4.36047e-06,
    4.23212e-06,
    4.10808e-06,
    3.9882e-06,
    3.87231e-06,
    3.76027e-06,
    3.65193e-06,
    3.54716e-06,
    3.44581e-06,
    3.34777e-06,
    3.25291e-06,
    3.16111e-06,
    3.07227e-06,
    2.98628e-06,
    2.90302e-06,
    2.82242e-06,
    2.74436e-06,
    2.66877e-06,
    2.59555e-06,
    2.52461e-06,
    2.45588e-06,
    2.38928e-06,
    2.32474e-06,
    2.26219e-06,
    2.20154e-06,
    2.14275e-06,
    2.08575e-06,
    2.03047e-06,
    1.97685e-06,
    1.92485e-06,
    1.8744e-06,
    1.82546e-06,
    1.77796e-06,
    1.73187e-06,
    1.68714e-06,
    1.64373e-06,
    1.60158e-06,
    1.56066e-06,
    1.52092e-06,
    1.48234e-06,
    1.44487e-06,
    1.40847e-06,
    1.37311e-06,
    1.33876e-06,
    1.30539e-06,
    1.27296e-06,
    1.24144e-06,
    1.21081e-06,
    1.18104e-06};

  return nt;
}
