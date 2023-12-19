#include "VanillaOption.hpp"

VanillaOption::VanillaOption(double T, int nbTimeSteps, int size, float strike)
  : Option(T, nbTimeSteps, size)
{
    strike_ = strike;
}

VanillaOption::VanillaOption(char* jsonPath)
  : Option(jsonPath)
{
    JsonReaderUtils* jsonReaderUtils = new JsonReaderUtils(jsonPath);
    this->strike_ = jsonReaderUtils->getStrikeFromJson();
}

double
VanillaOption::payoff(const PnlMat* path)
{
    return std::max(MGET(path, nbTimeSteps_, 0) - strike_, 0.0);
}