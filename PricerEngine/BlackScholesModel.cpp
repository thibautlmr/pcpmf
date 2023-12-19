#include "BlackScholesModel.hpp"

// Constructeur de la classe
BlackScholesModel::BlackScholesModel(int size, double r, double rho, const PnlVect* sigma, const PnlVect* spot)
  : size_(size)
  , r_(r)
  , rho_(rho)
{
    sigma_ = pnl_vect_copy(sigma);
    spot_ = pnl_vect_copy(spot);
    cholesky_ = pnl_mat_create_from_scalar(size_, size_, rho_);
    pnl_mat_set_diag(cholesky_, 1, 0);
    pnl_mat_chol(cholesky_);
    sCurrent_ = pnl_vect_copy(spot_);
    sNext_ = pnl_vect_copy(spot_);
    G_ = pnl_vect_create(size_);
    choleskyRow_ = pnl_vect_create(size_);
    tmpG_ = pnl_vect_create(size_);
    column_ = pnl_mat_new();
}

// Destructeur de la classe
BlackScholesModel::~BlackScholesModel()
{
    pnl_vect_free(&sigma_);
    pnl_vect_free(&spot_);
    pnl_mat_free(&cholesky_);
    pnl_vect_free(&G_);
    pnl_vect_free(&choleskyRow_);
    pnl_vect_free(&tmpG_);
    pnl_vect_free(&sCurrent_);
    pnl_vect_free(&sNext_);
    pnl_mat_free(&column_);
}

void
BlackScholesModel::asset(PnlMat* path, double T, int nbTimeSteps, PnlRng* rng)
{

    pnl_vect_clone(sCurrent_, spot_);
    pnl_vect_clone(sNext_, spot_);

    // Initialisation
    double dt = T / nbTimeSteps;

    // Initilisation de path avec les valeurs initiales des assets
    pnl_mat_set_row(path, spot_, 0);

    double assetCurrentValue, drift, diffusion, assetNextValue;
    double volAsset;

    // Boucle sur le temps
    for (int i = 1; i <= nbTimeSteps; i++) {
        pnl_vect_rng_normal_d(G_, size_, rng);
        // Boucle sur les actifs
        for (int j = 0; j < size_; j++) {
            assetCurrentValue = pnl_vect_get(sCurrent_, j);

            // Calcul de la prochaine valeur de trajectoire pour l'actif considéré
            volAsset = pnl_vect_get(sigma_, j);
            drift = (r_ - (volAsset * volAsset) / 2) * dt;
            diffusion = volAsset * sqrt(dt);

            pnl_mat_get_row(choleskyRow_, cholesky_, j);
            pnl_vect_clone(tmpG_, G_);
            pnl_vect_mult_vect_term(tmpG_, choleskyRow_);
            assetNextValue = assetCurrentValue * exp(drift + diffusion * pnl_vect_sum(tmpG_));

            pnl_vect_set(sNext_, j, assetNextValue);
        }
        // Actualisation des tableaux
        pnl_vect_clone(sCurrent_, sNext_);

        // Remplissage de la matrice de trajectoires
        pnl_mat_set_row(path, sNext_, i);
    }
}

void
BlackScholesModel::asset(PnlMat* path, double t, double T, int nbTimeSteps, PnlRng* rng, const PnlMat* past)
{

    // Initialisation
    int d = size_;
    double dt = T / nbTimeSteps;
    PnlVect* S_current;
    double nbPast = (int)(t / dt);
    double nbGenerate = nbTimeSteps - nbPast;
    pnl_mat_get_row(S_current, past, nbPast - 1);
    PnlVect* S_next = pnl_vect_copy(S_current);
    PnlVect* currentVect;

    // Remplissage de path avec le past
    for (int i = 0; i < nbPast; i++) {
        pnl_mat_get_row(currentVect, past, i);
        pnl_mat_set_row(path, currentVect, i);
    }

    // Boucle sur le temps
    for (int i = nbPast; i < nbTimeSteps; i++) {

        // Boucle sur les actifs
        for (int j = 0; j < d; j++) {
            double asset_current_value = pnl_vect_get(S_current, j);

            // Calcul variable aléatoire gaussienne
            double gaussian = pnl_rng_normal(rng);

            // Calcul de la prochaine valeur de trajectoire pour l'actif considéré
            double drift = (r_ - (pnl_vect_get(sigma_, j) * pnl_vect_get(sigma_, j)) / 2) * dt;
            double diffusion = pnl_vect_get(sigma_, j) * sqrt(dt);

            double asset_next_value = asset_current_value * exp(drift + diffusion * gaussian);

            pnl_vect_set(S_next, j, asset_next_value);
        }
        // Actualisation des tableaux
        S_current = pnl_vect_copy(S_next);
        // Remplissage de la matrice de trajectoires
        pnl_mat_set_row(path, S_next, i);
    }
}

void
BlackScholesModel::shiftAsset(PnlMat* shiftPath, const PnlMat* path, int d, double h, double t, double timestep)
{

    // Initialisation des varaibles
    int nbTimeSteps = path->m - 1;
    int dMax = path->n;

    // Vérification de la validité des inputs
    if (d < 0 || d >= dMax) {
        std::cerr << "Error : Invalid index input." << std::endl;
        return;
    }

    // Copie de la trajectoire d'origine dans shiftPath
    pnl_mat_clone(shiftPath, path);

    // Calcul de l'indice de début de shift
    int startingShiftIndex = (t / timestep);

    // Parcours de shiftPath en appliquant le shift
    pnl_mat_resize(column_, shiftPath->m, 1);
    pnl_mat_extract_subblock(column_, shiftPath, startingShiftIndex, nbTimeSteps - startingShiftIndex + 1, d, 1);
    pnl_mat_mult_scalar(column_, 1 + h);
    pnl_mat_set_subblock(shiftPath, column_, startingShiftIndex, d);
}