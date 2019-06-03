#pragma once
#include <chrono>
#include <string>
#include "./nlohmann/json.hpp"

using json = nlohmann::json;

class run {
 private:
  int numSamples = 10000;
  int numProcesors = 1;
  bool isParallel;
  double PI;
  char* DNA;
  char* TDNA;
  std::string problem = "PI";  // DNA
  std::chrono::nanoseconds duration;

  void prepare();
  void sequentialPi(void);
  void parallelPi(void);
  void sequentialDna(void);
  void parallelDna(void);

 public:
  run(int numSamples, int numProcesors, bool isParallel);
  run(json config);
  ~run();
  run* execute();
  std::string toString();
};