#pragma once

#include "stdafx.h"
using namespace std;


class WavReader {
public:
	char *url;
	char *ChunkID = nullptr;
	uint32_t ChunkSize = -1;
	char *Format = nullptr;
	char *Subchunk1ID = nullptr;
	uint32_t Subchunk1Size = -1;
	uint16_t AudioFormat = -1;
	uint16_t NumChannels = -1;
	uint32_t SampleRate = -1;
	uint32_t ByteRate = -1;
	uint16_t BlockAlign = -1;
	uint16_t BitsPerSample = -1;
	char *Subchunk2ID = nullptr;
	uint32_t Subchunk2Size = -1;
	std::vector<uint32_t> data;

	char *get_ChunkID();
	int get_ChunkSize();
	char *get_Format();
	char *get_Subchunk1ID();
	int get_Subchunk1Size();
	int get_AudioFormat();
	int get_NumChannels();
	int get_SampleRate();
	int get_ByteRate();
	int get_BlockAlign();
	int get_BitsPerSample();
	char *get_Subchunk2ID();
	int get_Subchunk2Size();
	vector<uint32_t> get_data();
	void print_DataFields(System::Windows::Forms::TextBox^ text_box);
	void print_data(FILE *f);
	void read_data();
	WavReader(char *url);

	virtual ~WavReader();
private:
	ifstream file;
	bool ChunkID_asgnd = false, ChunkSize_asgnd = false, Format_asgnd = false, Subchunk1ID_asgnd = false, Subchunk1Size_asgnd = false, AudioFormat_asgnd = false, NumChannels_asgnd = false, SampleRate_asgnd = false, ByteRate_asgnd = false, BlockAlign_asgnd = false, BitsPerSample_asgnd = false, Subchunk2ID_asgnd = false, Subchunk2Size_asgnd = false, data_asgnd = false;
	int location_of_pattern(char *pattern, int pattern_length, long start_location);
	void protected_read(char *buffer, int length);
};

