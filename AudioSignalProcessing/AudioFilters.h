#pragma once
/*
* AudioFilters.h
*
*  Created on: Dec 21, 2017
*      Author: Elliot
*/
#include "stdafx.h"
/*
#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <complex>
#include <valarray>
#include <string>
*/
#include "FourierTransform.h"

#define sinc(x) x == 0 ? 1 : sin(M_PI*x)/(M_PI*x)

typedef std::complex<double> Complex;

class AudioFilters {
public:
	static void signal_to_file(char *file_name, Complex *signal, int num_samples) {
		FILE *f = fopen(file_name, "w");
		for (int i = 0; i < num_samples; i++) {
			char c = (signal[i].real() < 0) ? '-' : '+';
			fprintf(f, "%f%c%fi", signal[i].real(), c, abs(signal[i].imag()));
			if (i != num_samples - 1)fprintf(f, "\n");
		}
		fclose(f);
	}

	static void Lowpass_Filter(Complex *signal, int sample_rate,
		int num_samples, double cutoff, double falloff) {
		Complex *lpr = lowpass_response(sample_rate, num_samples, cutoff, falloff);
		FourierTransform::fft(signal, num_samples);
		FourierTransform::fft(lpr, num_samples);
		// Scale factor ensures there is no amplification in the filter
		double scale_factor = pow(abs(lpr[0]), -1);
		for (int t = 0; t < num_samples; t++) {
			signal[t].real(signal[t].real() * scale_factor * abs(lpr[t]));
			signal[t].imag(signal[t].imag() * scale_factor * abs(lpr[t]));
		}
		FourierTransform::ifft(signal, num_samples);
	}

	static void Highpass_Filter(Complex *signal, int sample_rate, int num_samples, double cutoff, double falloff) {
		Complex *lpr = lowpass_response(sample_rate, num_samples, cutoff, falloff);
		FourierTransform::fft(signal, num_samples);
		FourierTransform::fft(lpr, num_samples);
		// Scale factor ensures there is no amplification in the filter
		double scale_factor = pow(abs(lpr[0]), -1);
		for (int t = 0; t < num_samples; t++) {
			// Highpass filter == amplitude reversed + amplitude shifted Lowpass filter
			signal[t].real(signal[t].real() * (scale_factor * -abs(lpr[t]) + 1));
			signal[t].imag(signal[t].imag() * (scale_factor * -abs(lpr[t]) + 1));
		}
		FourierTransform::ifft(signal, num_samples);
	}

	static void Bandpass_Filter(Complex *signal, int sample_rate, int num_samples, double cutoff_low, double cutoff_high, double falloff) {
		Complex *lpr1 = lowpass_response(sample_rate, num_samples, cutoff_low, falloff);
		Complex *lpr2 = lowpass_response(sample_rate, num_samples, cutoff_high, falloff);
		FourierTransform::fft(signal, num_samples);
		FourierTransform::fft(lpr1, num_samples);
		FourierTransform::fft(lpr2, num_samples);
		double scale_factor1 = pow(abs(lpr1[0]), -1);
		double scale_factor2 = pow(abs(lpr2[0]), -1);

		for (int t = 0; t < num_samples; t++) {
			// Bandpass filter == Lowpass filter * Highpass filter
			signal[t].real(signal[t].real() * (scale_factor1 * -abs(lpr1[t]) + 1) * (scale_factor2 * abs(lpr2[t])));
			signal[t].imag(signal[t].imag() * (scale_factor1 * -abs(lpr1[t]) + 1) * (scale_factor2 * abs(lpr2[t])));
		}
		FourierTransform::ifft(signal, num_samples);
	}

	static void Bandreject_Filter(Complex *signal, int sample_rate, int num_samples, double cutoff_low, double cutoff_high, double falloff) {
		Complex *lpr1 = lowpass_response(sample_rate, num_samples, cutoff_low, falloff);
		Complex *lpr2 = lowpass_response(sample_rate, num_samples, cutoff_high, falloff);
		FourierTransform::fft(signal, num_samples);
		FourierTransform::fft(lpr1, num_samples);
		FourierTransform::fft(lpr2, num_samples);
		double scale_factor1 = pow(abs(lpr1[0]), -1);
		double scale_factor2 = pow(abs(lpr2[0]), -1);

		for (int t = 0; t < num_samples; t++) {
			// Bandreject filter == Lowpass filter + Highpass filter
			signal[t].real(signal[t].real() * ((scale_factor1 * abs(lpr1[t])) + (scale_factor2 * -abs(lpr2[t]) + 1)));
			signal[t].imag(signal[t].imag() * ((scale_factor1 * abs(lpr1[t])) + (scale_factor2 * -abs(lpr2[t]) + 1)));
		}
		FourierTransform::ifft(signal, num_samples);
	}

	static void Comb_Filter(Complex *signal, int num_samples, int sample_rate, double delay, float scaling_factor) {
		// Feedforward comb filter
		int delay_s = delay * sample_rate;		// s * samples/s = sample
		Complex *cr = comb_response(num_samples, delay_s, scaling_factor);

		FourierTransform::fft(signal, num_samples);
		FourierTransform::fft(cr, num_samples);

		for (int t = 0; t < num_samples; t++) {
			signal[t].real(signal[t].real() * abs(cr[t]));
		}
		FourierTransform::ifft(signal, num_samples);
	}

public:

