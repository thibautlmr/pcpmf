#pragma once
#include <nlohmann/json.hpp>
#include "BlackScholesModelInputParser.hpp"

namespace input_parsers
{
	class CoreBlackScholesModelInputParser : public BlackScholesModelInputParser
	{
	private:
		nlohmann::json json;
	public:
		int get_underlying_number() const;
		int get_monitoring_times() const;
		double get_correlation_parameter() const;
		double get_interest_rate() const;
		double get_final_simulation_date() const;
		PnlVect * get_volatility() const;

		CoreBlackScholesModelInputParser(const nlohmann::json& j) : json(j)
		{};

		virtual ~CoreBlackScholesModelInputParser() {};
	};
}