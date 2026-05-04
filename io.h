//
// Created by Abdul on 21/04/2026.
//

#ifndef COURSEWORK_IO_H
#define COURSEWORK_IO_H

#include "waveform.h"

int count_rows(const char *filename);
int load_csv(const char *filename, waveformsample *samples, int row_count);


int write_results(const char *filename,
                  double rms_A, double rms_B, double rms_C,
                  double p2p_A, double p2p_B, double p2p_C,
                  double dc_A, double dc_B, double dc_C,
                  int clip_A, int clip_B, int clip_C,
                  int tol_A, int tol_B, int tol_C,
                  int clipped_count_A, int clipped_count_B, int clipped_count_C,
                  double mean_frequency,
                  double mean_power_factor,
                  double mean_thd);
#endif //COURSEWORK_IO_H

