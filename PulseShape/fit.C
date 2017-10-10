//https://root-forum.cern.ch/t/fitting-with-lognormal-function/17629

void fit(){

  TFile *f = new TFile("phaseScanPulse.root");

  TH1D * h1 = (TH1D*) f->Get("dall");
  h1->Draw("hist");

  /////////
  ///// pick the first logNormal

  // set initial parameters 
  double p[3]; 
  p[0] = h1->GetEntries()*h1->GetXaxis()->GetBinWidth(1);   // area of the histogram 
   
  // find median of histogram 
  double prob[] = {0.5}; 
  double q[1]; 
  h1->GetQuantiles(1,q,prob);
  double median = q[0];
  // find mode of histogram 
  double  mode = h1->GetBinCenter( h1->GetMaximumBin());

  std::cout << "histogram mode is " << mode  << " median is " << median << std::endl;

  if (median < 0) { 
    Error("lognormal","not valid histogram median");
    return;
  }

  // m is log(median)
  p[1] = std::log(median); 

  // s2 is  log(median) - log(mode) 
  p[2] = std::sqrt( std::log(median/mode) ); 

  ///////
  //// setting the second logNormal

  //  TF1 *logN = new TF1("","ROOT::Math::lognormal_pdf(x,[0],[1],0)",0,1000);
  TF1 *logN = new TF1("logN","[0]*ROOT::Math::lognormal_pdf(x,[1],[2] ) ", 20., 40. ); 
  TF1 *logN2 = new TF1("logN2","[0]*ROOT::Math::lognormal_pdf(x,[1],[2] ) ", 40., 100. ); 

  logN->SetParameters(p); 
  logN->SetParName(0,"A1");
  logN->SetParName(1,"m1");
  logN->SetParName(2,"s1");

  double m[3]; 
  m[0]=0.5*p[0]; // area
  m[1] = 0.5*p[1]; // mean
  m[2] = 0.5*p[2]; //sigma
  logN2->SetParameters(m); 
  logN2->SetParName(0,"A2");
  logN2->SetParName(1,"m2");
  logN2->SetParName(2,"s2");

  TF1 *f1= new TF1 ("f1","logN+logN2",10.,100.);

  double par[6]; 

  h1->Draw();
  std::cout << logN->GetNpar() << std::endl;

  logN->SetLineColor(kBlue);
  logN2->SetLineColor(kGreen+1);

  //  h1->Fit(logN,"V");
  h1->Fit(logN,"V","",20., 40.);
  h1->Fit(logN2,"V+","",40., 100.);

  logN->GetParameters(&par[0]);
  logN2->GetParameters(&par[3]);
  f1->SetParName(0,"A1");
  f1->SetParName(1,"m1");
  f1->SetParName(2,"s1");
  f1->SetParName(3,"A2");
  f1->SetParName(4,"m2");
  f1->SetParName(5,"s2");
  f1->SetParameters(par);

  h1->Fit(f1,"V","",20., 100.);

  //logN->Draw("same");
  //logN2->Draw("same");
  //f1->SetLineColor(kViolet);
  //f1->Draw("same");

  cout << "chi2=" <<  f1->GetChisquare() << endl;

}
