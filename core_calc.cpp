#include <iostream>
#include "core_calc.h"

// Taking our bond input to calculate the periodic coupon payment.
Money pcp(const Bond *bond) {
    Money result(bond->pval);
    return result;
}
