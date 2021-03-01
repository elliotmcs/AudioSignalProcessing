/*
 * AudioFilters.h
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

#include "FourierTransform.h"

#ifndef AUDIOFILTERS_H_
#define AUDIOFILTERS_H_
# define M_PI           3.14159265358979323846  /* pi */
#define sinc(x) x == 0 ? 1 : sin(M_PI*x)/(M_PI*x)

typedef std::complex<double> Complex;

class AudioFilters {
public:
        static void signal_to_file(char *file_name, std::vector<Complex> *signal, int num_samples){
                FILE *f = fopen(file_name, "w");
                for(int i = 0; i < num_samples; i++){
                        char c = (signal->at(i).real() < 0) ? '-' : '+';
                        fprintf(f, "%f%c%fi", signal->at(i).real(), c, abs(signal->at(i).imag()));
                        if(i != num_samples - 1)fprintf(f, "\n");
                }
                fclose(f);
        }

        static void Lowpass_Filter(std::vector<Complex> *signal, size_t sample_rate,
                        size_t num_samples, double cutoff, double falloff) {
                Complex * LPR = FourierTransform::fft(lowpass_response(sample_rate, num_samples, cutoff, falloff), num_samples);
                Complex * X = FourierTransform::fft(signal->data(), num_samples);
                // Scale factor ensures there is no amplification in the filter
                double scale_factor = pow(abs(LPR[0]), -1);
                for (size_t t = 0; t < num_samples; t++) {
                    Complex c = Complex(X[t].real() * scale_factor * abs(LPR[t]),
                                        X[t].imag() * scale_factor * abs(LPR[t]));
                    X[t] = c;
                }
                Complex * x = FourierTransform::ifft(X, num_samples);
                for (size_t t = 0; t < num_samples; t++) {
                    signal->at(t) = x[t];
                }
        }

        static void Highpass_Filter(std::vector<Complex> *signal, size_t sample_rate, size_t num_samples, double cutoff, double falloff){
                Complex *LPR = FourierTransform::fft(lowpass_response(sample_rate, num_samples, cutoff, falloff), num_samples);
                Complex * X = FourierTransform::fft(signal->data(), num_samples);
                // Scale factor ensures there is no amplification in the filter
                double scale_factor = pow(abs(LPR[0]), -1);
                for (size_t t = 0; t < num_samples; t++) {
                        // Highpass filter == amplitude reversed + amplitude shifted Lowpass filter
                    Complex c = Complex(X[t].real() * (scale_factor * -abs(LPR[t]) + 1),
                                        X[t].imag() * (scale_factor * -abs(LPR[t]) + 1));
                    X[t] = c;
                }
                Complex * x = FourierTransform::ifft(X, num_samples);
                for (size_t t = 0; t < num_samples; t++) {
                    signal->at(t) = x[t];
                }
        }

        static void Bandpass_Filter(std::vector<Complex> *signal, size_t sample_rate, size_t num_samples, double cutoff_low, double cutoff_high, double falloff){
                Complex *lpr1 = lowpass_response(sample_rate, num_samples, cutoff_low, falloff);
                Complex *lpr2 = lowpass_response(sample_rate, num_samples, cutoff_high, falloff);
                Complex * X = FourierTransform::fft(signal->data(), num_samples);
                Complex * LPR1 = FourierTransform::fft(lpr1, num_samples);
                Complex * LPR2 = FourierTransform::fft(lpr2, num_samples);
                double scale_factor1 = pow(abs(LPR1[0]), -1);
                double scale_factor2 = pow(abs(LPR2[0]), -1);

                for (size_t t = 0; t < num_samples; t++) {
                        // Bandpass filter == Lowpass filter * Highpass filter
                    Complex c = Complex(X[t].real() * (scale_factor1 * -abs(LPR1[t]) + 1) * (scale_factor2 * abs(LPR2[t])),
                                        X[t].imag() * (scale_factor1 * -abs(LPR1[t]) + 1) * (scale_factor2 * abs(LPR2[t])));
                    X[t] = c;
                }
                Complex * x = FourierTransform::ifft(X, num_samples);
                for (size_t t = 0; t < num_samples; t++) {
                    signal->at(t) = x[t];
                }
        }

