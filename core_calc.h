/*
* CORE CALCULATIONS
*
* This header handles the core computational functionality for our bond
* calculator.
*/
#include "Money.h"

/*
 * name: Bond
 *
 * fields:
 *  - pval: Face value
 *  - c_rate: Coupon Rate / Annual Percentage
 *  - c_freq: Coupon frequency, 0 = annual, 1 = semiannual, 2 = quarterly
 *  - ttm: Time to Maturity in years
 *  - cval: Current value 
 */
typedef struct {
    std::string pval;
    double c_rate;
    int c_freq;
    int ttm;
    std::string cval;
} Bond;

// Calculates the periodic coupon payment using our Bond as an input
Money pcp(const Bond *bond);

double flat_curve_dr(const Bond *bond);

double ytm(const Bond *bond); 
