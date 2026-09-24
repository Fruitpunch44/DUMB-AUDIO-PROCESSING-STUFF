#include"fft.h"


void fft(float complex in[], size_t num_samples, size_t stride, float complex out[]) {

    // Implementation for Discrete Fourier Transform
    assert(num_samples > 0);

    if(num_samples==1){
        out[0]=in[0];
        return;

    }
    
    //gotten from https://rosettacode.org/wiki/Fast_Fourier_transform#C
    fft(in, num_samples/2, 2*stride, out);
    fft(in+stride, num_samples/2, 2*stride, out+num_samples/2);

    for(size_t k =0;k<num_samples/2;k++){
        float complex even = out[k];
        float complex odd = cexp(-2*pi*I*k/num_samples) * out[k+num_samples/2];
        out[k]= even+odd;
        out[k+num_samples/2]=even-odd;
    }

}

void wrapper_fft(float complex buff[],size_t n){  
    float complex *out = malloc(n * sizeof(float complex));
    if(!out){
        fprintf(stderr,"error in allocation");
        return;
    }
    for (size_t i = 0;i<n;i++){
        out[i]=buff[i];
    }
    fft(buff,n,1,out);
    for (size_t i = 0;i<n;i++){
        buff[i]=out[i];
    }
    free(out);
}



//get amplitude
float get_amplitude(float complex z){
    float a = fabs(creal(z));
    float b = fabs(cimag(z));
    if(a>b){
        return a;
    }else{
        return b;
}
}
void get_magnitude(float complex z[],size_t num){
    float mag [num];
       for(size_t i = 0;i<num;i++){
            float real = fabs(creal(z[i]));
            float img = fabs(cimag(z[i]));
            mag[i] = sqrt(real*real + img*img);
            printf("[%zu]mag vals %2f\n",i,mag[i]);
    }
    }
