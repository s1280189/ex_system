* main.c
 *
 *  Created on: 2023/02/01
 *      Author: s1280189
 */

#include "sys/alt_alarm.h"
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 1024*16
float complex x[MAX],y[MAX],z[MAX];
void fft_1d_rec(float complex f[], int length){
// write your code here
	if(length==1)return;
	float complex a[length/2], b[length/2];
	for(int i=0;i<length/2; i++){
		a[i]= ;
		b[i]= ;
	}
	
	fft_1d_rec(a,length/2);
	fft_1d_rec(b, length/2);
	
	for(int i=0;i<length/2;++i){
		f[2*i]=...;
		f[2*i+1]=...;
	}
	return;
}

void dft_1d(float complex a[], float complex res[], int length){
// write your code here
	 for(int t=0;t<length;t++){
	    for(int x=0;x<length;x++){
	      res[t]+=a[x]*cexpf((-I*2*t*M_PI*x)/length);
	    }
	  }
	}

}
int compare(){
int i,n=16;
float complex u[] ={1,2,3,4,1,2,3,4,0,0,0,0,0,0,0,0};
float complex v[n],w[n];
for(i=0;i<n;++i) v[i]=u[i];
fft_1d_rec(u,n);
dft_1d(v,w,n);
for(i=0;i<n;++i){
if(cabsf(w[i]-u[i])>0.0001) {
printf("Test failed: u[%d] != w[%d]\n",i,i);
return -1;
}
}
printf("Test passed\n");
return 0;
}
int main(){
int start_time, finish_time,n,i;
float total_time;
compare();
for(n=1<<4; n<(1<<11);n=n<<1){
for(i=0;i<n;++i) x[i]=rand()/1024;
start_time=alt_nticks();
dft_1d(x,y,n);
finish_time=alt_nticks();
total_time = ((finish_time-start_time)*1000)/alt_ticks_per_second();
printf("Total time of DFT (n=%d): %f ms\n",n,total_time);
start_time=alt_nticks();
fft_1d_rec(x,n);
finish_time=alt_nticks();
total_time = ((finish_time-start_time)*1000)/alt_ticks_per_second();
printf("Total time of FFT (n=%d): %f ms\n",n,total_time);
}
printf("Finished.\n");
return 0;
}
