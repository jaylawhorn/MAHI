class datEntry {
public:
  double val_[3];
  double ped_[3];
  double sval_;
  double sped_;
  double tot_[3];
  double stot_;
  
  datEntry(double v0, double v1, double v2, 
	   double p0, double p1, double p2) 
  {
    sval_=v0+v1+v2;
    sped_=p0+p1+p2;
    stot_=sval_+sped_;

    val_[0]=v0;///sval_;
    val_[1]=v1;///sval_;
    val_[2]=v2;///sval_;
    
    ped_[0]=p0;
    ped_[1]=p1;
    ped_[2]=p2;

    tot_[0]=(v0+p0);///stot_;
    tot_[1]=(v1+p1);///stot_;
    tot_[2]=(v2+p2);///stot_;
    
  };
  
};

void test() {
  
  vector<datEntry> ahh;
  ahh.push_back(datEntry(4,7,6,1,1,2));
  ahh.push_back(datEntry(8,13,12,2,1,1));
  
  double va[4] = {0};
  double pa[4] = {0};
  double ta[4] = {0};
  
  double vv[4][4] = {0};
  double pp[4][4] = {0};
  double tt[4][4] = {0};
  
  double vp[4][4] = {0};
  double pv[4][4] = {0};
  
  double vt[4][4] = {0};
  double tv[4][4] = {0};
  
  double pt[4][4] = {0};
  double tp[4][4] = {0};

  for (int ii=0; ii<ahh.size(); ii++) {
    va[0]+=ahh.at(ii).val_[0]/ahh.size();
    va[1]+=ahh.at(ii).val_[1]/ahh.size();
    va[2]+=ahh.at(ii).val_[2]/ahh.size();
    va[3]+=ahh.at(ii).sval_/ahh.size();
    
    pa[0]+=ahh.at(ii).ped_[0]/ahh.size();
    pa[1]+=ahh.at(ii).ped_[1]/ahh.size();
    pa[2]+=ahh.at(ii).ped_[2]/ahh.size();
    pa[3]+=ahh.at(ii).sped_/ahh.size();
    
    ta[0]+=ahh.at(ii).tot_[0]/ahh.size();
    ta[1]+=ahh.at(ii).tot_[1]/ahh.size();
    ta[2]+=ahh.at(ii).tot_[2]/ahh.size();
    ta[3]+=ahh.at(ii).stot_/ahh.size();
    
    vv[3][3]+=ahh.at(ii).sval_*ahh.at(ii).sval_/ahh.size();
    pp[3][3]+=ahh.at(ii).sped_*ahh.at(ii).sped_/ahh.size();
    tt[3][3]+=ahh.at(ii).stot_*ahh.at(ii).stot_/ahh.size();
    
    vp[3][3]+=ahh.at(ii).sval_*ahh.at(ii).sped_/ahh.size();
    pv[3][3]+=ahh.at(ii).sped_*ahh.at(ii).sval_/ahh.size();
    vt[3][3]+=ahh.at(ii).sval_*ahh.at(ii).stot_/ahh.size();
    tv[3][3]+=ahh.at(ii).stot_*ahh.at(ii).sval_/ahh.size();
    pt[3][3]+=ahh.at(ii).sped_*ahh.at(ii).stot_/ahh.size();
    tp[3][3]+=ahh.at(ii).stot_*ahh.at(ii).sped_/ahh.size();
    
    for (int j=0; j<3; j++) {
      vv[j][3]+=ahh.at(ii).val_[j]*ahh.at(ii).sval_/ahh.size();
      vv[3][j]+=ahh.at(ii).sval_*ahh.at(ii).val_[j]/ahh.size();
      pp[j][3]+=ahh.at(ii).ped_[j]*ahh.at(ii).sped_/ahh.size();
      pp[3][j]+=ahh.at(ii).sped_*ahh.at(ii).ped_[j]/ahh.size();
      tt[j][3]+=ahh.at(ii).tot_[j]*ahh.at(ii).stot_/ahh.size();
      tt[3][j]+=ahh.at(ii).stot_*ahh.at(ii).tot_[j]/ahh.size();
      vp[j][3]+=ahh.at(ii).val_[j]*ahh.at(ii).sped_/ahh.size();
      pv[j][3]+=ahh.at(ii).ped_[j]*ahh.at(ii).sval_/ahh.size();
      vt[j][3]+=ahh.at(ii).val_[j]*ahh.at(ii).stot_/ahh.size();
      tv[j][3]+=ahh.at(ii).tot_[j]*ahh.at(ii).sval_/ahh.size();
      pt[j][3]+=ahh.at(ii).ped_[j]*ahh.at(ii).stot_/ahh.size();
      tp[j][3]+=ahh.at(ii).tot_[j]*ahh.at(ii).sped_/ahh.size();
      pv[3][j]+=ahh.at(ii).val_[j]*ahh.at(ii).sped_/ahh.size();
      vp[3][j]+=ahh.at(ii).ped_[j]*ahh.at(ii).sval_/ahh.size();
      tv[3][j]+=ahh.at(ii).val_[j]*ahh.at(ii).stot_/ahh.size();
      vt[3][j]+=ahh.at(ii).tot_[j]*ahh.at(ii).sval_/ahh.size();
      tp[3][j]+=ahh.at(ii).ped_[j]*ahh.at(ii).stot_/ahh.size();
      pt[3][j]+=ahh.at(ii).tot_[j]*ahh.at(ii).sped_/ahh.size();
      
      for (int k=0; k<3; k++) {	
	vv[j][k]+=ahh.at(ii).val_[j]*ahh.at(ii).val_[k]/ahh.size();
	vv[k][j]+=ahh.at(ii).val_[k]*ahh.at(ii).val_[j]/ahh.size();
	pp[j][k]+=ahh.at(ii).ped_[j]*ahh.at(ii).ped_[k]/ahh.size();
	pp[k][j]+=ahh.at(ii).ped_[k]*ahh.at(ii).ped_[j]/ahh.size();
	tt[j][k]+=ahh.at(ii).tot_[j]*ahh.at(ii).tot_[k]/ahh.size();
	tt[k][j]+=ahh.at(ii).tot_[k]*ahh.at(ii).tot_[j]/ahh.size();
	vp[j][k]+=ahh.at(ii).val_[j]*ahh.at(ii).ped_[k]/ahh.size();
	pv[j][k]+=ahh.at(ii).ped_[j]*ahh.at(ii).val_[k]/ahh.size();
	vt[j][k]+=ahh.at(ii).val_[j]*ahh.at(ii).tot_[k]/ahh.size();
	tv[j][k]+=ahh.at(ii).tot_[j]*ahh.at(ii).val_[k]/ahh.size();
	pt[j][k]+=ahh.at(ii).ped_[j]*ahh.at(ii).tot_[k]/ahh.size();
	tp[j][k]+=ahh.at(ii).tot_[j]*ahh.at(ii).ped_[k]/ahh.size();
	vp[k][j]+=ahh.at(ii).val_[k]*ahh.at(ii).ped_[j]/ahh.size();
	pv[k][j]+=ahh.at(ii).ped_[k]*ahh.at(ii).val_[j]/ahh.size();
	vt[k][j]+=ahh.at(ii).val_[k]*ahh.at(ii).tot_[j]/ahh.size();
	tv[k][j]+=ahh.at(ii).tot_[k]*ahh.at(ii).val_[j]/ahh.size();
	pt[k][j]+=ahh.at(ii).ped_[k]*ahh.at(ii).tot_[j]/ahh.size();
	tp[k][j]+=ahh.at(ii).tot_[k]*ahh.at(ii).ped_[j]/ahh.size();
      }
    }
  }

  for (int j=0; j<4; j++) {
    for (int k=0; k<4; k++) {
      
      vv[j][k]-=va[j]*va[k];
      pp[j][k]-=pa[j]*pa[k];
      tt[j][k]-=ta[j]*ta[k];
      
      vp[j][k]-=va[j]*pa[k];
      pv[j][k]-=pa[j]*va[k];
      tp[j][k]-=ta[j]*pa[k];
      pt[j][k]-=pa[j]*ta[k];
      vt[j][k]-=va[j]*ta[k];
      tv[j][k]-=ta[j]*va[k];
      
    }
  }

  double test[4][4]={0};

  for (int j=0; j<4; j++) {
    for (int k=0; k<4; k++) {
      test[j][k] = tt[j][k] - pp[j][k] - pv[j][k] - vp[j][k];
      cout << test[j][k] << ", ";
    }
    cout << endl;
  }

  cout << endl << "vv" << endl;
  for (int j=0; j<4; j++) {
    for (int k=0; k<4; k++) {
      cout << vv[j][k] << ", ";
    }
    cout << endl;
  }
  

}
