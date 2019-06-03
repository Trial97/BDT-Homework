
#include <fstream>
#include <iostream>

#include "run.hpp"
#include "utils.hpp"

using namespace std;

json readConfig(string cfgPath) {
  fstream configFile;
  json config;
  configFile.open(cfgPath.c_str());
  if (!configFile.is_open()) {
    return config;
  }
  configFile >> config;
  configFile.close();
  return config;
  return nullptr;
}

int main(int, char**) {
  json config;
  config = readConfig("./config.json");
  cout << "{" << endl;
  for (json::iterator it = config.begin(); it != config.end(); ++it) {
    auto r = new run(*it);
    cout << r->execute()->toString() << "," << endl;
    delete r;
  }
  cout << "}" << endl;
}
