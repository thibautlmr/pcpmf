#pragma once

#include "Option.hpp"
#include "BlackScholesModel.hpp"
#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include <iostream>
#include <cmath>

class MonteCarlo
{
  public:
    BlackScholesModel* mod_; /*! pointeur vers le modèle */
    Option* opt_;            /*! pointeur sur l'option */
    PnlRng* rng_;            /*! pointeur sur le générateur */
    double fdStep_;          /*! pas de différence finie */
    long nbSamples_;         /*! nombre de tirages Monte Carlo */

    MonteCarlo(BlackScholesModel* mod, Option* opt, PnlRng* rng, double fdStep, long nbSamples);

    ~MonteCarlo();

    /**
     * Calcule le prix de l'option à la date t
     *
     * @param[in]  past contient la trajectoire du sous-jacent
     * jusqu'à l'instant t
     * @param[in] t date à laquelle le calcul est fait
     * @param[out] prix contient le prix
     * @param[out] std_dev contient l'écart type de l'estimateur
     */
    void price(const PnlMat* past, double t, double& prix, double& std_dev, bool isMonitoringDate);

    /**
     * Calcule le delta de l'option à la date t
     *
     * @param[in] past contient la trajectoire du sous-jacent
     * jusqu'à l'instant t
     * @param[in] t date à laquelle le calcul est fait
     * @param[out] delta contient le vecteur de delta
     * @param[out] std_dev contient l'écart type de l'estimateur
     */
    void delta(const PnlMat* past, double t, PnlVect* delta, PnlVect* std_dev, bool isMonitoringDate);



    double p_and_l(PnlMat* marketData, double hedgingNumber, double& prix_init);

    void updatePast(PnlMat* past, double t, int index, PnlMat* marketData, bool& lastWasDiscretizationTime);

    void buildPath(PnlMat* path, PnlMat* marketData, double hedgingNumber);

    PnlMat* path_;
    PnlVect* payoffs_;
};
