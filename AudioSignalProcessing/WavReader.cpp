#include "stdafx.h"
#include "WavReader.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

WavReader::WavReader(char *url) {
	this->url = url;
	file.open(url, ios::in | ios::binary);
	if (file.fail()) { fputs("File error", stderr); exit(1); }
	read_data();
}

WavReader::~WavReader() {
	if (file.is_open())file.close();
	data.clear();
}

void WavReader::protected_read(char *buffer, int length) {
	file.read(buffer, length);
	if (file.fail()) { fputs("Reading error", stderr); exit(3); }
}

int WavReader::location_of_pattern(char *pattern, int pattern_length, long start_location) {
	char *buffer = (char *)malloc(sizeof(char));
	file.seekg(start_location, ios::beg);
	do {
		protected_read(buffer, 1);
	} while (*buffer != pattern[0]);
	int i = 1;
	protected_read(buffer, 1);
	for (; i < pattern_length && pattern[i] == *buffer; i++) {
		protected_read(buffer, 1);
	}
	int location = (int)file.tellg();
	if (i == pattern_length) {
		location = (int)file.tellg() - pattern_length - 1;
		return location;
	}
	else {
		return location_of_pattern(pattern, pattern_length, location);
	}
}

void WavReader::read_data() {
	char *chunk_id_pat = "RIFF";
	char *format_pat = "WAVE";
	char *subchunk1_id_pat = "fmt ";
	char *subchunk2_id_pat = "data";
	int chunk_id_loc = location_of_pattern(chunk_id_pat, 4, 0);
	file.seekg(chunk_id_loc);
	get_ChunkID();
	get_ChunkSize();
	int format_id_loc = location_of_pattern(format_pat, 4, chunk_id_loc);
	file.seekg(format_id_loc);
	get_Format();
	int subchunk1_id_loc = location_of_pattern(subchunk1_id_pat, 4, format_id_loc);
	file.seekg(subchunk1_id_loc);
	get_Subchunk1ID();
	get_Subchunk1Size();
	get_AudioFormat();
	get_NumChannels();
	get_SampleRate();
	get_ByteRate();
	get_BlockAlign();
	get_BitsPerSample();
	int subchunk2_id_loc = location_of_pattern(subchunk2_id_pat, 4, subchunk1_id_loc);
	file.seekg(subchunk2_id_loc);
	get_Subchunk2ID();
	get_Subchunk2Size();
	get_data();

}
char *WavReader::get_ChunkID() {
	/* ChunkID:
	* byte offset = 0
	* big-endian
	* Contains the letters "RIFF"
	*/
	if (ChunkID_asgnd == false) {
		long size = 4;
		this->ChunkID = (char *)malloc(sizeof(char)*(size + 1));

		file.read(this->ChunkID, size);
		if (file.fail()) { fputs("Reading error (ChunkID)", stderr); exit(3); }
		ChunkID[4] = '\0';
		ChunkID_asgnd = true;
	}
	return this->ChunkID;
}
int WavReader::get_ChunkSize() {
	/* ChunkSize:
	* byte offset = 4
	* little-endian
	* The size of the rest of the chunk following this number
	* minus 8 bytes for the two fields not include in this count:
	* ChunkID and ChunkSize
	*/
	if (ChunkSize_asgnd == false) {
		uint32_t buffer;
		file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
		if (file.fail()) { fputs("Reading error (ChunkSize)", stderr); exit(3); }
		this->ChunkSize = buffer;
		ChunkSize_asgnd = true;
	}
	return this->ChunkSize;
}
char *WavReader::get_Format() {
	/* Format
	* byte offset = 8
	* big-endian
	* Contains the letters "WAVE"
	*/
	if (Format_asgnd == false) {
		long size = 4;
		this->Format = (char *)malloc(sizeof(char)*(size + 1));

		file.read(this->Format, size);
		if (file.fail()) { fputs("Reading error (Format)", stderr); exit(3); }
		Format[4] = '\0';
		Format_asgnd = true;
	}
	return this->Format;
}
char *WavReader::get_Subchunk1ID() {
	/* Subchunk1ID
	* byte offset = 12
	* big-endian
	* Contains the letters "fmt "
	*/
	if (Subchunk1ID_asgnd == false) {
		long size = 4;
		this->Subchunk1ID = (char *)malloc(sizeof(char)*(size + 1));

		file.read(this->Subchunk1ID, size);
		if (file.fail()) { fputs("Reading error (Subchunk1ID)", stderr); exit(3); }
		Subchunk1ID[4] = '\0';
		Subchunk1ID_asgnd = true;
	}
	return this->Subchunk1ID;
}
int WavReader::get_Subchunk1Size() {
	/* Subchunk1Size
	* byte offset = 16
	* little-endian
	* The size of the rest of the subchunk which follows this number.
	*/
	if (Subchunk1Size_asgnd == false) {
		uint32_t buffer;
		file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
		if (file.fail()) { fputs("Reading error (Subchunk1Size)", stderr); exit(3); }
		this->Subchunk1Size = buffer;
		Subchunk1Size_asgnd = true;
	}
	return this->Subchunk1Size;
}
int WavReader::get_AudioFormat() {
	/* AudioFormat
	* byte offset = 20
	* little-endian
	* PCM = 1 (i.e. linear quantization) Values other than 1 indicate
	* some form of compression
	*/
	if (AudioFormat_asgnd == false) {
		uint16_t buffer;
		file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
		if (file.fail()) { fputs("Reading error (AudioFormat)", stderr); exit(3); }
		this->AudioFormat = buffer;
		AudioFormat_asgnd = true;
	}
	return this->AudioFormat;
}
int WavReader::get_NumChannels() {
	/* NumChannels
	* byte offset = 22
	* little-endian
	* Mono = 1, Stereo = 2, etc.
	*/
	if (NumChannels_asgnd == false) {
		uint16_t buffer;
		file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
		if (file.fail()) { fputs("Reading error (NumChannels)", stderr); exit(3); }
		this->NumChannels = buffer;
		NumChannels_asgnd = true;
	}
	return this->NumChannels;
}
int WavReader::get_SampleRate() {
	/* SampleRate
	* byte offset = 24
	* little-endian
	* 8000Hz, 44100Hz, etc
	*/
	if (SampleRate_asgnd == false) {
		uint32_t buffer;
		file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
		if (file.fail()) { fputs("Reading error (SampleRate)", stderr); exit(3); }
		this->SampleRate = buffer;
		SampleRate_asgnd = true;
	}
	return this->SampleRate;
}
int WavReader::get_ByteRate() {
	/* ByteRate
	* byte offset = 28
	* little-endian
	* == SampleRate * NumChannels * BitsPerSample/8
	*/
	if (ByteRate_asgnd == false) {
		uint32_t buffer;
		file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
		if (file.fail()) { fputs("Reading error (ByteRate)", stderr); exit(3); }
		this->ByteRate = buffer;
		ByteRate_asgnd = true;
	}
	return this->ByteRate;
}
int WavReader::get_BlockAlign() {
	/* BlockAlign
	* byte offset = 32
	* little-endian
	* == NumChannels * BitsPerSample/8
	* The number of bytes for one sample including all channels.
	*/
	if (BlockAlign_asgnd == false) {
		uint16_t buffer;
		file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
		if (file.fail()) { fputs("Reading error (BlockAlign)", stderr); exit(3); }
		this->BlockAlign = buffer;
		BlockAlign_asgnd = true;
	}
	return this->BlockAlign;
}
int WavReader::get_BitsPerSample() {
	/* BitsPerSample
	* byte offset = 34
	* little-endian
	* 8 bits = 8, 16 bits = 16, etc.
	*/
	if (BitsPerSample_asgnd == false) {
		uint16_t buffer;
		file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
		if (file.fail()) { fputs("Reading error (BitsPerSample)", stderr); exit(3); }
		this->BitsPerSample = buffer;
		BitsPerSample_asgnd = true;
	}
	return this->BitsPerSample;
}
char *WavReader::get_Subchunk2ID() {
	/* Subchunk2ID
	* byte offset = 36
	* big-endian
	* Contains the letters "data"
	*/
	if (Subchunk2ID_asgnd == false) {
		long size = 4;
		this->Subchunk2ID = (char *)malloc(sizeof(char)*(size + 1));

		file.read(this->Subchunk2ID, size);
		if (file.fail()) { fputs("Reading error (Subchunk2ID)", stderr); exit(3); }
		Subchunk2ID[4] = '\0';
		Subchunk2ID_asgnd = true;
	}
	return this->Subchunk2ID;
}
int WavReader::get_Subchunk2Size() {
	/* Subchunk2Size
	* byte offset = 40
	* little-endian
	* == NumSamples * NumChannels * BitsPerSample/8
	* This is the number of bytes in the data.
	*/
	if (Subchunk2Size_asgnd == false) {
		uint32_t buffer;
		file.read(reinterpret_cast<char *>(&buffer), sizeof(buffer));
		if (file.fail()) { fputs("Reading error (Subchunk2Size)", stderr); exit(3); }
		this->Subchunk2Size = buffer;
		Subchunk2Size_asgnd = true;
	}
	return this->Subchunk2Size;
}
std::vector<uint32_t> WavReader::get_data() {
	/* Data
	* byte offset = 44
	* little-endian
	* The actual sound data.
	*/
	if (data_asgnd == false) {
		char *buffer_c = (char *)malloc(get_Subchunk2Size());
		file.read(buffer_c, get_Subchunk2Size());
		if (get_BitsPerSample() == 16) {
			uint16_t *buffer = reinterpret_cast<uint16_t *>(buffer_c);
			if (file.fail()) { fputs("Reading error (data)", stderr); exit(3); }
			vector<uint32_t> temp(buffer, buffer + get_Subchunk2Size() / sizeof(uint16_t));
			this->data = temp;
		}
		else if (get_BitsPerSample() == 32) {
			uint32_t *buffer = reinterpret_cast<uint32_t *>(buffer_c);
			if (file.fail()) { fputs("Reading error (data)", stderr); exit(3); }
			vector<uint32_t> temp(buffer, buffer + get_Subchunk2Size() / sizeof(uint32_t));
			this->data = temp;
		}
		data_asgnd = true;
	}
	return this->data;
}

