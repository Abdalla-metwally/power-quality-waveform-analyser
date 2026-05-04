//
// Created by Abdul on 21/04/2026.
//
#include <stdio.h>
#include "io.h"

int count_rows(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: file not found\n");
        return 0;
    }
    char line[256];
    int count = 0;

    // Skip header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL) {
        count++;
    }
    fclose(file);
    return count;
}

int load_csv(const char *filename, waveformsample *samples, int row_count) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: file could not be opened\n");
        return 0;
    }

    char line[256];

    // Skip the header row
    fgets(line, sizeof(line), file);

    int i = 0;

    while (fgets(line, sizeof(line), file) != NULL && i < row_count) {
        sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &(samples + i)->timestamp,
               &(samples + i)->phase_A_voltage,
               &(samples + i)->phase_B_voltage,
               &(samples + i)->phase_C_voltage,
               &(samples + i)->line_current,
               &(samples + i)->frequency,
               &(samples + i)->power_factor,
               &(samples + i)->thd_percent);

        i++;
    }

    fclose(file);
    return 1;
}

int write_results(const char *filename,
                  double rms_A, double rms_B, double rms_C,
                  double p2p_A, double p2p_B, double p2p_C,
                  double dc_A, double dc_B, double dc_C,
                  int clip_A, int clip_B, int clip_C,
                  int tol_A, int tol_B, int tol_C,
                  int clipped_count_A, int clipped_count_B, int clipped_count_C,
                  double mean_frequency,
                  double mean_power_factor,
                  double mean_thd) {

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error: could not create results file\n");
        return 0;
    }

    fprintf(file, "Power Quality Analysis Report\n");
    fprintf(file, "=============================\n\n");

    fprintf(file, "Input data summary:\n");
    fprintf(file, "- Dataset: 3-phase AC waveform data\n");
    fprintf(file, "- Window: approximately 200 ms\n");
    fprintf(file, "- Nominal voltage: 230 V RMS\n");
    fprintf(file, "- Tolerance band: 207 V to 253 V\n\n");

    fprintf(file, "RMS Voltage:\n");
    fprintf(file, "Phase A: %.2f V\n", rms_A);
    fprintf(file, "Phase B: %.2f V\n", rms_B);
    fprintf(file, "Phase C: %.2f V\n\n", rms_C);

    fprintf(file, "Peak-to-Peak Voltage:\n");
    fprintf(file, "Phase A: %.2f V\n", p2p_A);
    fprintf(file, "Phase B: %.2f V\n", p2p_B);
    fprintf(file, "Phase C: %.2f V\n\n", p2p_C);

    fprintf(file, "DC Offset:\n");
    fprintf(file, "Phase A: %.2f V\n", dc_A);
    fprintf(file, "Phase B: %.2f V\n", dc_B);
    fprintf(file, "Phase C: %.2f V\n\n", dc_C);

    fprintf(file, "Clipping Detection:\n");
    fprintf(file, "Phase A: %s\n", clip_A ? "CLIPPING DETECTED" : "OK");
    fprintf(file, "Phase B: %s\n", clip_B ? "CLIPPING DETECTED" : "OK");
    fprintf(file, "Phase C: %s\n\n", clip_C ? "CLIPPING DETECTED" : "OK");

    fprintf(file, "Clipped Sample Count:\n");
    fprintf(file, "Phase A: %d samples\n", clipped_count_A);
    fprintf(file, "Phase B: %d samples\n", clipped_count_B);
    fprintf(file, "Phase C: %d samples\n\n", clipped_count_C);

    fprintf(file, "Tolerance Check:\n");
    fprintf(file, "Phase A: %s\n", tol_A ? "WITHIN LIMIT" : "OUT OF LIMIT");
    fprintf(file, "Phase B: %s\n", tol_B ? "WITHIN LIMIT" : "OUT OF LIMIT");
    fprintf(file, "Phase C: %s\n\n", tol_C ? "WITHIN LIMIT" : "OUT OF LIMIT");

    fprintf(file, "Additional Measurements:\n");
    fprintf(file, "Mean frequency over the 200 ms window: %.3f Hz\n", mean_frequency);
    fprintf(file, "Mean power factor: %.3f\n", mean_power_factor);
    fprintf(file, "Mean THD: %.2f %%\n\n", mean_thd);

    fprintf(file, "Overall assessment:\n");
    fprintf(file, "- RMS values are compared against the 230 V nominal supply.\n");
    fprintf(file, "- Tolerance compliance is checked using the 207 V to 253 V range.\n");
    fprintf(file, "- Clipping is flagged when |voltage| >= 324.9 V.\n");

    fclose(file);
    return 1;
}