#include "Option.hpp"

Option::Option(double T, int size)
  : T_(T)
  , size_(size)
{
}

Option::Option(char* jsonPath)
{
    JsonReaderUtils* jsonReaderUtils = new JsonReaderUtils(jsonPath);
    char* typeOption = jsonReaderUtils->getTypeOptionFromJson();
    if (!jsonReaderUtils->isTypeOption(typeOption)) {
        throw std::invalid_argument("You are trying to instantiate a wrong Option type object from a JSON file that does t describe such an object.");
    }
    this->T_ = jsonReaderUtils->getMaturityFromJson();
    this->size_ = jsonReaderUtils->getSizeFromJson();
}