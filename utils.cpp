
#include "utils.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <random>

void exportVariable(std::string variable, std::string value) {
  system(("export " + variable + "=" + value).c_str());
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

double sequentialPI(const int numSamples) {
  UniformDistribution distribution;

  int counter = 0;
  for (int s = 0; s != numSamples; s++) {
    auto x = distribution.sample();
    auto y = distribution.sample();

    if (x * x + y * y < 1) {
      counter++;
    }
  }

  return 4.0 * counter / numSamples;
}

int samplesInsideCircle(const int numSamples) {
  UniformDistribution distribution;

  int counter = 0;
  for (int s = 0; s != numSamples; s++) {
    auto x = distribution.sample();
    auto y = distribution.sample();
    ;

    if (x * x + y * y < 1) {
      counter++;
    }
  }

  return counter;
}

double parallelPI(int numTotalSamples, int numChunks) {
  int chunk = numTotalSamples / numChunks;

  int counter = 0;

#pragma omp parallel for shared(numChunks, chunk) reduction(+ : counter)
  for (int i = 0; i < numChunks; i++) {
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