/*
* CORE CALCULATIONS
*
* This header handles the core computational functionality for our bond
* calculator.
*/

/*
 * name: Bond
 *
 * fields:
 *  - pval: Face value
 *  - c_rate: Coupon Rate / Annual Percentage
 *  - c_freq: Coupon frequency, 0 = annual, 1 = semiannual, 2 = quarterly
 *  - ttm: Time to Maturity in years
 *  - ytm: Yield to Maturity / Annual Yield
 */
typedef struct {
    long int pval;
    int c_rate;
    int c_freq;
    int ttm;
    int ytm;
} Bond;

int pcp(const Bond *bond);
