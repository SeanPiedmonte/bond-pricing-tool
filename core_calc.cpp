#include <iostream>
#include <cmath>
#include "core_calc.h"

// Taking our bond input to calculate the periodic coupon payment.
Money pcp(const Bond *bond) {
    Money result(bond->pval);
    result.mult_per(bond->c_rate);
    return result / bond->c_freq;
}

double ytm(const Bond *bond) {
    Money pval(bond->pval);
    Money cval(bond->cval);
    std::cout << bond->pval << ", " << bond->cval << std::endl;
    std::cout << pval << ", " << cval << std::endl;
    return 0.0;
}

double flat_curve_dr(const Bond *bond) {
    double yieldtm = ytm(bond);
    return 1.0 / (1.0 + pow(yieldtm/bond->c_rate, bond->c_rate*bond->c_freq));
}


