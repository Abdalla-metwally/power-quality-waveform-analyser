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
                  int tol_A, int tol_B, int tol_C) {

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error: could not create results file\n");
        return 0;
    }

    fprintf(file, "Power Quality Analysis Report\n");
    fprintf(file, "-----------------------------\n\n");

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

    fprintf(file, "Tolerance Check:\n");
    fprintf(file, "Phase A: %s\n", tol_A ? "WITHIN LIMIT" : "OUT OF LIMIT");
    fprintf(file, "Phase B: %s\n", tol_B ? "WITHIN LIMIT" : "OUT OF LIMIT");
    fprintf(file, "Phase C: %s\n", tol_C ? "WITHIN LIMIT" : "OUT OF LIMIT");

    fclose(file);
    return 1;
}