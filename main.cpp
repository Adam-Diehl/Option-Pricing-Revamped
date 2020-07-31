/*
Author: Adam Diehl
Program: Option Pricing -> Main File
Date: 2020-07-27
Revised: 2020-07-30
Description: Handles the core logic that organizes the option pricing algorithms.
Compile notes: gcc -o OptionCalculator main.cpp -std=c++11 -lstdc++
Runtime notes: ./OptionCalculator ./config/VanillaCall.json
JSON notes: Parameters["Option Type"]
*/

/* ---------- Load Libraries ---------- */
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "includes/json.hpp" // source: https://github.com/nlohmann/json
using json = nlohmann::json;

#include "includes/BlackScholes.hpp"
#include "includes/IOfunctions.hpp"

/* ---------- Begin Main File ---------- */
int main(int argc, char *argv[])

{
  // Input directory
  std::string Directory = "";

  // Parse program arguments: first argument is MANDATORY: a JSON file
  if (argc > 1) { // MANDATORY: Locate JSON file
    std::string Filename(argv[1]);
    Directory += Filename;
  } else {
    std::cout << "[ERROR: invalid arguments -> you must specify a JSON file containing option's parameters.]\n";
    return -1;
  }
  std::ifstream ParamsFile(Directory);
  json Parameters;
  ParamsFile >> Parameters;

  // Parse program arguments: OPTIONAL arguments
  bool FlagAppendOutput = false; // append output value to JSON file
  bool FlagSilent = false; // suppress most output to console
  bool FlagVerbose = false; // run program in verbose mode
  if (argc > 2) {
    for (char **pargv = argv+2; *pargv != argv[argc]; pargv++) {
      if (strcmp(*pargv, "-a") == 0 || strcmp(*pargv, "-append") == 0) {
        FlagAppendOutput = true;
      } else if (strcmp(*pargv, "-s") == 0 || strcmp(*pargv, "-silent") == 0) {
        FlagSilent = true;
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
      IOHandlerOptionPricing(Parameters, Price, FlagAppendOutput, FlagSilent, FlagVerbose);
      if (FlagAppendOutput) {
        Parameters["Option Price"] = Price;
        std::ofstream Output(Directory);
        Output << std::setw(4) << Parameters << std::endl;
      }
    } else if (OptionType == "American") {
      std::cout << "\n>>> American options are not currently implemented.\n";
    }
  }

  // Shutdown
  if (FlagVerbose) {
    if (FlagAppendOutput) {
      std::cout << "File " << Directory << " modified to include option price\n";
    }
    std::cout << "\nProgram terminated\n.";
  }
  return 0;
}
