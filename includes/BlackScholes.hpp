/*
Author: Adam Diehl
Program: Option Pricing -> Includes -> Black Scholes
Date: 2020-07-28
Revised: 2020-07-30
Description: Calculates closed form solutions to the Black Scholes algorithm.
*/

/* ---------- Load Libraries ---------- */
#include <cmath>

/* ---------- Statistical Functions ---------- */
double NormCDF(double z, double sigma);
double NormCDF(double z, double sigma) {
  return 0.5 * erfc(- z / (sigma*sqrt(2)));
}

/* ---------- Simulation Methods ---------- */
// Black Scholes with simple Monte Carlo (Euler discretization) -- TODO
double BlackScholesMonteCarlo(json Parameters);
double BlackScholesMonteCarlo(json Parameters) {
  return 0;
}

// Black Scholes with Milstein discretization -- TODO
double BlackScholesMonteCarloMilstein(json Parameters);
double BlackScholesMonteCarloMilstein(json Parameters) {
  return 0;
}

/* ---------- Black Scholes Family ---------- */
// Closed form vanilla Black Scholes
double BlackScholes(json Parameters);
double BlackScholes(json Parameters) {

  std::string ExerciseType = Parameters["Exercise Type"];
  double S = Parameters["Input Values"]["Initial Stock Price"];
  double K = Parameters["Input Values"]["Strike Price"];
  double r = Parameters["Input Values"]["Risk-Free Rate"];
  double Vol = Parameters["Input Values"]["Volatility"];
  double T = Parameters["Input Values"]["Time-to-Maturity"];

  double d1 = (1/(Vol*sqrt(T))) * (log(S/K) + (r + 0.5*Vol*Vol)*T);
  double d2 = d1 - Vol*sqrt(T);

  if(ExerciseType == "Call") {
    return S*NormCDF(d1,1) - K*exp(-r*T)*NormCDF(d2,1);
  } else { //Put
    return -S*NormCDF(-d1,1) + K*exp(-r*T)*NormCDF(-d2,1);
  }
}

// Black Scholes with American Exercise
double BlackScholesAmerican(json Parameters);
double BlackScholesAmerican(json Parameters) {
  std::string ExerciseType = Parameters["Exercise Type"];

  if(ExerciseType == "Call") { //Call with no dividends is equivalent to European call
    return BlackScholes(Parameters);
  } else { // Put -- TODO
    double S = Parameters["Input Values"]["Initial Stock Price"];
    double K = Parameters["Input Values"]["Strike Price"];
    double r = Parameters["Input Values"]["Risk-Free Rate"];
    double Vol = Parameters["Input Values"]["Volatility"];
    double T = Parameters["Input Values"]["Time-to-Maturity"];
    return 0;
  }
}
