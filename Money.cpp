#include "Money.h"

Money::Money(const Money &money) 
    : units{ money.units }
{
}

Money::Money(const Money &&money)
    : units{ money.units }
{
}

Money::Money(long long units)
    : units{ units * 100000} // transform into our 6 digits of precision
{
}

Money::~Money() {
}

void Money::mult_per(double per) {
    units = units * (per/100.0);
}

void Money::div_per(double per) {
    units = units / per;
}

void Money::set_units(long long u) {
    units = u;
}

long long Money::get_units() {
    return units;
}

std::ostream& operator<<(std::ostream& out, const Money& money) {
    out << money.units;
    return out;    
}