	static Complex *lowpass_response(int sample_rate, int num_samples, double cutoff, double falloff) {
		Complex *signal = (Complex *)malloc(sizeof(Complex) * num_samples);
		double f_c = cutoff / (double)sample_rate;
		double b = falloff / (double)sample_rate;
		double N = 4.0 / b;
		for (int t = 0; t < num_samples; t++) {
			// Lowpass impulse response = sinc * backman window
			// f_c is the cutoff, N - 1 is the falloff
			double val = 2 * f_c*sinc(2 * f_c*(t - (N - 1) / 2.0)) * (0.42 - 0.5*cos(2 * M_PI*t / (N - 1)) + 0.08*cos(4 * M_PI*t / (N - 1)));
			// Window needs to be truncated before the second period
			if ((double)t / ((double)N - 1) > 1)val = 0;
			signal[t] = Complex(val, 0);
		}

		return signal;
	}

	static Complex *lowpass_magnitude_response(int sample_rate, int num_samples, double cutoff, double falloff) {
		Complex *lpr = lowpass_response(sample_rate, num_samples, cutoff, falloff);
		Complex *lpr_mag = (Complex *)malloc(num_samples * sizeof(Complex));
		FourierTransform::fft(lpr, num_samples);
		double scale_factor = pow(abs(lpr[0]), -1);
		for (int i = 0; i < num_samples; i++) {
			lpr_mag[i] = scale_factor * abs(lpr[i]);
		}
		free(lpr);
		return lpr_mag;
	}
	static Complex *highpass_magnitude_response(int sample_rate, int num_samples, double cutoff, double falloff) {
		Complex *lpr = lowpass_response(sample_rate, num_samples, cutoff, falloff);
		Complex *hpr_mag = (Complex *)malloc(num_samples * sizeof(Complex));
		FourierTransform::fft(lpr, num_samples);
		double scale_factor = pow(abs(lpr[0]), -1);
		for (int i = 0; i < num_samples; i++) {
			hpr_mag[i] = 1 - scale_factor * abs(lpr[i]);
		}
		free(lpr);
		return hpr_mag;
	}
	static Complex *bandpass_magnitude_response(int sample_rate, int num_samples, double cutoff_low, double cutoff_high, double falloff) {
		Complex *lpr1 = lowpass_response(sample_rate, num_samples, cutoff_low, falloff);
		Complex *lpr2 = lowpass_response(sample_rate, num_samples, cutoff_high, falloff);
		Complex *bpr_mag = (Complex *)malloc(num_samples * sizeof(Complex));
		FourierTransform::fft(lpr1, num_samples);
		FourierTransform::fft(lpr2, num_samples);
		double scale_factor1 = pow(abs(lpr1[0]), -1);
		double scale_factor2 = pow(abs(lpr2[0]), -1);
		for (int i = 0; i < num_samples; i++) {
			bpr_mag[i] = (scale_factor1 * abs(lpr1[i])) - (scale_factor2 * abs(lpr2[i]));
		}
		free(lpr1);
		free(lpr2);
		return bpr_mag;
	}
	static Complex *bandreject_magnitude_response(int sample_rate, int num_samples, double cutoff_low, double cutoff_high, double falloff) {
		Complex *lpr1 = lowpass_response(sample_rate, num_samples, cutoff_low, falloff);
		Complex *lpr2 = lowpass_response(sample_rate, num_samples, cutoff_high, falloff);
		Complex *brr_mag = (Complex *)malloc(num_samples * sizeof(Complex));
		FourierTransform::fft(lpr1, num_samples);
		FourierTransform::fft(lpr2, num_samples);
		double scale_factor1 = pow(abs(lpr1[0]), -1);
		double scale_factor2 = pow(abs(lpr2[0]), -1);
		for (int i = 0; i < num_samples; i++) {
			brr_mag[i] = scale_factor1 * abs(lpr1[i]) + (-scale_factor2 * abs(lpr2[i]) + 1);
		}
		free(lpr1);
		free(lpr2);
		return brr_mag;
	}
	static Complex *comb_magnitude_response(int sample_rate, int num_samples, double delay, double scaling_factor) {
		// Feedforward comb filter
		int delay_s = delay * sample_rate;		// s * samples/s = sample
		Complex *cr = comb_response(num_samples, delay_s, scaling_factor);
		Complex *cr_mag = (Complex *)malloc(num_samples * sizeof(Complex));
		FourierTransform::fft(cr, num_samples);

		for (int t = 0; t < num_samples; t++) {
			cr_mag[t] = abs(cr[t]);
		}
		return cr_mag;
	}

	static Complex *comb_response(int num_samples, int delay, float scaling_factor) {
		/* Impulse repsonse of feedforward comb filter is magnitude 1 impulse at t = 0 and
		* magnitude scaling_factor impulse at t = delay(in samples).
		*/
		Complex *signal = (Complex *)malloc(sizeof(Complex) * num_samples);
		signal[0] = 1;
		for (int t = 1; t < num_samples; t++) {
			signal[t] = (t == delay) ? scaling_factor : 0;
		}
		return signal;
	}
};
