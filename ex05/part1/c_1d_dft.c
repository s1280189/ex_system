#include<stdio.h>
#include<complex.h>
#include<math.h>

#define MAX 1024
float complex x[MAX*MAX], y[MAX*MAX], z[MAX*MAX];

void dft_1d(float complex a[], float complex res[], int length){
  //write code here  
  for(int t=0;t<length;t++){
    for(int i=0;i<length;i++){
      res[t]+=a[i]*cexpf((-I*2*t*M_PI*i)/length);
    }
  }
}


void idft_1d(float complex a[], float complex res[], int length){
  //write code here
}


int main(){
  int n,i;

  scanf("%d",&n);
  for(i=0;i<n;i++){
    float tmp;
    scanf("%f", &tmp);
    x[i]=temp;
  }
  dft_1d(x, y , n);
  idft_1d(y, z, n);

  for(i=0;i<n;i++){
    printf("%.3f%+.3fi\n", crealf(y[i]), cimagf(y[i]));
  }


  for(i=0;i<n;i++){
     printf("%.3f%+.3fi\n", crealf(z[i]), cimagf(z[i]));
  }

  for(i=0;i<n;i++){
    printf("%.3f\n", cabsf(z[i]));
  }

  return 0;
}
