#pragma once
#include <nlohmann/json.hpp>
#include "BarrierOptionInputParser.hpp"


namespace input_parsers
{
	class CoreBarrierOptionInputParser : public BarrierOptionInputParser
	{
	private:
		nlohmann::json json;
	public:
		int get_underlying_number() const final;
		double get_maturity() const;
		double get_strike() const;
		PnlVect * get_payoff_coefficients() const;
		PnlVect * get_lower_barrier() const;
		PnlVect * get_upper_barrier() const;
		CoreBarrierOptionInputParser(const nlohmann::json &j) : json(j)
		{};
		~CoreBarrierOptionInputParser() {};
	};
}