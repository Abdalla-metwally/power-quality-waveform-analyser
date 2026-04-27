//
// Created by Abdul on 21/04/2026.
//

#ifndef COURSEWORK_IO_H
#define COURSEWORK_IO_H

#include "waveform.h"

int count_rows(const char *filename);
int load_csv(const char *filename, waveformsample *samples, int row_count);

#endif //COURSEWORK_IO_H

