/*
Author: Adam Diehl
Program: Option Pricing -> Main File
Date: 2020-07-27
Version: 0.1
Version notes:
  - 0.1: Added ability to read a JSON file
Description: Handles the core logic that organizes the option pricing algorithms.

Compile notes: gcc -o test main.cpp -std=c++11 -lstdc++
Runtime notes: ./test OptionParams_Call_Euro.json
JSON notes: Parameters["Option Type"]
*/

/* ---------- Load Libraries ---------- */
#include <fstream>
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

  // Get top level data to route option calculator
  std::string PriceMechanism = Parameters["Price Evolution"];
  std::string OptionType = Parameters["Option Type"];

  // Send data to appropriate functions
  if (PriceMechanism == "Black Scholes") {
    if (OptionType == "European") {
      double Price = BlackScholes(Parameters);
      PrettyPrint_Params_BlackScholes(Parameters);
      std::cout << "\nOutputs: \n";
      std::cout << " > Option price = " << std::to_string(Price) << "\n";
    } else if (OptionType == "American") {
      std::cout << "\n>>> American options are not currently implemented.\n";
    }
  }

  // Shutdown
  std::cout << "\nProgram terminated\n.";
}
