# Option Pricing Algorithms

This repository contains C++ scripts for pricing options under various assumptions for the underlying stock behavior and types of exotic option classes.

## About 
### Project Description
This project brings together the various programs that I have previously written for option pricing and connects them all through a lightweight CLI. The programmed is designed to read in a set of parameters from a JSON file, automatically select the best pricing algorithm, and then perform the appropriate calculations. For all but the most simple case (Black Scholes with closed form solution) this requires simulating stochastic differential equations. Performing these simulations in a performant manner requires careful memory management, hence the choice of a C family language. The program is (currently) implemented  entirely in C++, with a "mostly C style" (C++ is used for some 'quality of life' features). 

This program is currently in the very-early stages of development and in no way should be considered a finished product. 

### Version Information
- Version 0.2.1: Added logic to parse run flags, and some basic IO related to them
- Version 0.2:
	- App can parse and calculate European calls/puts using Black Scholes model
	- App can read and parse JSON files
	- Refactored IO, exception handling, removed hardcoded paths 
- Version 0.1: Basic skeleton of app logic.

#### Planned features
Program execution flags:
- "-append" or "-a" -> appends the output of the calculation to the input JSON
- "-Silent" or "-s" -> suppresses most of the output to the console
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
