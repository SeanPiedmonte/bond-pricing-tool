/*
* CORE CALCULATIONS
*
* This header handles the core computational functionality for our bond
* calculator.
*/
#include <vector>
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
typedef struct Bond {
    std::string pval;
    double c_rate;
    int c_freq;
    int ttm;
    std::string cval;

    friend std::istream &operator>>(std::istream &stream, Bond &b);
    friend std::ostream &operator<<(std::ostream &stream, const Bond b);
} Bond;

typedef struct OverTimeChart {
    int period;
    double cash_flow;
    double disc_fact;
    double pres_val;

    friend std::ostream &operator<<(std::ostream &stream, const Bond b);
} OverTimeChart;

// Calculates the periodic coupon payment using our Bond as an input
Money pcp(const Bond *bond);

double flat_curve_dr(const Bond *bond);

double ytm(const Bond *bond); 

double disc_fact(double ytm, int ppy, int years);

void output_table(std::ostream &stream, std::vector<Bond> bonds);
double macaulay_duration(Bond bond);
double modified_duration(double mac_dur, double yield, int ppy);
Money convexity(Bond bond, double dur);
double calc_spot_rate(Bond bond);
