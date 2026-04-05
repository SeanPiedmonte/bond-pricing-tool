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
    double c_rate;
    int c_freq;
    int ttm;
    std::string pval;
    std::string cval;

    friend std::istream &operator>>(std::istream &stream, Bond &b);
    friend std::ostream &operator<<(std::ostream &stream, const Bond b);
} Bond;

// Allows for printing of values for display
typedef struct OverTimeChart {
    double cash_flow;
    double disc_fact;
    double pres_val;
    int period;

    friend std::ostream &operator<<(std::ostream &stream, const Bond b);
} OverTimeChart;

typedef struct YieldCurveOutput {
    double rate;
    int period;
    Money calc_val;
    Money cash_flow; 
} YieldCurveOutput;

typedef struct Rate {
    double rate;
    int year;
} Rate;

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
void mult_years_inter(Rate rates[], Rate rate1, Rate rate2, int start, int end);
const Rate *interpolate_rates(const Rate rates[], int num_rates, int n, int freq);
