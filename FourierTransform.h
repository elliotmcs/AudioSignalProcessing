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
    static Complex * fft(Complex *x, size_t N) {
        Complex * X = (Complex *)malloc(sizeof(Complex) * N);
        if(N >= 2){
            size_t half_N = N >> 1;
//            separate(X, N);   // all evens to lower half, all odds to upper half
            Complex * x_even = (Complex *)malloc(half_N * sizeof(Complex));
            Complex * x_odd = (Complex *)malloc(half_N * sizeof(Complex));
            for (size_t i = 0; i < half_N; i++) {
                x_even[i] = x[2 * i];
                x_odd[i] = x[2 * i + 1];
            }
            Complex * X_even = fft(x_even, half_N);   // recurse even items
            Complex * X_odd = fft(x_odd, half_N);   // recurse odd  items
            // combine results of two half recursions
            for (size_t k = 0; k < half_N; k++) {
                Complex e = X_even[k];   // even
                Complex o = X_odd[k];   // odd
                // w is the "twiddle-factor"
                Complex w = (k == 0) ? 1 : exp(Complex(0, -2. * M_PI * (double)k / (double)N));
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
                    X[k + half_N] = 0;
                } else if (o.real() == 0 && o.imag() == 0) {
                    X[k] = e;
                    X[k + half_N] = e;
                } else if (e.real() == 0 && e.imag() == 0) {
                    X[k] = w * o;
                    X[k + half_N] = -w * o;
                } else {
                    X[k] = even;
                    X[k + half_N] = odd;
                }
            }
        } else {
            X = x;
        }
        return X;
    }
    static Complex * ifft(Complex *X, size_t N) {
        //F^-1{x} = F{x*}*/N
        /*i.e. The inverse discrete fourier transform is equal to the
         * conjugate forward fourier transform with x conjugate input, all over N
         * where N is the number of samples.
         */
        Complex * x = (Complex *)malloc(sizeof(Complex) * N);
        for(size_t i = 0; i < N; i++){
            //Conjugate input
            x[i] = std::conj(X[i]);
        }
        x = fft(x, N);
        for(size_t j = 0; j < N; j++){
            //Conjugate output
            x[j] = std::conj(x[j]);
            //Divide by N
            x[j].real(x[j].real()/N);
            x[j].imag(x[j].imag()/N);
        }
        return x;
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
