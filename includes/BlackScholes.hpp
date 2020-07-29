/*
Author: Adam Diehl
Program: Option Pricing -> Includes -> Black Scholes
Date: 2020-07-28
Version: 0.1
Version notes:
  - 0.1: Added closed form BS function
Description: Calculates closed form solutions to the Black Scholes algorithm.
*/

/* ---------- Load Libraries ---------- */
#include <cmath>

/* ---------- Statistical Functions ---------- */
double NormCDF(double z, double sigma);
double NormCDF(double z, double sigma) {
  return 0.5 * erfc(- z / (sigma*sqrt(2)));
}

/* ---------- Closed-Form Black Scholes ---------- */
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

  if(ExerciseType == "Call") { //Call
    return S*NormCDF(d1,1) - K*exp(-r*T)*NormCDF(d2,1);
  } else { //Put
    return -S*NormCDF(-d1,1) + K*exp(-r*T)*NormCDF(-d2,1);
  }
}
