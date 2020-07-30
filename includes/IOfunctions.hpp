/*
Author: Adam Diehl
Program: Option Pricing -> Includes -> IOfunctions
Date: 2020-07-28
Revised: 2020-07-29
Description: Functions to perform any IO beyond the most basic stuff that can be
  handled by the main file without clutter.
*/

/* ---------- Pretty Printing ---------- */
void PrettyPrint_Params_BlackScholes(json Parameters);
void PrettyPrint_Params_BlackScholes(json Parameters) {
  std::cout << "Input parameters:\n";
  std::cout << " > Pricing mechanism: " << Parameters["Price Evolution"] << "\n";
  std::cout << " > Option type: " << Parameters["Option Type"] << "\n";
  std::cout << " > Exercise type: " << Parameters["Exercise Type"] << "\n";
  std::cout << " > Initial stock price: " << Parameters["Input Values"]["Initial Stock Price"] << "\n";
  std::cout << " > Strike price: " << Parameters["Input Values"]["Strike Price"] << "\n";
  std::cout << " > Risk-Free Rate: " << Parameters["Input Values"]["Risk-Free Rate"] << "\n";
  std::cout << " > Volatility: " << Parameters["Input Values"]["Volatility"] << "\n";
  std::cout << " > Time-to-Maturity: " << Parameters["Input Values"]["Time-to-Maturity"] << "\n";
}

/* ---------- IO Handlers for Subroutines ---------- */
void IOHandlerOptionPricing(json Parameters, double Price, bool FlagAppendOutput, bool FlagSilent, bool FlagVerbose);
void IOHandlerOptionPricing(json Parameters, double Price, bool FlagAppendOutput, bool FlagSilent, bool FlagVerbose) {
  if (FlagVerbose) {
    PrettyPrint_Params_BlackScholes(Parameters);
    std::cout << "\nOutputs: \n";
    std::cout << " > Option price = " << std::to_string(Price) << "\n";
  } else if (!FlagSilent) {
    std::cout << "Option price = " << std::to_string(Price) << "\n";
  }
}
