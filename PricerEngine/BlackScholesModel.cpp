#include "BlackScholesModel.hpp"

// Constructeur de la classe
BlackScholesModel::BlackScholesModel(int size, double r, const PnlVect* sigma, const PnlMat* vol_cholesky, const PnlVect* paymentDates)
  : size_(size)
  , r_(r)
{
    sigma_ = pnl_vect_copy(sigma);
    vol_cholesky_ = pnl_mat_copy(vol_cholesky);
    paymentDates_ = pnl_vect_copy(paymentDates);
    sCurrent_ = pnl_vect_create_from_zero(size_);
    sNext_ = pnl_vect_copy(sCurrent_);
    G_ = pnl_vect_create_from_zero(size_);
    choleskyRow_ = pnl_vect_create_from_zero(size_);
    tmpG_ = pnl_vect_create_from_zero(size_);
    column_ = pnl_mat_new();
}

// Destructeur de la classe
BlackScholesModel::~BlackScholesModel()
{
    pnl_vect_free(&sigma_);
    pnl_vect_free(&G_);
    pnl_vect_free(&choleskyRow_);
    pnl_vect_free(&tmpG_);
    pnl_vect_free(&sCurrent_);
    pnl_vect_free(&sNext_);
    pnl_mat_free(&column_);
}


void
BlackScholesModel::asset(PnlMat* path, double t, double T, PnlRng* rng, const PnlMat* past, bool isMonitoringDate)
{
    // Initialisation
    int d = size_;
    double step = 0;
    int followingMonitoringIndex = 0;
    double assetCurrentValue, drift, assetNextValue;

    double nbPast = past->m;
    pnl_mat_get_row(sCurrent_, past, nbPast - 1);
    sNext_ = pnl_vect_copy(sCurrent_);
    PnlVect *currentVect = pnl_vect_create_from_zero(d);

    // Remplissage de path avec le past
    for (int i = 0; i < nbPast - 1; i++) {
        pnl_mat_get_row(currentVect, past, i);
        pnl_mat_set_row(path, currentVect, i);
    }

    if (isMonitoringDate) {
        pnl_mat_get_row(currentVect, past, nbPast - 1);
        pnl_mat_set_row(path, currentVect, nbPast - 1);
    } else {
        while (t > GET(paymentDates_, followingMonitoringIndex)) {
            followingMonitoringIndex += 1;
        }
        step = GET(paymentDates_, followingMonitoringIndex) - t;
        pnl_vect_rng_normal_d(G_, size_, rng);
        for (int j = 0; j < d; j++) {

            assetCurrentValue = pnl_vect_get(sCurrent_, j);

            // Calcul de la prochaine valeur de trajectoire pour l'actif considéré
            drift = (r_ - (pnl_vect_get(sigma_, j) * pnl_vect_get(sigma_, j)) / 2) * (step);

            pnl_mat_get_row(choleskyRow_, vol_cholesky_, j);
            pnl_vect_clone(tmpG_, G_);
            pnl_vect_mult_vect_term(tmpG_, choleskyRow_);

            assetNextValue = assetCurrentValue * exp(drift + sqrt(step) * pnl_vect_sum(tmpG_));

            pnl_vect_set(sNext_, j, assetNextValue);
        }
        // Actualisation des tableaux
        sCurrent_ = pnl_vect_copy(sNext_);
        // Remplissage de la matrice de trajectoires
        pnl_mat_set_row(path, sNext_, nbPast - 1);
    }

    // Boucle sur le temps
    for (int i = nbPast; i < path->m; i++) {
        step = GET(paymentDates_, i) - GET(paymentDates_, i - 1);
        // Boucle sur les actifs
        pnl_vect_rng_normal_d(G_, size_, rng);
        for (int j = 0; j < d; j++) {

            assetCurrentValue = pnl_vect_get(sCurrent_, j);

            // Calcul de la prochaine valeur de trajectoire pour l'actif considéré
            drift = (r_ - (pnl_vect_get(sigma_, j) * pnl_vect_get(sigma_, j)) / 2) * (step);

            pnl_mat_get_row(choleskyRow_, vol_cholesky_, j);
            pnl_vect_clone(tmpG_, G_);
            pnl_vect_mult_vect_term(tmpG_, choleskyRow_);

            assetNextValue = assetCurrentValue * exp(drift + sqrt(step) * pnl_vect_sum(tmpG_));

            pnl_vect_set(sNext_, j, assetNextValue);
        }
        // Actualisation des tableaux
        sCurrent_ = pnl_vect_copy(sNext_);
        // Remplissage de la matrice de trajectoires
        pnl_mat_set_row(path, sNext_, i);
    }
}

void
BlackScholesModel::shiftAsset(PnlMat* shiftPath, const PnlMat* path, int d, double h, double t, bool isMonitoringDate)
{

    // Initialisation des varaibles
    int dMax = path->n;
    int startingShiftIndex = shiftPath->m - 1;
    pnl_mat_clone(shiftPath, path);

    // Vérification de la validité des inputs
    if (d < 0 || d >= dMax) {
        std::cerr << "Error : Invalid index input." << std::endl;
        return;
    }

    // Calcul de l'indice de début de shift
    if (isMonitoringDate) {
        for (int i = 0; i < paymentDates_->size - 1; i++) {
            if (abs(GET(paymentDates_, i)) < pow(10, -6)) {
                startingShiftIndex = i + 1;
            }
        }    
    } else {
        startingShiftIndex = 0;
        while (GET(paymentDates_, startingShiftIndex) < t) {
            startingShiftIndex++;
        }
    }
    // Parcours de shiftPath en appliquant le shift
    // pnl_mat_resize(column_, shiftPath->m, 1);
    for (int l = startingShiftIndex; l < shiftPath->m; l++) {
        pnl_mat_set(shiftPath, l, d, (1 + h) * pnl_mat_get(shiftPath, l, d));
    }
}