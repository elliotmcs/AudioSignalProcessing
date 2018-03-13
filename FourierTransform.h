/*
 * FourierTransform.h
 *
 *  Created on: Dec 21, 2017
 *      Author: Elliot
 */

#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <complex>
#include <valarray>
#include <string>

#ifndef FOURIERTRANSFORM_H_
#define FOURIERTRANSFORM_H_
# define M_PI           3.14159265358979323846  /* pi */
typedef std::complex<double> Complex;

class FourierTransform {
public:
    static void fft(Complex *X, int N) {
        if(N >= 2){
            separate(X, N);   // all evens to lower half, all odds to upper half
            fft(X, N / 2);   // recurse even items
            fft(X + N / 2, N / 2);   // recurse odd  items
            // combine results of two half recursions
            for (int k = 0; k < N / 2; k++) {
                Complex e = X[k];   // even
                Complex o = X[k + N / 2];   // odd
                // w is the "twiddle-factor"
                Complex w = (k == 0) ? 1 : exp(Complex(0, -2. * M_PI * k / N));
                //X[k] = e + w * o;
                //X[k+N/2] = e - w * o;

                //Rounding out the floating point errors
                Complex even = e + w * o;
                even.real(remove_error(even.real(), 5));
                even.imag(remove_error(even.imag(), 5));
                Complex odd = e - w * o;
                odd.real(remove_error(odd.real(), 5));
                odd.imag(remove_error(odd.imag(), 5));

                if (o.real() == 0 && o.imag() == 0 && e.real() == 0
                        && e.imag() == 0) {
                    X[k] = 0;
                    X[k + N / 2] = 0;
                } else if (o.real() == 0 && o.imag() == 0) {
                    X[k] = e;
                    X[k + N / 2] = e;
                } else if (e.real() == 0 && e.imag() == 0) {
                    X[k] = w * o;
                    X[k + N / 2] = -w * o;
                } else {
                    X[k] = even;
                    X[k + N / 2] = odd;
                }
            }
        }
    }
    static void ifft(Complex *X, int N) {
        //F^-1{x} = F{x*}*/N
        /*i.e. The inverse discrete fourier transform is equal to the
         * conjugate forward fourier transform with x conjugate input, all over N
         * where N is the number of samples.
         */
        for(int i = 0; i < N; i++){
            //Conjugate input
            X[i] = std::conj(X[i]);
        }
        fft(X, N);
        for(int j = 0; j < N; j++){
            //Conjugate output
            X[j] = std::conj(X[j]);
            //Divide by N
            X[j].real(X[j].real()/N);
            X[j].imag(X[j].imag()/N);
        }
    }
private:
    static void separate(Complex* a, int n) {
        Complex* b = new Complex[n / 2]; // get temp heap storage
        for (int i = 0; i < n / 2; i++) // copy all odd elements to heap storage
            b[i] = a[i * 2 + 1];
        for (int i = 0; i < n / 2; i++) // copy all even elements to lower-half of a[]
            a[i] = a[i * 2];
        for (int i = 0; i < n / 2; i++) // copy all odd (from heap) to upper-half of a[]
            a[i + n / 2] = b[i];
        delete[] b;                 // delete heap storage
    }
    static double remove_error(double val, int precision) {
        //Scales val by 10^precision, rounds result to nearest integer, then scales by 10^-precision
        double scaled_val = val * pow(10, precision);
        double rounded_val = round(scaled_val);
        return rounded_val * pow(10, -precision);
    }

};

#endif /* FOURIERTRANSFORM_H_ */
