# Option Pricing Algorithms

This repository contains C++ scripts for pricing options under various assumptions for the underlying stock behavior and types of exotic option classes.

## About 
### Project Description
Forthcoming.

### Version Information
- Version 0.1: Basic skeleton of app logic.

#### Planned features
Program execution flags:
- "-append" or "-a" -> appends the output of the calculation to the input JSON
- "-compact" or "-c" -> suppresses most of the output to the console
- "-verbose" or "-v" -> prints more stuff to the console

### Installation
Currently the only way to install is to compile from source.

#### External Dependencies
- #include "includes/json.hpp" -> source: https://github.com/nlohmann/json

### Examples
Pass a JSON file on the command line to run the code:
```
User $ ./OptionCalculator OptionParams_Call_Euro.json
Outputs: 
 > Option price = 9.927630
```
With verbose flag:
```
User $ ./OptionCalculator OptionParams_Call_Euro.json -v
Input parameters:
 > Pricing mechanism: "Black Scholes"
 > Option type: "European"
 > Exercise type: "Call"
 > Initial stock price: 100.0
 > Strike price: 101.0
 > Risk-Free Rate: 0.05
 > Volatility: 0.2
 > Time-to-Maturity: 1.0

Outputs: 
 > Option price = 9.927630

Program terminated
```
