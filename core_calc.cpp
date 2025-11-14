#include <iostream>
#include <cmath>
#include "core_calc.h"

// Taking our bond input to calculate the periodic coupon payment.
Money pcp(const Bond *bond) {
    Money result(bond->pval);
    result.mult_per(bond->c_rate);
    return result / bond->c_freq;
}

// Newton-Raphson Method for calculating the ytm
double nrm(long long fv, long long cv, double r, long long ppp) {
    long long final = fv/std::pow(r+1, 20) + ppp * ((1 - 1/std::pow(r+1, 20))/r);
    long long derv_f = (ppp*((1/std::pow(1+r,20))+((20*r)/std::pow(1+r,21))-1)/(r*r)) -
                       ((20*fv)/std::pow(r+1,21));
    double r2 = r - double(final-cv)/derv_f;
    return r2;
}

double ytm(const Bond *bond) {
    Money pval(bond->pval);
    Money cval(bond->cval);
    long long c_pay = pval.get_units() * bond->c_rate / bond->c_freq;
    long long dividend = c_pay + ((pval-cval).get_units()/(bond->c_rate*bond->c_freq));
    std::cout << dividend << std::endl;
    return 0.0;
}

double flat_curve_dr(const Bond *bond) {
    double yieldtm = ytm(bond);
    return 1.0 / (1.0 + pow(yieldtm/bond->c_rate, bond->c_rate*bond->c_freq));
}


