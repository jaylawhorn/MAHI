{

  //-------------------------------------------
  //
  //generate array of numbers
  //
  //-------------------------------------------

  //TFile *f = new TFile("goodData/sortedByTDC_all.root","read");
  TFile *f = new TFile("sortedByTDC_all.root","read");
  
  //vector<TProfile*> v_p3;
  vector<TProfile*> v_p4;
  for (int i=0; i<50; i++) {
    char pname[10];
    //sprintf(pname,"p3_%i",i);
    //v_p3.push_back((TProfile*)f->Get(pname));
    sprintf(pname,"p4_%i",i);
    v_p4.push_back((TProfile*)f->Get(pname));
  } 

  double leakage = (v_p4.at(0)->GetBinContent(9+1))/50.;

  for(int i=0; i<50; i++){
    double sf = 1.0 - leakage * (double)i;
    v_p4.at(i)->Scale(sf);
  }

  TFile *outputfile = new TFile("phaseScanPulse.root","recreate");

  TH1D *dall = new TH1D("diff","differenced pulse shape",500,0,250);
  TH1D *gall = new TH1D("raw","TDC-ordered pulse fractions",500,0,250);

  for (int i=0; i<50; i++) {

    gall->SetBinContent(i+1,     v_p4.at(49-i)->GetBinContent(0+1));
    gall->SetBinContent(i+1+50,  v_p4.at(49-i)->GetBinContent(1+1));
    gall->SetBinContent(i+1+100, v_p4.at(49-i)->GetBinContent(2+1));
    gall->SetBinContent(i+1+150, v_p4.at(49-i)->GetBinContent(3+1));
    gall->SetBinContent(i+1+200, v_p4.at(49-i)->GetBinContent(4+1));
    gall->SetBinContent(i+1+250, v_p4.at(49-i)->GetBinContent(5+1));
    gall->SetBinContent(i+1+300, v_p4.at(49-i)->GetBinContent(6+1));
    gall->SetBinContent(i+1+350, v_p4.at(49-i)->GetBinContent(7+1));
    gall->SetBinContent(i+1+400, v_p4.at(49-i)->GetBinContent(8+1));
    gall->SetBinContent(i+1+450, v_p4.at(49-i)->GetBinContent(9+1));

  }

  for (int i=1; i<500; i++) {
    double temp=gall->GetBinContent(i+1)-gall->GetBinContent(i);
    double terror = gall->GetBinError(i+1)*gall->GetBinError(i+1) + gall->GetBinError(i)*gall->GetBinError(i);
    if (i+1-50>0) {
      temp+=dall->GetBinContent(i+1-50);
      terror+=dall->GetBinError(i+1-50)*dall->GetBinError(i+1-50);
    }
    dall->SetBinContent(i+1,temp);
    dall->SetBinError(i+1, sqrt(terror));
    
  }

  gall->Rebin(2);
  gall->Scale(0.5);

  dall->Rebin(2);
  dall->Scale(0.5);

  outputfile->Write();
  outputfile->Close();

}
