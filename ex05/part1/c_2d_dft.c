#include<stdio.h>
#include<complex.h>
#include<math.h>

#define MAX 1024
float complex x[MAX*MAX], y[MAX*MAX], z[MAX*MAX];

void idft_2d(float complex a[], float complex res[], int len_m, int len_n){
//Write code
  for(int m=0;m<len_m;m++){
    for(int n=0;n<len_n;n++){
      for(int k=0;k<len_m;k++){
        for(int l=0;l<len_n;l++){
          res[len_m*m+n] += a[len_m*k+l]*cexpf(2*M_PI*I*((k*m)/len_m + (l*n)/len_n));
        }
      }

    }
  }

}


void dft_2d(float complex a[], float complex res[], int len_m, int len_n){
//write code
  for(int k=0;k<len_m;k++){
    for(int l=0;l<len_n;l++){

      for(int m=0;m<len_m;m++){
        for(int n=0;n<len_n;n++){
          res[len_m*k+l]+= a[len_m*m+n]*cexpf(-2*M_PI*I*((k*m)/len_m + (l*n)/len_n));
        }
      }

    }
  }

}

int main(){
  int n,m,i,j;
  scanf("%d %d", &m, &n);
  
  for(j=0;j<n;j++){
    for(i=0;i<m;i++){
      float tmp;
      scanf("%f", &tmp);
      x[j*m+i]=tmp;
    }
  }
  dft_2d(x,y,m,n);
  idft_2d(y,z,m,n);

  for(j=0;j<n;j++){
    for(i=0;i<m;i++){
      printf("%.3f", cabsf(z[j*m+i]));
    }
    printf("\n");
  }

  return 0;
}
