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
    std_dev = sqrt(squareSum / nbSamples_);
}



void MonteCarlo::delta(const PnlMat *past, double t, PnlVect *delta, PnlVect *std_dev, bool isMonitoringDate) {

    PnlMat *path = pnl_mat_create_from_zero(opt_->size_, opt_->size_);
    PnlMat *pathCopy = pnl_mat_create_from_zero(opt_->size_, opt_->size_);
    double commonFactor = exp(-mod_->r_ * (opt_->T_ - t)) / (2 * fdStep_);
    double interSquare;
    double payoffShiftPlus, payoffShiftMinus;
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

    // Calcul des deltas
    PnlVect *lastRow = pnl_vect_create_from_zero(opt_->size_);
    pnl_mat_get_row(lastRow, past, past->m - 1);

    pnl_vect_mult_scalar(delta, commonFactor / nbSamples_);
    pnl_vect_div_vect_term(delta, lastRow);

    // Calcul des stdDev
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

    // std::cout << "Delta  : " << GET(delta, 0) << "; Delta  stddev : " << GET(std_dev, 0) << std::endl;

    pnl_mat_free(&shiftMinus);
    pnl_mat_free(&shiftPlus);
    pnl_vect_free(&diffShift);
}

//double
//MonteCarlo::p_and_l(PnlMat* marketData, double hedgingNumber, double& prix_init)
//{
//
//    PnlVect *delta = pnl_vect_create(opt_->size_);
//    PnlVect *delta_std_dev = pnl_vect_create_from_zero(opt_->size_);
//    PnlMat *pathPNL = pnl_mat_create_from_zero(opt_->size_ + 1, opt_->size_);
//    PnlVect *newDelta = pnl_vect_create(opt_->size_);
//    PnlVect *stdDevVect = pnl_vect_create(opt_->size_);
//    double currentDate = 0;
//    double stepH = opt_->T_ / hedgingNumber;
//    PnlVect *currentSpots = pnl_vect_create(opt_->size_);
//    pnl_vect_clone(currentSpots, mod_->spot_);
//    double error_pnl = 0;
//    double std_dev = 0;
//    //price(prix_init, std_dev);
//    double vCurrent = 0;
//    double commonFactor = exp(mod_->r_ * opt_->T_ / hedgingNumber);
//    double currentDouble = 0;
//    PnlVect *saveDelta = pnl_vect_create(opt_->size_);
//    PnlMat *past = pnl_mat_create(1, opt_->size_);
//    pnl_mat_set_row(past, mod_->spot_, 0);
//
//    // Initialisation
//    //this->delta(delta, delta_std_dev);
//    pnl_vect_mult_vect_term(currentSpots, delta);
//    vCurrent = prix_init - pnl_vect_sum(currentSpots);
//    std::cout << "price 0 : " << prix_init << std::endl;
//    bool lastWasDiscretizationTime = true;
//    // Boucle
//    for (int i = 1; i <= hedgingNumber; i++) {
//        currentDate += stepH;
//        pnl_vect_clone(saveDelta, delta);
//        updatePast(past, currentDate, i, marketData, lastWasDiscretizationTime);
//        //this->delta(past, currentDate, delta, stdDevVect);
//        //this->price(past, currentDate, prix_init, std_dev);
//        std::cout << "price " << i << " : " << prix_init << std::endl;
//        pnl_vect_clone(newDelta, delta);
//        pnl_mat_get_row(currentSpots, marketData, i);
//        pnl_vect_minus_vect(newDelta, saveDelta);
//        pnl_vect_mult_vect_term(newDelta, currentSpots);
//        currentDouble = pnl_vect_sum(newDelta);
//        vCurrent = vCurrent * commonFactor - currentDouble;
//    }
//
//    // Update path with real market values
//    buildPath(pathPNL, marketData, hedgingNumber);
//
//    // Final calculation
//    pnl_vect_mult_vect_term(currentSpots, saveDelta);
//    double payoff = opt_->payoff(pathPNL);
//    double res = vCurrent + pnl_vect_sum(currentSpots) - payoff;
//
//    pnl_mat_free(&past);
//    pnl_vect_free(&currentSpots);
//    pnl_vect_free(&delta);
//    pnl_vect_free(&delta_std_dev);
//    pnl_mat_free(&pathPNL);
//    pnl_vect_free(&newDelta);
//    pnl_vect_free(&saveDelta);
//    return res;
//}
//
//void
//MonteCarlo::updatePast(PnlMat* past, double t, int index, PnlMat* marketData, bool& lastWasDiscretizationTime)
//{
//    double checkDiscretisation = opt_->T_ / opt_->size_;
//    PnlVect* rowToAdd = pnl_vect_create(opt_->size_);
//
//    pnl_mat_get_row(rowToAdd, marketData, index);
//
//    if (lastWasDiscretizationTime) {
//        // Précédent discrétisation : OK
//        pnl_mat_add_row(past, past->m, rowToAdd);
//    } else {
//        // Précédent discrétisation : KO
//        pnl_mat_set_row(past, rowToAdd, past->m - 1);
//    }
//
//    lastWasDiscretizationTime = (std::fmod(t, checkDiscretisation) == 0) ? true : false;
//}
//
//void
//MonteCarlo::buildPath(PnlMat* path, PnlMat* marketData, double hedgingNumber)
//{
//    int currentIndex = 0;
//    double stepN = hedgingNumber / opt_->size_;
//    for (int i = 0; i <= opt_->size_; i++) {
//        PnlVect* currentRowMD = pnl_vect_create(opt_->size_);
//        pnl_mat_get_row(currentRowMD, marketData, currentIndex);
//        pnl_mat_set_row(path, currentRowMD, i);
//        currentIndex += stepN;
//    }
//}