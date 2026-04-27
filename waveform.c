//
// Created by Abdul on 21/04/2026.
//
#include "waveform.h"

double sum_phaseA(waveformsample *samples, int count) {
    double sum = 0;

    for (int i = 0; i < count; i++) {
        sum += (samples + i)->phase_A_voltage;
    }

    return sum;
}
