#include<math.h>
#include<complex.h>
#include<stdio.h>
#include<assert.h>

#define pi 3.14159265358979323846f
void fft(float complex in[],float complex out [],size_t num_samps,size_t stride){
    assert(num_samps>0);

    if(num_samps==1){
        out[0]=in[0];
        return;
    }

    fft(in,out,num_samps/2,2*stride);
    fft(in+stride,out+num_samps/2,num_samps/2,2*stride);

    //frequency bias
    for(size_t k = 0 ;k<num_samps/2;k++){
        float complex even = out[k];
        float complex odd = cexp(-2*pi*I*k/num_samps) * out[k+num_samps/2];
        out[k]=even+odd;
        out[k+num_samps/2]=even-odd;
    }

}
void otherfft(float complex buff[],size_t n){
    float complex out[n];
    for (size_t i = 0;i<n;i++){
        out[i]=buff[i];
    }
    fft(buff,out,n,1);
    for (size_t i = 0;i<n;i++){
        buff[i]=out[i];
    }
}
 
void show(const char * s, float complex buf[]) {
	printf("%s", s);
	for (int i = 0; i < 9; i++)
		if (!cimag(buf[i]))
			printf("%g ", creal(buf[i]));
		else
			printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
}
int main(int argc,char *argv[]){

    	 float complex buf[] = {1, 1, 1, 1, 0, 0, 0, 0,2};
         otherfft(buf,8);
         show("fft:",buf);

         return 0;

}