#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s power_quality_log.csv\n", argv[0]);
        return 1;
    }

    int row_count = count_rows(argv[1]);

    if (row_count == 0) {
        printf("No data found or file could not be opened.\n");
        return 1;
    }

    waveformsample *samples = malloc(row_count * sizeof(waveformsample));

    if (samples == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (load_csv(argv[1], samples, row_count) == 0) {
        printf("Failed to load CSV data.\n");
        free(samples);
        return 1;
    }

    printf("File loaded successfully.\n");
    printf("Rows loaded: %d\n", row_count);

    double rms_A = compute_rms(samples, row_count, 'A');
    double rms_B = compute_rms(samples, row_count, 'B');
    double rms_C = compute_rms(samples, row_count, 'C');

    printf("RMS Phase A: %.2f V\n", rms_A);
    printf("RMS Phase B: %.2f V\n", rms_B);
    printf("RMS Phase C: %.2f V\n", rms_C);


    double p2p_A = compute_peak_to_peak(samples, row_count, 'A');
    double p2p_B = compute_peak_to_peak(samples, row_count, 'B');
    double p2p_C = compute_peak_to_peak(samples, row_count, 'C');

    printf("\n");

    printf("P2P Phase A: %.2f V\n", p2p_A);
    printf("P2P Phase B: %.2f V\n", p2p_B);
    printf("P2P Phase C: %.2f V\n", p2p_C);

    free(samples);

    return 0;
}