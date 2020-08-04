/*
Author: Adam Diehl
Program: Option Pricing -> Includes -> Black Scholes
Date: 2020-07-28
Revised: 2020-07-30
Description: Calculates closed form solutions to the Black Scholes algorithm.
*/

/* ---------- Load Libraries ---------- */
#include <algorithm>
#include <cmath>
#include <random>

/* ---------- Statistical Functions ---------- */
double NormCDF(double z, double sigma);
double NormCDF(double z, double sigma) {
  return 0.5 * erfc(- z / (sigma*sqrt(2)));
}

/* ---------- Simulation Methods ---------- */
// Black Scholes with simple Monte Carlo (Euler discretization) -- TODO
double BlackScholesMonteCarlo(json Parameters);
double BlackScholesMonteCarlo(json Parameters) {

  // Read in parameters
  double S = Parameters["Input Values"]["Initial Stock Price"];
  double K = Parameters["Input Values"]["Strike Price"];
  double r = Parameters["Input Values"]["Risk-Free Rate"];
  double Vol = Parameters["Input Values"]["Volatility"];
  double T = Parameters["Input Values"]["Time-to-Maturity"];
  int Steps = Parameters["Simulation Parameters"]["Number of Steps"];
  int N = Parameters["Simulation Parameters"]["Number of Simulations"];

  // Compute constants that depend on program parameters
  double dt = T/Steps;
  double sqrtDT = sqrt(dt);
  double Discount = exp(-r*T);
  double NormalizingConstant = 1/(N + 0.00);
  double Payoff = 0.0;

  // Seed RNG
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<float> RNORM(0.0, 1.0);

  // Initialize memory
  std::vector<std::vector<double> > PricePath(N,std::vector<double>(Steps));

  // Simulate forward
  for (int i = 0; i < N; i++) {
    PricePath[i][0] = S;
    for (int j = 1; j < Steps; j++) {
      PricePath[i][j] = PricePath[i][j-1] + r*PricePath[i][j-1]*dt + Vol*PricePath[i][j-1]*sqrtDT*RNORM(gen);
    }
  }

  // Calculate payoff
  for (int i = 0; i < N; i++) {
    Payoff += std::max((PricePath[i][Steps-1] - K), 0.0) * NormalizingConstant;
  }

  return (Discount * Payoff);
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
    return 0;
  }
}
