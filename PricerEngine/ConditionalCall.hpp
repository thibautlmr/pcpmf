#include "Option.hpp"
#include "algorithm"

class ConditionalCall : public Option
{
  public:
    double r_;
    PnlVect* strikes_;
    PnlVect *paymentDates_;
    bool isMonitoringDate_;

    ConditionalCall(double T, int size, double r, PnlVect* strike, PnlVect* paymentDates, bool isMonitoringDate);


    /**
     * Calcule la valeur du payoff sur la trajectoire
     *
     * @param[in] path est une matrice de taille (N+1) x d
     * contenant une trajectoire du modèle telle que créée
     * par la fonction asset.
     * @return phi(trajectoire)
     */
    double payoff(const PnlMat* path) override;
};