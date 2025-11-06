#include <iostream>
#include "core_calc.h"

// Taking our bond input to calculate the periodic coupon payment.
int pcp(const Bond *bond) {
    long int c_pay = bond->c_rate * bond->pval / 100000;
    std::cout << c_pay << std::endl;
    return 0;
}
