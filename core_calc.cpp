#include <iostream>
#include <vector>
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
// 0.05 is the initial guess that we pass to the nrm
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

/*
* c_pay: periodic coupon payment
* yield: periodic yield
* mat_val: value of bond at maturity
* n: bond length
* curr_price: current bond price
*/
double macaulay_duration(Bond bond) {
    double df;
    Money mat_val(bond.pval);
    Money c_pay = mat_val * (bond.c_rate/bond.c_freq);
    Money curr_price(bond.cval);
    Money sum;
    for (int i = 1; i <= bond.ttm*bond.c_freq; i++) {
        if (i == bond.ttm*bond.c_freq) {
            c_pay = c_pay + mat_val;
        }
        df = disc_fact(bond.c_rate/bond.c_freq, 1, i);
        sum = sum + (c_pay * i * df);
    }
    return (double)(sum.units) / mat_val.units / bond.c_freq;
}

// Calculate discount rate when the interest rates vary little over time
double flat_curve_dr(const Bond *bond) {
    double yieldtm = ytm(bond);
    return 1.0 / (1.0 + pow(yieldtm/bond->c_rate, bond->c_rate*bond->c_freq));
}

// Adjusted version of Macaulay's
// ppy is the periods per year
double modified_duration(double m_dur, double ytm, int ppy) {
    return m_dur / (1 + ytm/ppy);
}

Money convexity(Bond bond, double dur) {
    Money curr_price(bond.cval);
    Money mat_val(bond.pval);
    Money coup_val = mat_val * bond.c_rate;
    double non_sum_term = 1.0 / (curr_price.getDol() * std::pow(1.0 + bond.c_rate, 2));
    Money sum;
    for (int i = 1; i <= bond.ttm; i++) {
        if (i == bond.ttm) {
            coup_val = (coup_val.units + mat_val.units)/std::pow(1.0+bond.c_rate,i);
        }
        sum = sum + (coup_val.units/std::pow(1.0+bond.c_rate,i) / std::pow(1+bond.c_rate,i))*(i*i + i);
    }
    return sum * non_sum_term;
}

double *interpolate_rates(const double rates[], int n) {
    double *int_rates = new double[n];
     
    return int_rates;
}

// Calculate a discount factor based on a given yield curve
YieldCurveOutput *curve_based_pricing(const double rates[], Bond *bond) {
    double *int_rates = interpolate_rates(rates, bond->ttm*bond->c_freq);
    int n = bond->ttm * bond->c_freq;
    YieldCurveOutput *yco = new YieldCurveOutput[n];
    Money coup_pay = pcp(bond);
    Money total = Money(0);
    for (int t = 0; t < n-1; t++) {
        yco[t].cash_flow = coup_pay;
        yco[t].rate = rates[t];
        yco[t].calc_val = (coup_pay / std::pow(1+rates[t], t));
    }
    
    yco[n-1].rate = rates[n-1];
    yco[n-1].cash_flow = Money(bond->pval) + coup_pay;
    yco[n-1].calc_val = ((Money(bond->pval) + coup_pay) / std::pow(1+rates[n-1], n-1));
    delete int_rates;
    return yco;
}

void output_table(std::ostream &stream, const std::vector<Bond> bonds) {
    char buffer[100];
    for (Bond bond : bonds) {
        double fval = std::stod(bond.pval);
        stream << "Period | Cash Flow | Discount Factor | Present Value\n";
        stream << "----------------------------------------------------\n";
        Money cash_flow = pcp(&bond);
        double flow = cash_flow.getDol();

        double yield = ytm(&bond);
        
        double fut_val = 0.0, adj_val = 0.0;
        double df;
        for (int i=1; i < bond.ttm * bond.c_freq; i++) {
            fut_val += flow;
            df = disc_fact(yield, bond.c_freq, i);
            adj_val += flow * df;
            sprintf(buffer, "%-7d|%-11.2f|%-17f|%0.2f\n", i, flow, df, flow * df);
            stream << buffer;
        }

        fut_val += flow + fval;
        df = disc_fact(yield, bond.c_freq, bond.ttm * bond.c_freq);
        adj_val += (flow + fval) * df;
        sprintf(buffer, "%-7d|%-11.2f|%-17f|%0.2f\n", bond.ttm * bond.c_freq, flow+fval, 
                df, (flow + fval) * df);
        double mac_dur = macaulay_duration(bond);
        stream << buffer;
        stream << "----------------------------------------------------\n";
        stream << "Macaulay Duration: " << mac_dur << "%" << std::endl;
        stream << "Modified Duration: " << modified_duration(mac_dur, yield, bond.c_freq) 
            << "%" << std::endl;
        stream << "Total Future Received Value: " << fut_val + fval << std::endl;
        stream << "Total Adjusted Future Received Value: " 
        << adj_val + (fval * df) << std::endl;
    }
}

// Overloaded inserter operator to output a bond to a stream
std::ostream &operator<<(std::ostream &stream, const Bond b) {
    stream << b.pval << "," << b.cval << "," << b.c_rate<< "," << b.ttm << ","
        << b.c_freq;
    return stream;
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
