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
    long long comp = fv/std::pow(r2+1, 20) + ppp * ((1 - 1/std::pow(r2+1, 20))/r2);
    
    if (std::abs(comp - cv) > 10000) {
        return nrm(fv, cv, r2, ppp);
    } 
    return r2;
}

// Yield to maturity
double ytm(const Bond *bond) {
    Money pval(bond->pval);
    Money cval(bond->cval);
    long long c_pay = pval.units * bond->c_rate / bond->c_freq;
    double nrm_val = nrm(pval.units, cval.units, 0.05, c_pay);
    return nrm_val * bond->c_freq;
}

// Discount Factor calculation
double disc_fact(double ytm, int c_freq, int years) {
    int ppy = c_freq * years;
    return (1.0 / std::pow(1+(ytm/c_freq), ppy));
}

// Calculate discount rate when the interest rates vary little over time
double flat_curve_dr(const Bond *bond) {
    double yieldtm = ytm(bond);
    return 1.0 / (1.0 + pow(yieldtm/bond->c_rate, bond->c_rate*bond->c_freq));
}

// Overload the extractor operator so that we can take in a bond from a file
std::istream &operator>>(std::istream &stream, Bond &b) {
    char pval[50];
    char cval[50];
    char c_rate[50];
    char c_freq[50];
    char ttm[50];
    
    if (!stream.getline(pval, 50, ',')) {
        b.pval = "0";
    } else {
        b.pval = pval;
    }
    if (!stream.getline(cval, 50, ',')) {
        b.cval = "0";
    } else {
        b.cval = cval;
    }
    if (!stream.getline(c_rate, 50, ',')) {
        b.c_rate = 0.0;
    } else {
        b.c_rate = std::atof(c_rate);
    }
    if (!stream.getline(ttm, 50, ',')) {
        b.ttm = 0;
    } else {
        b.ttm= std::atoi(ttm);
    }
    if (!stream.getline(c_freq, 50, '\n')) {
        b.c_freq = 0;
    } else {
        b.c_freq = std::atoi(c_freq);
    }

    return stream;
}

// Overloaded inserter operator to output a bond to a stream
std::ostream &operator<<(std::ostream &stream, const Bond b) {
    stream << b.pval << "," << b.cval << "," << b.c_rate<< "," << b.ttm << ","
        << b.c_freq;
    return stream;
}
