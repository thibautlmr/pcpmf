#include "CoreBlackScholesModelInputParser.hpp"
#include "json_helper.hpp"

using namespace input_parsers;

int CoreBlackScholesModelInputParser::get_underlying_number() const
{
	int result;
	json.at("option size").get_to(result);
	return result;
}

int CoreBlackScholesModelInputParser::get_monitoring_times() const
{
	int result;
	json.at("timestep number").get_to(result);
	return result;
}

double CoreBlackScholesModelInputParser::get_correlation_parameter() const
{
	double result;
	json.at("correlation").get_to(result);
	return result;
}

double CoreBlackScholesModelInputParser::get_interest_rate() const
{
	double result;
	json.at("interest rate").get_to(result);
	return result;
}

double CoreBlackScholesModelInputParser::get_final_simulation_date() const
{
	double result;
	json.at("maturity").get_to(result);
	return result;
}

PnlVect * CoreBlackScholesModelInputParser::get_volatility() const
{
	PnlVect * result;
	json.at("volatility").get_to(result);
	return result;
}