/*
 * WavWriter.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: Elliot
 */
#include "WavWriter.h"


WavWriter::WavWriter(uint16_t audio_format, uint16_t num_channels, uint32_t sample_rate, uint16_t bits_per_sample, vector<uint32_t> data) {
    set_AudioFormat(audio_format);
    set_NumChannels(num_channels);
    set_SampleRate(sample_rate);
    set_BitsPerSample(bits_per_sample);
    set_data(data);

    uint32_t byte_rate = sample_rate*num_channels*bits_per_sample/8;
    uint16_t block_align = num_channels*bits_per_sample/8;

    set_ByteRate(byte_rate);
    set_BlockAlign(block_align);
}

WavWriter::~WavWriter() {}

void WavWriter::set_AudioFormat(uint16_t audio_format){
    this->AudioFormat = audio_format;
}
void WavWriter::set_NumChannels(uint16_t num_channels){
    this->NumChannels = num_channels;
}
void WavWriter::set_SampleRate(uint32_t sample_rate){
    this->SampleRate = sample_rate;
}
void WavWriter::set_BitsPerSample(uint16_t bits_per_sample){
    this->BitsPerSample = bits_per_sample;
}
void WavWriter::set_data(vector<uint32_t> data){
    this->data = data;
}
void WavWriter::set_ByteRate(uint32_t byte_rate){
    this->ByteRate = byte_rate;
}
void WavWriter::set_BlockAlign(uint16_t block_align){
    this->BlockAlign = block_align;
}

void WavWriter::int32_to_str(uint32_t n, char *target){
    target[0] = (char)(n % 256);
    target[1] = (char)((n >> 8) % 256);
    target[2] = (char)((n >> 16) % 256);
    target[3] = (char)((n >> 24) % 256);
}
void WavWriter::int16_to_str(uint16_t n, char *target){
    target[0] = (char)(n % 256);
    target[1] = (char)((n >> 8) % 256);
}

void WavWriter::generate_wavfile(char *url){
    this->url = url;
    size_t size = data.size();
    uint32_t subchunk2_size = this->data.size()*this->NumChannels*(this->BitsPerSample/8);
    uint32_t subchunk1_size = (this->AudioFormat == 1) ? 16 : 16;
    uint32_t chunk_size = 20 + subchunk1_size + subchunk2_size;
    printf("Size: %d\n", chunk_size);
    printf("Size_1: %d\n", subchunk1_size);
    printf("Size_2: %d\n", subchunk2_size);
    ofstream file;
    char *chunk_size_s = (char *)malloc(sizeof(char)*4);
    char *subchunk1_size_s = (char *)malloc(sizeof(char)*4);
    char *subchunk2_size_s = (char *)malloc(sizeof(char)*4);
    char *audio_format_s = (char *)malloc(sizeof(char)*2);
    char *num_channels_s = (char *)malloc(sizeof(char)*2);
    char *sample_rate_s = (char *)malloc(sizeof(char)*4);
    char *byte_rate_s = (char *)malloc(sizeof(char)*4);
    char *block_align_s = (char *)malloc(sizeof(char)*2);
    char *bits_per_sample_s = (char *)malloc(sizeof(char)*2);

    int32_to_str(chunk_size, chunk_size_s);
    int32_to_str(subchunk1_size, subchunk1_size_s);
    int32_to_str(subchunk2_size, subchunk2_size_s);
    int16_to_str(this->AudioFormat, audio_format_s);
    int16_to_str(this->NumChannels, num_channels_s);
    int32_to_str(this->SampleRate, sample_rate_s);
    int32_to_str(this->ByteRate, byte_rate_s);
    int16_to_str(this->BlockAlign, block_align_s);
    int16_to_str(this->BitsPerSample, bits_per_sample_s);

    file.open(url, ios::out | ios::binary);
    file.write("RIFF", 4);
    file.write(chunk_size_s, 4);
    file.write("WAVE", 4);
    file.write("fmt ", 4);
    file.write(subchunk1_size_s, 4);
    file.write(audio_format_s, 2);
    file.write(num_channels_s, 2);
    file.write(sample_rate_s, 4);
    file.write(byte_rate_s, 4);
    file.write(block_align_s, 2);
    file.write(bits_per_sample_s, 2);
    file.write("data", 4);
    file.write(subchunk2_size_s, 4);
    for(int i = this->data.size()-1; i >= 0; i--){
        if(this->BitsPerSample == 16){
            char *sample_s = (char *)malloc(sizeof(char)*2);
            int16_to_str(this->data[i], sample_s);
            file.write(sample_s, 2);
        }else if(this->BitsPerSample == 32){
            char *sample_s = (char *)malloc(sizeof(char)*4);
            int32_to_str(this->data[i], sample_s);
            file.write(sample_s, 4);
        }
    }
    file.close();
}


void WavWriter::print_DataFields(){
    printf("Audio Format: %d\n", this->AudioFormat);
    printf("Channels: %d\n", this->NumChannels);
    printf("Sample Rate: %d\n", this->SampleRate);
    printf("Byte Rate: %d\n", this->ByteRate);
    printf("Block Align: %d\n", this->BlockAlign);
    printf("Bits per Sample: %d\n", this->BitsPerSample);
}

void WavWriter::print_data(FILE *f){
    /*uint32_t *temp = (uint32_t *)this->data;
    for(int i = 0; i < get_Subchunk2Size(); i++){
        fprintf(f, "%u\n", temp[i]);
    }*/
}
