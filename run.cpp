
#include "run.hpp"
#include "utils.hpp"

run::run(int numSamples, int numProcesors, bool isParallel) {
  this->numSamples = numSamples;
  this->numProcesors = numProcesors;
  this->isParallel = isParallel;
}

run::run(json config) {
  if (config.find("numSamples") != config.end()) {
    this->numSamples = config["numSamples"];
  }
  if (config.find("numProcesors") != config.end()) {
    this->numProcesors = config["numProcesors"];
  }
  if (config.find("isParallel") != config.end()) {
    this->isParallel = config["isParallel"];
  }
  if (config.find("problem") != config.end()) {
    this->problem = config["problem"];
  }
}

run::~run() {
  if (this->problem == "DNA") {
    delete[] this->DNA;
    delete[] this->TDNA;
  }
}

void run::prepare() {
  // exportVariable(NUM_PROCESORS, std::to_string(this->numProcesors));
  if (this->problem == "DNA") {
    this->DNA = generateDNA(this->numSamples);
  }
}

run* run::execute() {
  this->prepare();
  if (this->problem == "PI") {
    if (this->isParallel) {
      this->duration = GetDuation([&]() { this->parallelPi(); });
    } else {
      this->duration = GetDuation([&]() { this->sequentialPi(); });
    }
  } else if (this->problem == "DNA") {
    if (this->isParallel) {
      this->duration = GetDuation([&]() { this->sequentialDna(); });
    } else {
      this->duration = GetDuation([&]() { this->parallelDna(); });
    }
  }
  return this;
}

std::string run::toString() {
  json out;
  out["problem"] = this->problem;
  out["numSamples"] = this->numSamples;
  out["numProcesors"] = this->numProcesors;
  out["isParallel"] = this->isParallel;
  out["duration"] = this->duration.count();
  if (this->problem == "PI") {
    out["PI"] = this->PI;
  } else if (this->problem == "DNA") {
    auto dna = std::string(this->DNA);
    out["DNA"] = dna;
    if (this->TDNA != nullptr) {
      auto tdna = std::string(this->TDNA);
      out["TDNA"] = tdna;
    }
  }
  return out.dump();
}

void run::sequentialPi(void) { this->PI = sequentialPI(this->numSamples); }
void run::parallelPi(void) {
  this->PI = parallelPI(this->numSamples, this->numProcesors);
}

void run::sequentialDna(void) {
  this->TDNA = sequentialDNA(this->numSamples, this->DNA);
}
void run::parallelDna(void) {
  this->TDNA = parallelDNA(this->numSamples, this->DNA);
}