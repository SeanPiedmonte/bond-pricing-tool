#include "Money.h"

Money::Money() : units{0} {
}

Money::Money(const Money &money) 
    : units{ money.units }
{
}

Money::Money(const Money &&money)
    : units{ money.units }
{
}

Money::Money(long long units)
    : units { units }
{
}

Money::Money(std::string u)
{
    std::string delimeter = ".";
    std::string dollars = u.substr(0, u.find(delimeter));
    u.erase(0, u.find(delimeter) + delimeter.length());
    std::string cents = u;
    units = std::stoi(dollars) * 1000000 + std::stoi(cents) * 10000;
}

Money::~Money() {
}

void Money::mult_per(double per) {
    units = units * per;
}

void Money::div_per(double per) {
    units = units / per;
}

void Money::show_units() {
    std::cout << this->units;
}

double Money::getDol() {
    return units / 1000000.0;
}

std::ostream& operator<<(std::ostream& out, const Money& money) {
    out << (double) (money.units / 1000000.0);
    return out;    
}
