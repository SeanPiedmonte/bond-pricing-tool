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
    : units { units }
{
}

Money::Money(std::string u)
{
    std::string delimeter = ".";
    std::string dollars = u.substr(0, u.find(delimeter));
    u.erase(0, u.find(delimeter) + delimeter.length());
    std::string cents = u;
    std::cout << "string: " << dollars << "." << cents << std::endl;
    std::cout << "conversion: " << std::stoi(dollars) * 1000000 + std::stoi(cents) * 10000 << std::endl;
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
