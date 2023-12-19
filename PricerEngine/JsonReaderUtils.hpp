#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

class JsonReaderUtils
{
  public:
    char* jsonPath_;
    nlohmann::json j;

    JsonReaderUtils(char* jsonPath);
    bool isTypeOption(char* typeOption);
    double getMaturityFromJson();
    int getSizeFromJson();
    int getNbTimeStepFromJson();
    PnlVect* getPayoffCoefficientsFromJson();
    PnlVect* getSpotFromJson();
    float getStrikeFromJson();
    char* getTypeOptionFromJson();
    PnlVect* getVolatilityFromJson();
    double getInterestRateFromJson();
    double getCorrelationFromJson();
    long getNbSimuFromJson();
    double getFdStepFromJson();
    double getHedgingDatesNumber();
    ~JsonReaderUtils();
};
