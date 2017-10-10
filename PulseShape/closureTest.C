{

  int a[10] = {2, 3, 4, 5, 6, 7, 5, 3, 4, 3};
  int b[13];

  for (int i=0; i<10; i++) {
    cout << a[i] << ", ";
  }
  cout << endl;

  for (int i=0; i<13; i++) {
    if (i==0) {
      b[i]=a[i];
    }
    else if (i==1) {
      b[i]=a[i-1]+a[i];
    }
    else if (i==2) {
      b[i]=a[i]+a[i-1]+a[i-2];
    }
    else if (i==10) {
      b[i]=a[i-1]+a[i-2]+a[i-3];
    }
    else if (i==11) {
      b[i]=a[i-2]+a[i-3];
    }
    else if (i==12) {
      b[i]=a[i-3];
    }
    else {
      b[i]=a[i]+a[i-1]+a[i-2]+a[i-3];
    }
  }

  for (int i=0; i<13; i++) {
  }
  cout << endl;


  int c[10];
  for (int i=0; i<10; i++) {
    if (i==0) {
      c[i]=b[i];
    }
    else if (i==1 ||i==2||i==3) {
      c[i]=b[i]-b[i-1];
    }
    else {
      c[i]=b[i]-b[i-1]+c[i-4];
    }
    //cout << c[i] << ", ";
  }
  //cout << endl;

  for (int i=0; i<10; i++) {
    cout << c[i] << ", ";
  }
  cout << endl;


}
