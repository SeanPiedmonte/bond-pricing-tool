#include <iostream>
#include <cmath>
#include "core_calc.h"

// Taking our bond input to calculate the periodic coupon payment.
Money pcp(const Bond *bond) {
    Money result(bond->pval);
    result.mult_per(bond->c_rate);
    return result / bond->c_freq;
}

double flat_curve_dr(const Bond *bond) {
    return 1.0 / (1.0 + pow(bond->ytm/bond->c_rate, bond->c_rate*bond->c_freq));
}
