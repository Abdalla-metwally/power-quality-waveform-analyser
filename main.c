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

    free(samples);

    return 0;
}