        static void Bandreject_Filter(std::vector<Complex> *signal, size_t sample_rate, size_t num_samples, double cutoff_low, double cutoff_high, double falloff){
                Complex *LPR1 = FourierTransform::fft(lowpass_response(sample_rate, num_samples, cutoff_low, falloff), num_samples);
                Complex *LPR2 = FourierTransform::fft(lowpass_response(sample_rate, num_samples, cutoff_high, falloff), num_samples);
                Complex * X = FourierTransform::fft(signal->data(), num_samples);
                double scale_factor1 = pow(abs(LPR1[0]), -1);
                double scale_factor2 = pow(abs(LPR2[0]), -1);

                for (size_t t = 0; t < num_samples; t++) {
                        // Bandreject filter == Lowpass filter + Highpass filter
                    Complex c = Complex(X[t].real() * ((scale_factor1 * abs(LPR1[t])) + (scale_factor2 * -abs(LPR2[t]) + 1)),
                                        X[t].imag() * ((scale_factor1 * abs(LPR1[t])) + (scale_factor2 * -abs(LPR2[t]) + 1)));
                    X[t] = c;
                }
                Complex * x = FourierTransform::ifft(X, num_samples);
                for (size_t t = 0; t < num_samples; t++) {
                    signal->at(t) = x[t];
                }
        }

        static void Comb_Filter(std::vector<Complex> *signal, size_t sample_rate, size_t num_samples, double delay, double scaling_factor){
                // Feedforward comb filter
                int delay_s = delay * sample_rate;		// s * samples/s = sample
                Complex *CR = FourierTransform::fft(comb_response(num_samples, delay_s, scaling_factor), num_samples);

                Complex * X = FourierTransform::fft(signal->data(), num_samples);

                for(size_t t = 0; t < num_samples; t++){
                    Complex c = Complex(X[t].real() * CR[t].real() - X[t].imag() - CR[t].imag(),
                                        X[t].real() * CR[t].imag() + X[t].imag() * CR[t].real());
                    X[t] = c;
                }
                Complex * x = FourierTransform::ifft(X, num_samples);
                for (size_t t = 0; t < num_samples; t++) {
                    signal->at(t) = x[t];
                }
        }

private:

        static Complex *lowpass_response(int sample_rate, int num_samples, double cutoff, double falloff) {
                Complex *signal = (Complex *) malloc(sizeof(Complex) * num_samples);
                double f_c = cutoff / (double)sample_rate;
                double b = falloff / (double)sample_rate;
                double N = 4.0 / b;
                for (int t = 0; t < num_samples; t++) {
                        // Lowpass impulse response = sinc * backman window
                        // f_c is the cutoff, N - 1 is the falloff
                        double val = 2*f_c*sinc(2*f_c*(t - (N - 1)/2.0)) * (0.42 - 0.5*cos(2*M_PI*t/(N - 1)) + 0.08*cos(4*M_PI*t/(N - 1)));
                        // Window needs to be truncated before the second period
                        if((double)t/((double)N - 1) > 1)val = 0;
                        signal[t] = Complex(val, 0);
                }

                return signal;
        }

        static Complex *comb_response(int num_samples, int delay, double scaling_factor){
                /* Impulse repsonse of feedforward comb filter is magnitude 1 impulse at t = 0 and
                * magnitude scaling_factor impulse at t = delay(in samples).
                */
                Complex *signal = (Complex *) calloc(num_samples, sizeof(Complex));
                signal[0] = 1;
                /*for(int t = 1; t < num_samples; t++){
                        signal[t] = (t == delay) ? scaling_factor : 0;
                }*/
                if(delay < num_samples) signal[delay] = scaling_factor;
                return signal;
        }
};

#endif /* AUDIOFILTERS_H_ */
