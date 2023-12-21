#include "MonteCarlo.hpp"

using namespace std;

MonteCarlo::MonteCarlo(BlackScholesModel* mod, Option* opt, PnlRng* rng, double fdStep, long nbSamples)
  : mod_(mod)
  , opt_(opt)
  , rng_(rng)
  , fdStep_(fdStep)
  , nbSamples_(nbSamples)
{
}

MonteCarlo::~MonteCarlo()
{
}

void
MonteCarlo::price(const PnlMat* past, double t, double& prix, double& std_dev, bool isMonitoringDate)
{
    double sum = 0;
    double squareSum = 0;
    double currentPayoff;
    PnlMat *path = pnl_mat_create_from_zero(opt_->size_, opt_->size_);
    double factor = exp(-(mod_->r_) * (opt_->T_ - t));
    for (int i = 0; i <= nbSamples_; i++) {
        mod_->asset(path, t, opt_->T_, rng_, past, isMonitoringDate);
        currentPayoff = opt_->payoff(path);
        sum += currentPayoff;
        squareSum += currentPayoff * currentPayoff;
    }
    pnl_mat_free(&path);
    prix = factor * sum / nbSamples_;
    squareSum = (pow(factor, 2) * squareSum) / nbSamples_ - prix * prix;
    std_dev = sqrt(abs(squareSum / nbSamples_));
}



void MonteCarlo::delta(const PnlMat *past, double t, PnlVect *delta, PnlVect *std_dev, bool isMonitoringDate) {

    PnlMat *path = pnl_mat_create_from_zero(opt_->size_, opt_->size_);
    PnlMat *pathCopy = pnl_mat_create_from_zero(opt_->size_, opt_->size_);
    double commonFactor = exp(-mod_->r_ * (opt_->T_ - t)) / (2 * fdStep_);
    double interSquare;
    double payoffShiftPlus;
    double payoffShiftMinus;
    PnlVect *diffShift = pnl_vect_create_from_zero(opt_->size_);
    PnlMat *shiftPlus = pnl_mat_create_from_zero(opt_->size_, opt_->size_);
    PnlMat *shiftMinus = pnl_mat_create_from_zero(opt_->size_, opt_->size_);
    for (int j = 0; j < delta->size; j++) {
        pnl_vect_set(delta, j, 0);
    }

    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, t, opt_->T_, rng_, past, isMonitoringDate);

        pnl_mat_clone(pathCopy, path);

        for (int k = 0; k < mod_->size_; k++) {
            mod_->shiftAsset(shiftPlus, pathCopy, k, fdStep_, t, isMonitoringDate);
            mod_->shiftAsset(shiftMinus, pathCopy, k, -fdStep_, t, isMonitoringDate);
            payoffShiftPlus = opt_->payoff(shiftPlus);
            payoffShiftMinus = opt_->payoff(shiftMinus);
            pnl_vect_set(diffShift, k, payoffShiftPlus - payoffShiftMinus);

            interSquare = (payoffShiftPlus - payoffShiftMinus) * (payoffShiftPlus - payoffShiftMinus);
            pnl_vect_set(std_dev, k, pnl_vect_get(std_dev, k) + interSquare);
        }
        pnl_vect_plus_vect(delta, diffShift);
    }

    // deltas computation
    PnlVect *lastRow = pnl_vect_create_from_zero(opt_->size_);
    pnl_mat_get_row(lastRow, past, past->m - 1);

    pnl_vect_mult_scalar(delta, commonFactor / nbSamples_);
    pnl_vect_div_vect_term(delta, lastRow);

    // stdDev computation
    double tmp = 0;
    double currentAsset = 0;
    double currentDelta = 0;
    for (int i = 0; i < opt_->size_; i++) {
        tmp = GET(std_dev, i);
        currentAsset = GET(lastRow, i);
        currentDelta = GET(delta, i);
        tmp = tmp * pow(commonFactor, 2) / (pow(currentAsset, 2) * nbSamples_) - pow(currentDelta, 2);
        pnl_vect_set(std_dev, i, sqrt(abs(tmp/ nbSamples_)));
    }
    pnl_mat_free(&shiftMinus);
    pnl_mat_free(&shiftPlus);
    pnl_vect_free(&diffShift);
}