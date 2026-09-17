#include"raylib.h"
#include<math.h>
#include<string.h>
#include<complex.h>
#include<assert.h>

#define pi 3.14159265358979323846f

/*what is this discrte fourier tra*/
void fft(float in[], size_t num_samples, size_t stride, float complex out[]);
