//
// Created by Abdul on 21/04/2026.
//
#include <math.h>
#include "waveform.h"

double sum_phaseA(waveformsample *samples, int count) {
    double sum = 0;

    for (int i = 0; i < count; i++) {
        sum += (samples + i)->phase_A_voltage;
    }

    return sum;
}

double get_phase_voltage(waveformsample *sample, char phase) {
    if (phase == 'A') {
        return sample->phase_A_voltage;
    } else if (phase == 'B') {
        return sample->phase_B_voltage;
    } else {
        return sample->phase_C_voltage;
    }
}

double compute_rms(waveformsample *samples, int count, char phase) {
    double sum_squares = 0.0;

    for (int i = 0; i < count; i++) {
        double voltage = get_phase_voltage(samples + i, phase);
        sum_squares += voltage * voltage;
    }

    return sqrt(sum_squares / count);
}

double compute_peak_to_peak(waveformsample *samples, int count, char phase) {
    double min = get_phase_voltage(samples, phase);
    double max = get_phase_voltage(samples, phase);

    for (int i = 1; i < count; i++) {
        double voltage = get_phase_voltage(samples + i, phase);

        if (voltage < min) {
            min = voltage;
        }

        if (voltage > max) {
            max = voltage;
        }
    }

    return max - min;
}

double compute_dc_offset(waveformsample *samples, int count, char phase) {
    double sum = 0;

    for (int i = 0; i < count; i++) {
        double value = get_phase_voltage(samples + i, phase);
        sum += value;
    }

    return sum / count;
}

int detect_clipping(waveformsample *samples, int count, char phase) {
    int clipped = 0;

    for (int i = 0; i < count; i++) {
        double value = get_phase_voltage(samples + i, phase);

        if (fabs(value) >= 324.9) {
            clipped = 1;
            break;  // no need to continue once found
        }
    }

    return clipped;
}