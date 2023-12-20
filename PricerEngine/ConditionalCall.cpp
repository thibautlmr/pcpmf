#include "ConditionalCall.hpp"
#include <cmath>


ConditionalCall::ConditionalCall(double T, int size, double r, PnlVect* strikes, PnlVect* paymentDates, bool isMonitoringDate)
  : Option(T, size)
{
    r_ = r;
    strikes_ = pnl_vect_copy(strikes);
    paymentDates_ = pnl_vect_copy(paymentDates);
    isMonitoringDate_ = isMonitoringDate;

}

double
ConditionalCall::payoff(const PnlMat* path)
{
    double currentPayoff;
    for (int i = 0; i < paymentDates_->size; i++) {
        currentPayoff = MGET(path, i, i) - GET(strikes_, i);
        if (currentPayoff > 0) {
            currentPayoff *= exp(r_ * (T_ - GET(paymentDates_, i )));
            return currentPayoff;
        }
    }
    return 0;
}