#include"fft.h"


void fft(float in[], size_t num_samples, size_t stride, float complex out[]) {

    // Implementation for Discrete Fourier Transform
    assert(num_samples > 0);

    if(num_samples==1){
        out[0]=in[0];
        return;

    }
    
    fft(in, num_samples/2, 2*stride, out);
    fft(in+stride, num_samples/2, 2*stride, out+num_samples/2);

    for(size_t k =0;k<num_samples/2;k++){
        float time = (float)k/2;
        float complex odd = cexp(-2*pi*I*time/num_samples * k);
        float complex even = out[k];
        out[k]= even+odd;
        out[k+num_samples/2]=even-odd;
    }

}