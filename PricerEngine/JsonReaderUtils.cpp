#include "JsonReaderUtils.hpp"

JsonReaderUtils::JsonReaderUtils(char* jsonPath)
  : jsonPath_(jsonPath)
{
    std::ifstream ifs(jsonPath_);
    j = nlohmann::json::parse(ifs);
}

bool
JsonReaderUtils::isTypeOption(char* optionType)
{
    std::string option_type = j.at("option type").get<std::string>();
    return strcmp(option_type.c_str(), optionType) == 0;
}

double
JsonReaderUtils::getMaturityFromJson()
{
    return j.at("maturity");
}

int
JsonReaderUtils::getSizeFromJson()
{
    return j.at("option size");
}

int
JsonReaderUtils::getNbTimeStepFromJson()
{
    return j.at("timestep number");
}

PnlVect*
JsonReaderUtils::getPayoffCoefficientsFromJson()
{
    std::vector<double> tempPayoffCoefficients = j.at("payoff coefficients");
    if (tempPayoffCoefficients.size() == 1) {
        int size = getSizeFromJson();
        return pnl_vect_create_from_scalar(size, *tempPayoffCoefficients.data());
    }
    return pnl_vect_create_from_scalar(tempPayoffCoefficients.size(), *tempPayoffCoefficients.data());
}

PnlVect*
JsonReaderUtils::getSpotFromJson()
{
    std::vector<double> tempSpot = j.at("spot");
    if (tempSpot.size() == 1) {
        int size = getSizeFromJson();
        return pnl_vect_create_from_scalar(size, *tempSpot.data());
    }
    return pnl_vect_create_from_scalar(tempSpot.size(), *tempSpot.data());
}

float
JsonReaderUtils::getStrikeFromJson()
{
    return j.at("strike");
}

char*
JsonReaderUtils::getTypeOptionFromJson()
{
    std::string option_type = j.at("option type").get<std::string>();
    char* typeOption = new char[option_type.length() + 1];
    strcpy(typeOption, option_type.c_str());
    return typeOption;
}

PnlVect*
JsonReaderUtils::getVolatilityFromJson()
{
    std::vector<double> tempVolatility = j.at("volatility");
    if (tempVolatility.size() == 1) {
        int size = getSizeFromJson();
        return pnl_vect_create_from_scalar(size, *tempVolatility.data());
    }
    return pnl_vect_create_from_scalar(tempVolatility.size(), *tempVolatility.data());
}

double
JsonReaderUtils::getInterestRateFromJson()
{
    return j.at("DomesticInterestRate");
}

double
JsonReaderUtils::getCorrelationFromJson()
{
    return j.at("correlation");
}

long
JsonReaderUtils::getNbSimuFromJson()
{
    return j.at("sample number");
}

double
JsonReaderUtils::getFdStepFromJson()
{
    return j.at("fd step");
}

double
JsonReaderUtils::getHedgingDatesNumber()
{
    return j.at("hedging dates number");
}

JsonReaderUtils::~JsonReaderUtils()
{
}