#ifndef FILTERHANDLER_H
#define FILTERHANDLER_H



#include <QMainWindow>

#include "WavReader.h"
#include "WavWriter.h"
#include "AudioFilters.h"

using namespace std;

typedef std::complex<double> Complex;

class FilterHandler
{
public:
    FilterHandler(char *url);
    void applyLPFilter(double cutoff, double falloff);
    void applyHPFilter(double cutoff, double falloff);
    void applyBPFilter(double cutoff_1, double cutoff_2, double falloff);
    void applyBRFilter(double cutoff_1, double cutoff_2, double falloff);
    void applyCMBFilter(double delay, double amplitude);
    void exportFile(char *url);
    ~FilterHandler();
private:
    char *url;
    size_t num_samples;
    int num_samples_log;
    size_t real_size;
    std::vector<Complex> *samples;
    enum FilterType {LP, HP, BP, BR, CMB};
    vector<uint32_t> data;
    WavReader *wav_r;
    WavWriter *wav_w;
};

#endif // FILTERHANDLER_H
