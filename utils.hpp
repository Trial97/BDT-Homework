#pragma once

#include <chrono>
#include <functional>
#include <string>

#define NUM_PROCESORS "OMP_NUM_THREADS"

void exportVariable(std::string variable, std::string value);

std::chrono::nanoseconds GetDuation(std::function<void()> func);

double sequentialPI(const unsigned long long numSamples);

double parallelPI(const unsigned long long numTotalSamples,
                  const unsigned long long numChunks = 8);

char* sequentialDNA(unsigned long long n, char* dna);

char* parallelDNA(unsigned long long n, char* dna);

char* generateDNA(unsigned long long n);