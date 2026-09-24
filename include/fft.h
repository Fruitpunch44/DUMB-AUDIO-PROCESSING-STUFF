//#include"raylib.h"
#include<math.h>
#include<string.h>
#include<complex.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<assert.h>

#define pi 3.14159265358979323846f
#define N 1<<13

typedef struct {
    float complex in [N];
    float complex out[N];
}Global_vals;

/*what is this discrte fourier tra*/
void fft(float complex in[], size_t num_samples, size_t stride, float complex out[]);
void wrapper_fft(float complex buff[],size_t n);
void get_magnitude(float complex z[] ,size_t num);


