{

  TFile *f = new TFile("M2TimeByChannel.root","read");
  vector<int> phase = {30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92};

  vector<TProfile2D*> v1;
  vector<TProfile2D*> v2;
  vector<TProfile2D*> v3;
  vector<TProfile2D*> v4;
  vector<TProfile2D*> v5;
  vector<TProfile2D*> v6;
  vector<TProfile2D*> v7;

  char pname[20];
  for (int i=0; i<phase.size(); i++) {
    sprintf(pname,"depth_1_%i",phase[i]);
    v1.push_back((TProfile2D*)f->Get(pname));
    sprintf(pname,"depth_2_%i",phase[i]);
    v2.push_back((TProfile2D*)f->Get(pname));
    sprintf(pname,"depth_3_%i",phase[i]);
    v3.push_back((TProfile2D*)f->Get(pname));
    sprintf(pname,"depth_4_%i",phase[i]);
    v4.push_back((TProfile2D*)f->Get(pname));
    sprintf(pname,"depth_5_%i",phase[i]);
    v5.push_back((TProfile2D*)f->Get(pname));
    sprintf(pname,"depth_6_%i",phase[i]);
    v6.push_back((TProfile2D*)f->Get(pname));
    sprintf(pname,"depth_7_%i",phase[i]);
    v7.push_back((TProfile2D*)f->Get(pname));
  }

  //depth 1
  for (int x=1; x< v1[0]->GetNbinsX()+1; x++) {
    for (int y=1; y< v1[0]->GetNbinsY()+1; y++) {

      int bestPhase=0;
      double bestAvgTime=-100;

      for (int j=0; j<phase.size(); j++) {
	if (abs(v1[j]->GetBinContent(x,y))<2 && v1[j]->GetBinContent(x,y)!=0) {
	  cout <<"   Depth: " << 1 << ", IEta: " << v1[0]->GetXaxis()->GetBinCenter(x) << ", IPhi: " << v1[0]->GetYaxis()->GetBinCenter(y) << ", ";
	  cout <<"Phase-setting: " << phase[j] << ", Average-time: " << v1[j]->GetBinContent(x,y) << endl;
	  if (bestPhase==0) {
	    bestPhase=phase[j];
	    bestAvgTime=v1[j]->GetBinContent(x,y);
	  }
	  else if (abs(v1[j]->GetBinContent(x,y))<abs(bestAvgTime)) {
	    bestPhase=phase[j];
	    bestAvgTime=v1[j]->GetBinContent(x,y);
	  }
	}
      }
      if (bestPhase!=0) {
	cout <<"Depth: " << 1 << ", IEta: " << v1[0]->GetXaxis()->GetBinCenter(x) << ", IPhi: " << v1[0]->GetYaxis()->GetBinCenter(y) << ", ";
	cout <<"Phase-setting: " << bestPhase << ", Average-time: " << bestAvgTime << endl;
      }
    }
  }
  cout << endl;
  //depth 2
  for (int x=1; x< v2[0]->GetNbinsX()+1; x++) {
    for (int y=1; y< v2[0]->GetNbinsY()+1; y++) {

      int bestPhase=0;
      double bestAvgTime=-100;

      for (int j=0; j<phase.size(); j++) {
	if (abs(v2[j]->GetBinContent(x,y))<1.5 && v2[j]->GetBinContent(x,y)!=0) {

	  if (bestPhase==0) {
	    bestPhase=phase[j];
	    bestAvgTime=v2[j]->GetBinContent(x,y);
	  }
	  else if (abs(v2[j]->GetBinContent(x,y))<abs(bestAvgTime)) {
	    bestPhase=phase[j];
	    bestAvgTime=v2[j]->GetBinContent(x,y);
	  }
	}
      }
      if (bestPhase!=0) {
	cout <<"Depth: " << 2 << ", IEta: " << v2[0]->GetXaxis()->GetBinCenter(x) << ", IPhi: " << v2[0]->GetYaxis()->GetBinCenter(y) << ", ";
	cout <<"Phase-setting: " << bestPhase << ", Average-time: " << bestAvgTime << endl;
      }
    }
  }
  cout << endl;
  //depth 3
  for (int x=1; x< v3[0]->GetNbinsX()+1; x++) {
    for (int y=1; y< v3[0]->GetNbinsY()+1; y++) {

      int bestPhase=0;
      double bestAvgTime=-100;

      for (int j=0; j<phase.size(); j++) {
	if (abs(v3[j]->GetBinContent(x,y))<1.5 && v3[j]->GetBinContent(x,y)!=0) {
	  if (bestPhase==0) {
	    bestPhase=phase[j];
	    bestAvgTime=v3[j]->GetBinContent(x,y);
	  }
	  else if (abs(v3[j]->GetBinContent(x,y))<abs(bestAvgTime)) {
	    bestPhase=phase[j];
	    bestAvgTime=v3[j]->GetBinContent(x,y);
	  }
	}
      }
      if (bestPhase!=0) {
	cout <<"Depth: " << 3 << ", IEta: " << v3[0]->GetXaxis()->GetBinCenter(x) << ", IPhi: " << v3[0]->GetYaxis()->GetBinCenter(y) << ", ";
	cout <<"Phase-setting: " << bestPhase << ", Average-time: " << bestAvgTime << endl;
      }
    }
  }
  cout << endl;
  //depth 4
  for (int x=1; x< v4[0]->GetNbinsX()+1; x++) {
    for (int y=1; y< v4[0]->GetNbinsY()+1; y++) {

      int bestPhase=0;
      double bestAvgTime=-100;

      for (int j=0; j<phase.size(); j++) {
	if (abs(v4[j]->GetBinContent(x,y))<1.5 && v4[j]->GetBinContent(x,y)!=0) {
	  if (bestPhase==0) {
	    bestPhase=phase[j];
	    bestAvgTime=v4[j]->GetBinContent(x,y);
	  }
	  else if (abs(v4[j]->GetBinContent(x,y))<abs(bestAvgTime)) {
	    bestPhase=phase[j];
	    bestAvgTime=v4[j]->GetBinContent(x,y);
	  }
	}
      }
      if (bestPhase!=0) {
	cout <<"Depth: " << 4 << ", IEta: " << v4[0]->GetXaxis()->GetBinCenter(x) << ", IPhi: " << v4[0]->GetYaxis()->GetBinCenter(y) << ", ";
	cout <<"Phase-setting: " << bestPhase << ", Average-time: " << bestAvgTime << endl;
      }
    }
  }
  cout << endl;
  //depth 5
  for (int x=1; x< v5[0]->GetNbinsX()+1; x++) {
    for (int y=1; y< v5[0]->GetNbinsY()+1; y++) {

      int bestPhase=0;
      double bestAvgTime=-100;

      for (int j=0; j<phase.size(); j++) {
	if (abs(v5[j]->GetBinContent(x,y))<1.5 && v5[j]->GetBinContent(x,y)!=0) {
	  if (bestPhase==0) {
	    bestPhase=phase[j];
	    bestAvgTime=v5[j]->GetBinContent(x,y);
	  }
	  else if (abs(v5[j]->GetBinContent(x,y))<abs(bestAvgTime)) {
	    bestPhase=phase[j];
	    bestAvgTime=v5[j]->GetBinContent(x,y);
	  }
	}
      }
      if (bestPhase!=0) {
	cout <<"Depth: " << 5 << ", IEta: " << v5[0]->GetXaxis()->GetBinCenter(x) << ", IPhi: " << v5[0]->GetYaxis()->GetBinCenter(y) << ", ";
	cout <<"Phase-setting: " << bestPhase << ", Average-time: " << bestAvgTime << endl;
      }
    }
  }
  cout << endl;
  //depth 6
  for (int x=1; x< v6[0]->GetNbinsX()+1; x++) {
    for (int y=1; y< v6[0]->GetNbinsY()+1; y++) {

      int bestPhase=0;
      double bestAvgTime=-100;

      for (int j=0; j<phase.size(); j++) {
	if (abs(v6[j]->GetBinContent(x,y))<1.5 && v6[j]->GetBinContent(x,y)!=0) {
	  if (bestPhase==0) {
	    bestPhase=phase[j];
	    bestAvgTime=v6[j]->GetBinContent(x,y);
	  }
	  else if (abs(v6[j]->GetBinContent(x,y))<abs(bestAvgTime)) {
	    bestPhase=phase[j];
	    bestAvgTime=v6[j]->GetBinContent(x,y);
	  }
	}
      }
      if (bestPhase!=0) {
	cout <<"Depth: " << 6 << ", IEta: " << v6[0]->GetXaxis()->GetBinCenter(x) << ", IPhi: " << v6[0]->GetYaxis()->GetBinCenter(y) << ", ";
	cout <<"Phase-setting: " << bestPhase << ", Average-time: " << bestAvgTime << endl;
      }
    }
  }
  cout << endl;
  //depth 7
  for (int x=1; x< v7[0]->GetNbinsX()+1; x++) {
    for (int y=1; y< v7[0]->GetNbinsY()+1; y++) {

      int bestPhase=0;
      double bestAvgTime=-100;

      for (int j=0; j<phase.size(); j++) {
	if (abs(v7[j]->GetBinContent(x,y))<1.5 && v7[j]->GetBinContent(x,y)!=0) {
	  if (bestPhase==0) {
	    bestPhase=phase[j];
	    bestAvgTime=v7[j]->GetBinContent(x,y);
	  }
	  else if (abs(v7[j]->GetBinContent(x,y))<abs(bestAvgTime)) {
	    bestPhase=phase[j];
	    bestAvgTime=v7[j]->GetBinContent(x,y);
	  }
	}
      }
      if (bestPhase!=0) {
	cout <<"Depth: " << 7 << ", IEta: " << v7[0]->GetXaxis()->GetBinCenter(x) << ", IPhi: " << v7[0]->GetYaxis()->GetBinCenter(y) << ", ";
	cout <<"Phase-setting: " << bestPhase << ", Average-time: " << bestAvgTime << endl;
      }
    }
  }


}
