
#include "utils.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

void exportVariable(std::string variable, std::string value) {
  auto cmd = variable + "=" + value;
  char* cmd1 = new char[cmd.length() + 1];
  strcpy(cmd1, cmd.c_str());
  cmd1[cmd.length()] = 0;
  putenv(cmd1);
  std::cout << getenv(variable.c_str()) << std::endl;
  system(cmd1);
}

std::chrono::nanoseconds GetDuation(std::function<void()> func) {
  auto start = std::chrono::steady_clock::now();
  func();
  auto end = std::chrono::steady_clock::now();
  return end - start;
}

class UniformDistribution {
 public:
  UniformDistribution() : generator(), distribution(-1.0, 1.0) {
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
  }

  double sample() { return distribution(generator); }

  UniformDistribution(const UniformDistribution&) = delete;
  UniformDistribution& operator()(const UniformDistribution&) = delete;
  UniformDistribution(UniformDistribution&&) = delete;
  UniformDistribution& operator()(UniformDistribution&&) = delete;

 private:
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution;
};

double sequentialPI(const unsigned long long numSamples) {
  UniformDistribution distribution;

  unsigned long long counter = 0;
  for (unsigned long long s = 0; s != numSamples; s++) {
    auto x = distribution.sample();
    auto y = distribution.sample();

    if (x * x + y * y < 1) {
      counter++;
    }
  }

  return 4.0 * counter / numSamples;
}

unsigned long long samplesInsideCircle(const unsigned long long numSamples) {
  UniformDistribution distribution;

  unsigned long long counter = 0;
  for (unsigned long long s = 0; s != numSamples; s++) {
    auto x = distribution.sample();
    auto y = distribution.sample();
    ;

    if (x * x + y * y < 1) {
      counter++;
    }
  }

  return counter;
}

double parallelPI(unsigned long long numTotalSamples,
                  unsigned long long numChunks) {
  unsigned long long chunk = numTotalSamples / numChunks;

  unsigned long long counter = 0;

#pragma omp parallel for shared(numChunks, chunk) reduction(+ : counter)
  for (unsigned long long i = 0; i < numChunks; i++) {
    counter += samplesInsideCircle(chunk);  // maybee change to
  }

  return 4.0 * counter / numTotalSamples;
}

char complement(char n) {
  switch (n) {
    case 'A':
      return 'T';
    case 'T':
      return 'A';
    case 'G':
      return 'C';
    case 'C':
      return 'G';
  }
  return ' ';
}

char* sequentialDNA(int n, char* dna) {
  char* cdna = new char[n + 1];
  for (int i = 0; i < n; i++) {
    cdna[i] = complement(dna[i]);
  }
  cdna[n] = 0;
  return cdna;
}

char* parallelDNA(int n, char* dna) {
  char* cdna = new char[n + 1];
#pragma omp parallel for shared(n, dna, cdna)  // reduction(+ : counter)
  for (int i = 0; i < n; i++) {
    cdna[i] = complement(dna[i]);
  }
  cdna[n] = 0;
  return cdna;
}

char* generateDNA(int n) {
  char* pDNA = new char[4]{'A', 'T', 'G', 'C'};
  char* dna = new char[n + 1];
  UniformDistribution distribution;
  for (int i = 0; i < n; i++) {
    int d = int(3 * (distribution.sample() + 1) / 2);
    dna[i] = pDNA[d];
  }
  dna[n] = 0;
  return dna;
}