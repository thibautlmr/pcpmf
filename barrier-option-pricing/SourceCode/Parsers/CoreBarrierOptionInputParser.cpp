#include "CoreBarrierOptionInputParser.hpp"
#include "json_helper.hpp"

using namespace input_parsers;

int CoreBarrierOptionInputParser::get_underlying_number() const
{
	int result;
	json.at("option size").get_to(result);
	return result;
}

double CoreBarrierOptionInputParser::get_maturity() const
{
	double result;
	json.at("maturity").get_to(result);
	return result;
}

double CoreBarrierOptionInputParser::get_strike() const
{
	double result;
	json.at("strike").get_to(result);
	return result;
}

PnlVect * CoreBarrierOptionInputParser::get_payoff_coefficients() const
{
	PnlVect * result;
	json.at("payoff coefficients").get_to(result);
	return result;
}

PnlVect * CoreBarrierOptionInputParser::get_lower_barrier() const
{
	PnlVect * result;
	json.at("lower barrier").get_to(result);
	return result;
}

PnlVect * CoreBarrierOptionInputParser::get_upper_barrier() const
{
	PnlVect * result;
	json.at("upper barrier").get_to(result);
	return result;
}