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
MonteCarlo::price(double& prix, double& std_dev)
{
    double sum = 0;
    double squareSum = 0;
    PnlMat* path = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
    PnlVect* payoffs = pnl_vect_create(nbSamples_);
    double currentPayoff;
    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, opt_->T_, opt_->nbTimeSteps_, rng_);
        currentPayoff = opt_->payoff(path);
        sum += currentPayoff;
        LET(payoffs, i) = currentPayoff;
    }
    pnl_mat_free(&path);
    double mean = sum / (nbSamples_);
    double deviation = 0;
    for (int j = 0; j < nbSamples_; j++) {
        deviation = GET(payoffs, j) - mean;
        squareSum += deviation * deviation;
    }
    pnl_vect_free(&payoffs);
    double factor = exp(-(mod_->r_) * (opt_->T_));
    std_dev = factor * sqrt(squareSum) / nbSamples_;
    prix = factor * mean;
    double lower_bound = prix - 1.96 * std_dev / sqrt(nbSamples_);
    double upper_bound = prix + 1.96 * std_dev / sqrt(nbSamples_);
}

void
MonteCarlo::price(const PnlMat* past, double t, double& prix, double& std_dev)
{
    double sum, squareSum;
    PnlMat* path = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
    PnlVect* payoffs = pnl_vect_create(nbSamples_);
    for (int i = 0; i <= nbSamples_; i++) {
        mod_->asset(path, t, opt_->T_, opt_->nbTimeSteps_, rng_, past);
        sum += opt_->payoff(path);
        LET(payoffs, i) = opt_->payoff(path);
    }
    double mean = sum / (nbSamples_);
    for (int j = 0; j <= nbSamples_; j++) {
        squareSum += (GET(payoffs, j) - mean) * (GET(payoffs, j) - mean);
    }
    double factor = exp(-(mod_->r_) * (opt_->T_));
    std_dev = factor * sqrt(squareSum / nbSamples_);
    prix = factor * mean;
    double lower_bound = prix - 1.96 * std_dev / sqrt(nbSamples_);
    double upper_bound = prix + 1.96 * std_dev / sqrt(nbSamples_);
}

void
MonteCarlo::delta(PnlVect* delta, PnlVect* std_dev)
{

    PnlMat* path = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
    double timeStep = (opt_->T_ / opt_->nbTimeSteps_);
    const int modSize = mod_->size_;
    std::vector<double> factor(modSize, 0.0);
    double commonFactor = exp(-mod_->r_ * (opt_->T_)) / (nbSamples_ * 2 * fdStep_);

    PnlMat* deltasMat = pnl_mat_create(nbSamples_, opt_->size_);
    PnlMat* shiftPlus = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
    PnlMat* shiftMinus = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
    double payoffShiftPlus, payoffShiftMinus;
    PnlVect* diffShift = pnl_vect_create(opt_->size_);

    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, opt_->T_, opt_->nbTimeSteps_, rng_);
        for (int k = 0; k < mod_->size_; k++) {
            mod_->shiftAsset(shiftPlus, path, k, fdStep_, 0, timeStep);
            mod_->shiftAsset(shiftMinus, path, k, -fdStep_, 0, timeStep);
            payoffShiftPlus = opt_->payoff(shiftPlus);
            payoffShiftMinus = opt_->payoff(shiftMinus);
            pnl_vect_set(diffShift, k, payoffShiftPlus - payoffShiftMinus);
        }
        pnl_vect_plus_vect(delta, diffShift);
        pnl_vect_mult_vect_term(diffShift, diffShift);
        pnl_mat_set_row(deltasMat, diffShift, i);
    }

    PnlVect* tmp = pnl_vect_create(opt_->size_);
    PnlVect* deltaBis = pnl_vect_copy(delta);
    pnl_vect_div_scalar(deltaBis, nbSamples_);
    pnl_vect_mult_vect_term(deltaBis, deltaBis);

    for (int i = 0; i < nbSamples_; i++) {
        pnl_mat_get_row(tmp, deltasMat, i);
        pnl_vect_plus_vect(std_dev, tmp);
        pnl_vect_minus_vect(std_dev, deltaBis);
    }
    for (int i = 0; i < mod_->size_; i++) {
        factor[i] = (commonFactor / pnl_mat_get(path, 0, i));
        pnl_vect_set(delta, i, factor[i] * pnl_vect_get(delta, i));
        pnl_vect_set(std_dev, i, factor[i] * sqrt(pnl_vect_get(std_dev, i)));
    }
    pnl_mat_free(&path);
    pnl_mat_free(&deltasMat);
    pnl_mat_free(&shiftPlus);
    pnl_mat_free(&shiftMinus);
    pnl_vect_free(&deltaBis);
    pnl_vect_free(&diffShift);
    pnl_vect_free(&tmp);
}

