#pragma once

#include <chrono>
#include <functional>
#include <string>

#define NUM_PROCESORS "OMP_NUM_THREADS"

void exportVariable(std::string variable, std::string value);

std::chrono::nanoseconds GetDuation(std::function<void()> func);

double sequentialPI(const int numSamples);

double parallelPI(const int numTotalSamples, const int numChunks = 8);

char* sequentialDNA(int n, char* dna);

char* parallelDNA(int n, char* dna);

char* generateDNA(int n);