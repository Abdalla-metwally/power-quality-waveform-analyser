//
// Created by Abdul on 03/05/2026.
//
#include <stdio.h>
#include <math.h>
#include "waveform.h"

int main(void) {
    waveformsample test_samples[2] = {
            {0, 2, 4, 4, 0, 0, 0, 0},
            {0, 7, 8, 9, 0, 0, 0, 0}
    };

    double rms_A = compute_rms(test_samples, 2, 'A');
    double rms_B = compute_rms(test_samples, 2, 'B');
    double rms_C = compute_rms(test_samples, 2, 'C');

    printf("RMS A expected 5.15, got %.2f\n", rms_A);
    printf("RMS B expected 6.32, got %.2f\n", rms_B);
    printf("RMS C expected 6.96, got %.2f\n", rms_C);

    double p2p_A = compute_peak_to_peak(test_samples, 2, 'A');
    double p2p_B = compute_peak_to_peak(test_samples, 2, 'B');
    double p2p_C = compute_peak_to_peak(test_samples, 2, 'C');

    printf("\n");

    printf("P2P A expected 5.00, got %.2f\n", p2p_A);
    printf("P2P B expected 4.00, got %.2f\n", p2p_B);
    printf("P2P C expected 5.00, got %.2f\n", p2p_C);


    double dc_A = compute_dc_offset(test_samples, 2, 'A');
    double dc_B = compute_dc_offset(test_samples, 2, 'B');
    double dc_C = compute_dc_offset(test_samples, 2, 'C');

    printf("\n");

    printf("DC A expected 4.50, got %.2f\n", dc_A);
    printf("DC B expected 6.00, got %.2f\n", dc_B);
    printf("DC C expected 6.50, got %.2f\n", dc_C);

    return 0;
}
