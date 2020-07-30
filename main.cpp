/*
Author: Adam Diehl
Program: Option Pricing -> Main File
Date: 2020-07-27
Version: 0.1
Version notes:
  - 0.1: Added ability to read a JSON file
Description: Handles the core logic that organizes the option pricing algorithms.

Compile notes: gcc -o OptionCalculator main.cpp -std=c++11 -lstdc++
Runtime notes: ./OptionCalculator OptionParams_Call_Euro.json
JSON notes: Parameters["Option Type"]
*/

/* ---------- Load Libraries ---------- */
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "includes/json.hpp" // source: https://github.com/nlohmann/json
using json = nlohmann::json;

#include "includes/BlackScholes.hpp"
#include "includes/IOfunctions.hpp"

/* ---------- Begin Main File ---------- */
int main(int argc, char *argv[])

{
  // Input directory
  std::string Directory = "//Users//Presidente//Documents//Programming//Option Pricing//config//";

  // Parse program arguments: first argument is MANDATORY: a JSON file
  if (argc > 1) { // MANDATORY: Locate JSON file
    std::string Filename(argv[1]);
    Directory += Filename;
  } else {
    throw std::invalid_argument("First argument missing -> you need to specify \
    a JSON file containing the option's parameters.");
  }
  std::ifstream ParamsFile(Directory);
  json Parameters;
  ParamsFile >> Parameters;

  // Parse program arguments: OPTIONAL arguments
  bool FlagAppendOutput = false; // append output value to JSON file
  bool FlagCompact = false; // suppress most output to console
  bool FlagVerbose = false; // run program in verbose mode
  if (argc > 2) {
    for (char **pargv = argv+2; *pargv != argv[argc]; pargv++) {
      if (strcmp(*pargv, "-a") == 0 || strcmp(*pargv, "-append") == 0) {
        FlagAppendOutput = true;
      } else if (strcmp(*pargv, "-c") == 0 || strcmp(*pargv, "-compact") == 0) {
        FlagCompact = true;
      } else if (strcmp(*pargv, "-v") == 0 || strcmp(*pargv, "-verbose") == 0) {
        FlagVerbose = true;
      } else {
        std::string ErrorMessage = "\n[Warning: an argument was not recognized and will be ignored -> ";
        std::string InvalidFlag = *pargv;
        std::cout << (ErrorMessage + InvalidFlag) << "]\n\n";
        continue;
      }
    }
  }

  // Get top level data to route option calculator
  std::string PriceMechanism = Parameters["Price Evolution"];
  std::string OptionType = Parameters["Option Type"];

  // Send data to appropriate functions
  if (PriceMechanism == "Black Scholes") {
    if (OptionType == "European") {
      double Price = BlackScholes(Parameters);
      HandleOutputBlackScholes(Parameters, Price, FlagAppendOutput, FlagCompact, FlagVerbose);
    } else if (OptionType == "American") {
      std::cout << "\n>>> American options are not currently implemented.\n";
    }
  }

  // Shutdown
  if (FlagVerbose) {
    std::cout << "\nProgram terminated\n.";
  }
  return 0;
}