void WavReader::print_DataFields(System::Windows::Forms::TextBox^ text_box) {
	char *str = (char *)calloc(52, sizeof(char));
	sprintf(str + strlen(str), "ID: %s\n", get_ChunkID());
	sprintf(str + strlen(str), "Size: %d\n", get_ChunkSize());
	sprintf(str + strlen(str), "Format: %s\n", get_Format());
	sprintf(str + strlen(str), "ID_1: %s\n", get_Subchunk1ID());
	sprintf(str + strlen(str), "Size_1: %d\n", get_Subchunk1Size());
	sprintf(str + strlen(str), "Audio Format: %d\n", get_AudioFormat());
	sprintf(str + strlen(str), "Channels: %d\n", get_NumChannels());
	sprintf(str + strlen(str), "Sample Rate: %d\n", get_SampleRate());
	sprintf(str + strlen(str), "Byte Rate: %d\n", get_ByteRate());
	sprintf(str + strlen(str), "Block Align: %d\n", get_BlockAlign());
	sprintf(str + strlen(str), "Bits per Sample: %d\n", get_BitsPerSample());
	sprintf(str + strlen(str), "ID_2: %s\n", get_Subchunk2ID());
	sprintf(str + strlen(str), "Size_2: %d\n", get_Subchunk2Size());
	System::String^ tb_str = Marshal::PtrToStringAnsi(IntPtr(str));
	text_box->AppendText(tb_str);
}

void WavReader::print_data(FILE *f) {
	std::vector<uint32_t> temp = get_data();
	for (auto &sample : temp) {
		fprintf(f, "%u\n", sample);
	}
}

