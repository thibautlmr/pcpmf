#include <iostream>
#include "json_reader.hpp"
#include "pricer.hpp"
#include "BlackScholesModel.hpp"
#include "MonteCarlo.hpp"
#include "Option.hpp"
#include "VanillaOption.hpp"
#include "pnl/pnl_finance.h"

BlackScholesPricer::BlackScholesPricer(nlohmann::json &jsonParams) {
    jsonParams.at("VolCholeskyLines").get_to(volatility);
    jsonParams.at("MathPaymentDates").get_to(paymentDates);
    jsonParams.at("Strikes").get_to(strikes);
    jsonParams.at("DomesticInterestRate").get_to(interestRate);
    jsonParams.at("RelativeFiniteDifferenceStep").get_to(fdStep);
    jsonParams.at("SampleNb").get_to(nSamples);
    nAssets = volatility->n;
}

BlackScholesPricer::~BlackScholesPricer() {
    pnl_vect_free(&paymentDates);
    pnl_vect_free(&strikes);
    pnl_mat_free(&volatility);
}

void BlackScholesPricer::print() {
    std::cout << "nAssets: " << nAssets << std::endl;
    std::cout << "fdStep: " << fdStep << std::endl;
    std::cout << "nSamples: " << nSamples << std::endl;
    std::cout << "strikes: ";
    pnl_vect_print_asrow(strikes);
    std::cout << "paymentDates: ";
    pnl_vect_print_asrow(paymentDates);
    std::cout << "volatility: ";
    pnl_mat_print(volatility);
}

void BlackScholesPricer::priceAndDeltas(const PnlMat *past, double currentDate, bool isMonitoringDate, double &price, double &priceStdDev, PnlVect* &deltas, PnlVect* &deltasStdDev) {
    price = 0.;
    priceStdDev = 0.;
    deltas = pnl_vect_create_from_zero(nAssets);
    deltasStdDev = pnl_vect_create_from_zero(nAssets);
    double maturity = GET(this->paymentDates, 0);
    double strike = GET(this->strikes, 0);
    double interestRate = this->interestRate;
    PnlMat *pastTmp = pnl_mat_create_from_scalar(1, 1, 100);
    PnlVect *spot = pnl_vect_create_from_scalar(1, 100);
    PnlVect *vol = pnl_vect_create_from_scalar(1, MGET(this->volatility, 0, 0));
    BlackScholesModel *bsm = new BlackScholesModel(1, interestRate, 1., vol, spot);
    VanillaOption *option = new VanillaOption(maturity, 250, 1, strike);
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));
    MonteCarlo *mc = new MonteCarlo(bsm, option, rng, this->fdStep, this->nSamples);
    mc->price(pastTmp, 0, price, priceStdDev);
    mc->delta(pastTmp, 0, deltas, deltasStdDev);
    double delta;
    double expectedPrice;
    pnl_cf_call_bs(100., strike, maturity, interestRate, 0., 0.2, &expectedPrice, &delta);
    std::cout << "Le prix theorique de cette option en 0 est : " << expectedPrice << std::endl;
    std::cout << "Le prix obtenu de cette option en 0 est : " << price << std::endl;
    std::cout << "Le delta obtenu de cette option en 0 est : " << GET(deltas, 0) << std::endl;
}