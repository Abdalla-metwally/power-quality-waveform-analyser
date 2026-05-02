cmake_minimum_required(VERSION 3.21)
project(Coursework C)

set(CMAKE_C_STANDARD 99)

add_executable(Coursework main.c waveform.c waveform.h io.c io.h)

add_executable(test_rms test.c waveform.c)