void
MonteCarlo::delta(const PnlMat* past, double t, PnlVect* delta, PnlVect* std_dev)
{

    PnlMat* path = pnl_mat_create(opt_->nbTimeSteps_ + 1, opt_->size_);
    PnlMat* pathCopy;
    double timeStep = (opt_->T_ / opt_->nbTimeSteps_);
    const int modSize = mod_->size_;
    std::vector<double> factor(modSize, 0.0);
    double commonFactor = exp(-mod_->r_ * (opt_->T_ - t)) / (nbSamples_ * 2 * fdStep_);
    double interSquare;

    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, t, opt_->T_, opt_->nbTimeSteps_, rng_, past);

        pathCopy = pnl_mat_copy(path);
        PnlMat* shift_plus = pnl_mat_copy(pathCopy);
        PnlMat* shift_moins = pnl_mat_copy(pathCopy);
        for (int k = 0; k < mod_->size_; k++) {
            mod_->shiftAsset(shift_plus, pathCopy, k, fdStep_, t, timeStep);
            mod_->shiftAsset(shift_moins, pathCopy, k, fdStep_, t, timeStep);
            pnl_vect_set(delta, k, pnl_vect_get(delta, k) + (opt_->payoff(shift_plus) - opt_->payoff(shift_moins)));
        }
    }

    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, opt_->T_, opt_->nbTimeSteps_, rng_);
        pathCopy = pnl_mat_copy(path);
        PnlMat* shift_plus = pnl_mat_copy(pathCopy);
        PnlMat* shift_moins = pnl_mat_copy(pathCopy);
        for (int k = 0; k < mod_->size_; k++) {
            interSquare = 0;
            mod_->shiftAsset(shift_plus, pathCopy, k, fdStep_, 0, timeStep);
            mod_->shiftAsset(shift_moins, pathCopy, k, -fdStep_, 0, timeStep);
            interSquare = (opt_->payoff(shift_plus) - opt_->payoff(shift_moins)) * (opt_->payoff(shift_plus) - opt_->payoff(shift_moins));
            pnl_vect_set(std_dev, k, pnl_vect_get(std_dev, k) + (interSquare - ((pnl_vect_get(delta, k)) / nbSamples_) * ((pnl_vect_get(delta, k)) / nbSamples_)));
        }
    }

    for (int i = 0; i < mod_->size_; i++) {
        factor[i] = (commonFactor / pnl_mat_get(path, t, i));
        pnl_vect_set(delta, i, factor[i] * pnl_vect_get(delta, i));
    }

    for (int k = 0; k < mod_->size_; k++) {
        pnl_vect_set(std_dev, k, factor[k]);
    }
}

double
MonteCarlo::p_and_l(PnlMat* marketData, double hedgingNumber, double& prix_init)
{

    PnlVect* delta = pnl_vect_create(opt_->size_);
    PnlMat* pathPNL = pnl_mat_create_from_zero(opt_->nbTimeSteps_ + 1, opt_->size_);
    PnlVect* newDelta = pnl_vect_create(opt_->size_);
    PnlVect* stdDevVect = pnl_vect_create(opt_->size_);
    double currentDate = 0;
    double stepH = opt_->T_ / hedgingNumber;
    PnlVect* currentSpots = pnl_vect_copy(mod_->spot_);
    double error_pnl = 0;
    double std_dev = 0;
    price(prix_init, std_dev);
    double vCurrent = 0;
    double commonFactor = exp(mod_->r_ * opt_->T_ / hedgingNumber);
    double currentDouble;
    PnlVect* saveDelta = pnl_vect_create(opt_->size_);

    // Initialisation
    this->delta(delta, stdDevVect);
    pnl_vect_mult_vect_term(currentSpots, delta);
    vCurrent = prix_init - pnl_vect_sum(currentSpots);
    PnlMat* past = pnl_mat_create(1, opt_->size_);
    pnl_mat_set_row(past, mod_->spot_, 0);
    bool lastWasDiscretizationTime = true;
    // Boucle
    for (int i = 1; i <= hedgingNumber; i++) {
        currentDate += stepH;
        saveDelta = pnl_vect_copy(delta);
        updatePast(past, currentDate, i, marketData, lastWasDiscretizationTime);
        this->delta(past, currentDate, delta, stdDevVect);
        newDelta = pnl_vect_copy(delta);
        pnl_mat_get_row(currentSpots, marketData, i);
        pnl_vect_minus_vect(newDelta, saveDelta);
        pnl_vect_mult_vect_term(newDelta, currentSpots);
        currentDouble = pnl_vect_sum(newDelta);
        vCurrent = vCurrent * commonFactor - currentDouble;
        pnl_vect_clone(delta, saveDelta);
    }

    // Update path with real market values
    buildPath(pathPNL, marketData, hedgingNumber);

    // Final calculation
    pnl_vect_mult_vect_term(currentSpots, saveDelta);

    return vCurrent + pnl_vect_sum(currentSpots) - opt_->payoff(pathPNL);
}

void
MonteCarlo::updatePast(PnlMat* past, double t, int index, PnlMat* marketData, bool& lastWasDiscretizationTime)
{
    double checkDiscretisation = opt_->T_ / opt_->nbTimeSteps_;
    PnlVect* rowToAdd = pnl_vect_create(opt_->size_);

    pnl_mat_get_row(rowToAdd, marketData, index);

    if (lastWasDiscretizationTime) {
        // Précédent discrétisation : OK
        pnl_mat_add_row(past, past->m, rowToAdd);
    } else {
        // Précédent discrétisation : KO
        pnl_mat_set_row(past, rowToAdd, past->m - 1);
    }

    lastWasDiscretizationTime = (std::fmod(t, checkDiscretisation) == 0) ? true : false;
}

void
MonteCarlo::buildPath(PnlMat* path, PnlMat* marketData, double hedgingNumber)
{
    int currentIndex = 0;
    double stepN = hedgingNumber / opt_->nbTimeSteps_;
    for (int i = 0; i <= opt_->nbTimeSteps_; i++) {
        PnlVect* currentRowMD = pnl_vect_create(opt_->size_);
        pnl_mat_get_row(currentRowMD, marketData, currentIndex);
        pnl_vect_print(currentRowMD);
        pnl_mat_set_row(path, currentRowMD, i);
        currentIndex += stepN;
    }
}