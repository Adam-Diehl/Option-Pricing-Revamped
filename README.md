# Option Pricing Algorithms

This repository contains C++ scripts for pricing options under various assumptions for the underlying stock behavior and types of exotic options.

## Table of Contents
- [About](https://github.com/Adam-Diehl/Option-Pricing-Revamped#about)
	- [Project Description](https://github.com/Adam-Diehl/Option-Pricing-Revamped#project-description)
	- [Version Information](https://github.com/Adam-Diehl/Option-Pricing-Revamped#version-information)
	- [Installation](https://github.com/Adam-Diehl/Option-Pricing-Revamped#installation)
- [Technical Details](https://github.com/Adam-Diehl/Option-Pricing-Revamped#technical-details)
	- [Financial Details](https://github.com/Adam-Diehl/Option-Pricing-Revamped#financial-details)
	- [Computational Details](https://github.com/Adam-Diehl/Option-Pricing-Revamped#computational-details)

## About
### Project Description
This project brings together and extends the various programs that I have previously written for option pricing and connects them all through a lightweight CLI. The programmed is designed to read in a set of parameters from a JSON file, automatically select the best pricing algorithm, and then perform the appropriate calculations. For all but the most simple case (Black Scholes with closed form solution) this requires numerically simulating stochastic differential equations. Performing these simulations in a performant manner requires careful memory management, hence the choice of a C family language. The program is (currently) implemented  entirely in C++11, with a "mostly C style" (C++ is used for some 'quality of life' features).

This program is currently in the very-early stages of development and in no way should be considered a finished product.

### Version Information
- Version 0.2.4: Added antithetic acceleration to Monte Carlo simulation
- Version 0.2.3: Added first draft of the Monte Carlo simulation for Geometric Brownian Motion
- Version 0.2.2: Added initial implementation of three execution flags:
	- "-append" or "-a" -> appends the output of the calculation to the input JSON
	- "-silent" or "-s" -> suppresses most of the output to the console
	- "-verbose" or "-v" -> prints more stuff to the console
- Version 0.2.1: Added logic to parse run flags, and some basic IO related to them
- Version 0.2:
	- App can parse and calculate European calls/puts using Black Scholes model
	- App can read and parse JSON files
	- Refactored IO, exception handling, removed hardcoded paths
- Version 0.1: Basic skeleton of app logic.

#### Planned features
- American options
- Program execution flags:
	- "-greeks" or "-g" -> additionally outputs the Greeks for the option
	- "-milstein" or "-m" -> modifies standard Euler discretization with Milstein discretization
	- "-srk" -> modified standard Euler discretization with stochastic Runge-Kutta
- Unit tests

### Installation
Currently the only way to install this is to compile from source.

#### External Dependencies
- #include "includes/json.hpp" -> source: https://github.com/nlohmann/json

### Examples
Pass a JSON file on the command line to run the code:
```
User $ ./OptionCalculator ./config/OptionParams_Call_Euro.json
Option price = 9.927630
```
With verbose flag:
```
User $ ./OptionCalculator ./config/OptionParams_Call_Euro.json -v
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
With append flag (and verbose flag):
```
User $ cat ./config/OptionParams_Call_Euro.json
{
    "Price Evolution": "Black Scholes",
    "Option Type": "European",
    "Exercise Type": "Call",
    "Input Values": {
        "Initial Stock Price": 100.0,
        "Risk-Free Rate": 0.05,
        "Strike Price": 101.0,
        "Time-to-Maturity": 1.0,
        "Volatility": 0.2
    }
}

User $ ./OptionCalculator ./config/OptionParams_Call_Euro.json -v -a
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
File ./config/OptionParams_Call_Euro.json modified to include option price

User $ cat ./config/OptionParams_Call_Euro.json
{
    "Exercise Type": "Call",
    "Input Values": {
        "Initial Stock Price": 100.0,
        "Risk-Free Rate": 0.05,
        "Strike Price": 101.0,
        "Time-to-Maturity": 1.0,
        "Volatility": 0.2
    },
    "Option Price": 9.927630032876948,
    "Option Type": "European",
    "Price Evolution": "Black Scholes"
}
```
Note that the external JSON library automatically returns the JSON file parameters in alphabetical order.

## Technical Details

This discusses the models, assumptions, and features of the program.

### Financial Details

### Computational Details

#### Antithetic Variates Method

To reduce both the number of sample paths required and the variance of the aggregate of the paths we can use [antithetic variates](https://en.wikipedia.org/wiki/Antithetic_variates). For Gaussian random variables this essentially amounts to halving the number of random Gaussian numbers we sample and taking their negative instead. For details see
- [*Introduction to reducing variance in Monte Carlo simulations*](http://www.columbia.edu/~ks20/4703-Sigman/4703-07-Notes-ATV.pdf), Section 1.4.

#### Black-Scholes

- Vanilla options (European style calls and puts)
	- These options are computed using the [closed form solution](https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model#Black%E2%80%93Scholes_formula) to the Black Scholes equation.
