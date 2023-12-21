#pragma once

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

/// \brief Modèle de Black Scholes
class BlackScholesModel
{
  public:
    int size_;         /// nombre d'actifs du modèle
    double r_;         /// taux d'intérêt
    PnlVect* sigma_;   /// vecteur de volatilités
    PnlMat* vol_cholesky_; ///
    PnlVect *paymentDates_;

    BlackScholesModel(int size_, double r_, const PnlVect* sigma_, const PnlMat* vol_cholesky_, const PnlVect* paymentDates_);

    ~BlackScholesModel();
    /**
     * Génère une trajectoire du modèle et la stocke dans path
     *
     * @param[out] path contient une trajectoire du modèle.
     * C'est une matrice de taille (nbTimeSteps+1) x d
     * @param[in] T  maturité
     * @param[in] nbTimeSteps nombre de dates de constatation
     */

    void asset(PnlMat *path, double t, double T, PnlRng *rng, const PnlMat *past, bool isMonitoringDate);

    /**
     * Calcule une trajectoire du modèle connaissant le
     * passé jusqu' à la date t
     *
     * @param[out] path  contient une trajectoire du sous-jacent. La partie jusqu'à
     * l'instant t est données par la matrice past
     * @param[in] t date jusqu'à laquelle on connait la trajectoire.
     * t n'est pas forcément une date de discrétisation
     * @param[in] nbTimeSteps nombre de pas de constatation
     * @param[in] T date jusqu'à laquelle on simule la trajectoire
     * @param[in] past trajectoire réalisée jusqu'a la date t
     */
    /**
     * Shift d'une trajectoire du sous-jacent
     *
     * @param[in]  path contient en input la trajectoire
     * du sous-jacent
     * @param[out] shift_path contient la trajectoire path dont la
     * composante d a été shiftée par (1+h) à partir de la date t.
     * @param[in] t date à partir de laquelle on shift
     * @param[in] h pas de différences finies
     * @param[in] d indice du sous-jacent à shifter
     * @param[in] timestep pas de constatation du sous-jacent
     */
    void shiftAsset(PnlMat* shift_path, const PnlMat* path, int d, double h, double t, bool isMonitoringDate);

  private:
    PnlVect* sCurrent_;
    PnlVect* sNext_;
    PnlVect* G_;
    PnlVect* choleskyRow_;
    PnlVect* tmpG_;
    PnlMat* column_;
};
