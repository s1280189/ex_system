#include <stdio.h>
#include <complex.h>
#include <math.h>

// f: input signals
// length: length of the signals that should be 2^n
// C99 or later supports dynamic array.
void fft_1d_rec(float complex f[], int length){
if(length==1) return;
float complex a[length/2],b[length/2];
for(int i=0; i<length/2; ++i) {
a[i] = ;
b[i] = ...;
}
fft_1d_rec(a,length/2);
fft_1d_rec(b,length/2);
for(int i=0; i<length/2; ++i) {
f[2*i ] = ...;
f[2*i+1] = ...;
}
return;
}
void ifft_1d_rec(float complex f[], int length){
for(int i=0; i<length; ++i) f[i] = conjf(f[i]);
fft_1d_rec(f,length);
for(int i=0; i<length; ++i) f[i] = conjf(f[i])/length;
}
