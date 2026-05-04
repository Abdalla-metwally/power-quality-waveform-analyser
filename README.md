# Power Quality Waveform Analyser

This project is a C program for analysing a three-phase power quality CSV file.

## What the program does

The program reads `power_quality_log.csv`, stores each row in a `waveformsample` struct, and calculates:

- RMS voltage for phases A, B and C
- Peak-to-peak voltage for phases A, B and C
- DC offset for phases A, B and C
- Clipping detection and clipped sample count
- RMS tolerance compliance against 230 V +/- 10%
- Mean frequency
- Mean power factor
- Mean THD

The program also writes the calculated results to `results.txt`.

## Files

- `main.c` - main program flow and function calls
- `waveform.c` - waveform analysis functions
- `waveform.h` - waveform struct and function prototypes
- `io.c` - CSV loading and results file writing
- `io.h` - file I/O function prototypes
- `test.c` - simple unit testing file
- `CMakeLists.txt` - CLion/CMake build file

## How to run it in CLion

1. Open the project folder in CLion.
2. Build the project.
3. Go to Run/Edit Configurations.
4. Add this program argument:

```text
power_quality_log.csv