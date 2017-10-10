{

  TFile *f = new TFile("phaseScanPulse.root");
  TH1D *h = (TH1D*) f->Get("raw");

  TF1 *f2= new TF1 ("f2","[0]*TMath::Landau(x,[1],[2])",0.,250.);
  f2->SetLineColor(kMagenta);
  f2->SetLineWidth(2);
  f2->SetParName(0,"A1");
  f2->SetParName(1,"MP");
  f2->SetParName(2,"width");
  f2->SetParameters(0.2223/2,34.78,3.822);

  //h->Scale(1.0/h->Integral(0,100));

  vector<float> thenew;

  float thenewSum=0;
  for (uint i=1; i<h->GetNbinsX(); i++) {
    thenew.push_back(h->GetBinContent(i));
    thenewSum+=h->GetBinContent(i);
  }

  float thenewLandauSum=0;
  vector<float> thenewlandau;
  float landaumax=0;
  for (int i=0; i<250; i++) {
    thenewlandau.push_back(f2->Integral(i,i+25));
    thenewLandauSum+=f2->Integral(i,i+25);
    if (f2->Integral(i,i+25)>landaumax) landaumax=f2->Integral(i,i+25);
  }

  vector<float> landau = {0, 7.6377e-05, 0.000418655, 0.00153692, 0.00436844, 0.0102076, 
			  0.0204177, 0.0360559, 0.057596, 0.0848493, 0.117069, 0.153152, 0.191858, 0.23198, 0.272461, 0.312438, 
			  0.351262, 0.388476, 0.423788, 0.457036, 0.488159, 0.517167, 0.54412, 0.569112, 0.592254, 0.613668, 
			  0.633402, 0.651391, 0.667242, 0.680131, 0.688868, 0.692188, 0.689122, 0.67928, 0.662924, 0.64087, 
			   0.614282, 0.584457, 0.552651, 0.51997, 0.487317, 0.455378, 0.424647, 0.395445, 0.367963, 0.342288, 
			   0.318433, 0.29636, 0.275994, 0.257243, 0.24, 0.224155, 0.2096, 0.196227, 0.183937, 0.172635, 
			   0.162232, 0.15265, 0.143813, 0.135656, 0.128117, 0.12114, 0.114677, 0.108681, 0.103113, 0.0979354, 
			   0.0931145, 0.0886206, 0.0844264, 0.0805074, 0.0768411, 0.0734075, 0.0701881, 0.0671664, 0.0643271, 
			   0.0616564, 0.0591418, 0.0567718, 0.054536, 0.0524247, 0.0504292, 0.0485414, 0.046754, 0.0450602, 
			   0.0434538, 0.041929, 0.0404806, 0.0391037, 0.0377937, 0.0365465, 0.0353583, 0.0342255, 0.0331447, 
			   0.032113, 0.0311274, 0.0301854, 0.0292843, 0.0284221, 0.0275964, 0.0268053, 0.0253052, 0.0238536, 
			   0.0224483, 0.0210872, 0.0197684, 0.0184899, 0.01725, 0.0160471, 0.0148795, 0.0137457, 0.0126445, 
			   0.0115743, 0.0105341, 0.00952249, 0.00853844, 0.00758086, 0.00664871,0.00574103, 0.00485689, 0.00399541, 
			   0.00315576, 0.00233713, 0.00153878, 0.000759962, 0 };

  float landauSum=0;
  for (int i=0; i<landau.size(); i++) {
    landauSum+=landau.at(i);
  }

  //cout << h->Integral(100, 250) << ", " << landauSum << ", " << thenewLandauSum << endl;
  TGraph *g = new TGraph();
  TGraph *g3 = new TGraph();

  for (uint i=0; i<landau.size(); i++) {
    g->SetPoint(i,i+100,landau.at(i));
  }

  float sum2=0;
  for (int i=0; i<4; i++) {
    g3->SetPoint(i,i,0);
  }
  for (int i=4; i<thenewlandau.size(); i++) {
    g3->SetPoint(i,i+100,thenewlandau.at(i-4)*h->GetMaximum()/landaumax);
    sum2+=thenewlandau.at(i)*h->GetMaximum()/landaumax;
    //cout << thenew.at(i)*landauSum/thenewSum << ", ";
  }
  //cout << sum2 << endl;
  //cout << landau.size() << endl;
  g->SetLineColor(kRed);
  g3->SetLineColor(kGreen);
  h->GetYaxis()->SetRangeUser(0,1);
  h->Draw("hist");
  g->Draw("same l");
  g3->Draw("same l");

  cout << "current Landau:" << endl;
  for (int i=0; i<125; i++) {
    cout << landau.at(i) << ", ";
    if (i%10==1 && i>1) cout << endl;
  }
  cout << endl << endl << "empirical pulse: " << endl;
  for (int i=0; i<125; i++) {
    cout << h->GetBinContent(i+1+100) << ", ";
    if (i%10==1 && i>1) cout << endl;
  }
  cout << endl << endl << "new Landau: "<< endl;
  for (int i=0; i<125; i++) {
    double tmp, val;
    g3->GetPoint(i,tmp,val);
    cout << val << ", ";
    if (i%10==1 && i>1) cout << endl;
  }
  cout << endl;
  

}
