#pragma once

#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "JsonReaderUtils.hpp"

/// \brief Classe Option abstraite
class Option
{
  public:
    double T_;        /// maturité
    int size_;        /// dimension du modèle, redondant avec BlackScholesModel::size_

    Option(double T, int size);

    //~Option();

    Option(char* jsonPath);
    /**
     * Calcule la valeur du payoff sur la trajectoire
     *
     * @param[in] path est une matrice de taille (N+1) x d
     * contenant une trajectoire du modèle telle que créée
     * par la fonction asset.
     * @return phi(trajectoire)
     */
    virtual double payoff(const PnlMat* path) = 0;
};
