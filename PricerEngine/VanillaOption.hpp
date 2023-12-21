#include "Option.hpp"
#include "algorithm"

class VanillaOption : public Option
{
  public:
    double strike_;

    VanillaOption(double T, int size, double strike);

    VanillaOption(char* jsonPath);

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