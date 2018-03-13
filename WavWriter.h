/*
 * WavWriter.h
 *
 *  Created on: Dec 13, 2017
 *      Author: Elliot
 */

#ifndef WAVWRITER_H_
#define WAVWRITER_H_

#include <QMainWindow>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>


using namespace std;

class WavWriter {
public:
    char *url;
    uint16_t AudioFormat = -1;
    uint16_t NumChannels = -1;
    uint32_t SampleRate = -1;
    uint32_t ByteRate = -1;
    uint16_t BlockAlign = -1;
    uint16_t BitsPerSample = -1;
    vector<uint32_t> data;

    WavWriter(uint16_t audio_format, uint16_t num_channels, uint32_t sample_rate, uint16_t bits_per_sample, vector<uint32_t> data);
    virtual ~WavWriter();
    void set_AudioFormat(uint16_t audio_format);
    void set_NumChannels(uint16_t num_channels);
    void set_SampleRate(uint32_t sample_rate);
    void set_BitsPerSample(uint16_t bits_per_sample);
    void set_data(vector<uint32_t> data);
    void print_DataFields();
    void print_data(FILE *f);
    void generate_wavfile(char *url);
private:
    void set_ByteRate(uint32_t byte_rate);
    void set_BlockAlign(uint16_t block_align);
    void int32_to_str(uint32_t n, char *target);
    void int16_to_str(uint16_t n, char *target);
};
#endif /* WAVWRITER_H_ */
