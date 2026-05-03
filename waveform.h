//
// Created by Abdul on 21/04/2026.
//

#ifndef COURSEWORK_WAVEFORM_H
#define COURSEWORK_WAVEFORM_H


typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;
} waveformsample;

double sum_phaseA(waveformsample *samples, int count);

double get_phase_voltage(waveformsample *sample, char phase);
double compute_rms(waveformsample *samples, int count, char phase);
double compute_peak_to_peak(waveformsample *samples, int count, char phase);

#endif //COURSEWORK_WAVEFORM_H
