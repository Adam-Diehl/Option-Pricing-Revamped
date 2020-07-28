/*
Author: Adam Diehl
Program: Option Pricing -> Main File
Date: 2020-07-27
Version: 0.1
Version notes:
  - 0.1: Added ability to read a JSON file

Compile notes: gcc -o test main.cpp -std=c++11 -lstdc++
Runtime notes: ./test OptionParams_Call_Euro.json
*/

/* ---------- Load Libraries ---------- */
#include <fstream>
#include <iostream>
#include <string>

#include "includes/json.hpp"
using json = nlohmann::json;

/* ---------- Begin Main File ---------- */
int main(int argc, char *argv[])

{
  // Input directory
  std::string Directory = "//Users//Presidente//Documents//Programming//Option Pricing//config//";

  // Parse arguments to locate JSON file
  if (argc > 1)
  {
    std::string Filename(argv[1]);
    Directory += Filename;
  }
  std::ifstream ParamsFile(Directory);
  json Parameters;
  ParamsFile >> Parameters;

  // Output
  std::cout << Parameters;
  std::cout << "\nAll done!\n";
}
