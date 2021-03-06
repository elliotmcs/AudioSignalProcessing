#include "FilterHandler.h"

FilterHandler::FilterHandler(char *url)
{
    this->url = url;
    wav_r = new WavReader(url);
    wav_r->print_DataFields();
    this->data = wav_r->get_data();
    reverse(data.begin(), data.end());
    real_size = data.size();
    num_samples_log = ceil(log2(real_size));
    num_samples = (size_t) pow(2, num_samples_log);
    printf("num_samples: %lu\n", num_samples);
    samples = new std::vector<Complex>();
    for (size_t i = 0; i < num_samples; i++) {
        Complex *c = new Complex(0, 0);
        if (i < real_size) {
            int val = (int) data[i];
            val = (val > pow(2, wav_r->get_BitsPerSample() - 1)) ?
                    val - pow(2, wav_r->get_BitsPerSample()) : val;
            c->real(val);
        } else {
            c->real(0);
        }
        samples->push_back(*c);
    }
}
void FilterHandler::applyLPFilter(double cutoff, double falloff) {
    AudioFilters::Lowpass_Filter(samples, wav_r->get_SampleRate(), num_samples, cutoff, falloff);
}
void FilterHandler::applyHPFilter(double cutoff, double falloff){
    AudioFilters::Highpass_Filter(samples, wav_r->get_SampleRate(), num_samples, cutoff, falloff);
}
void FilterHandler::applyBPFilter(double cutoff_1, double cutoff_2, double falloff){
    AudioFilters::Bandpass_Filter(samples, wav_r->get_SampleRate(), num_samples, cutoff_1, cutoff_2, falloff);
}
void FilterHandler::applyBRFilter(double cutoff_1, double cutoff_2, double falloff){
    AudioFilters::Bandreject_Filter(samples, wav_r->get_SampleRate(), num_samples, cutoff_1, cutoff_2, falloff);
}
void FilterHandler::applyCMBFilter(double delay, double amplitude){
    AudioFilters::Comb_Filter(samples, wav_r->get_SampleRate(), num_samples, delay, amplitude);
}
void FilterHandler::exportFile(char *url){
    vector<uint32_t> data_2;
    for (size_t i = 0; i < real_size; i++) {
        data_2.push_back((uint32_t) samples->at(i).real());
    }
    wav_w = new WavWriter(wav_r->get_AudioFormat(),
            wav_r->get_NumChannels(), wav_r->get_SampleRate(),
            wav_r->get_BitsPerSample(), data_2);

    wav_w->generate_wavfile(url);
}
FilterHandler::~FilterHandler(){
    delete this;
}
