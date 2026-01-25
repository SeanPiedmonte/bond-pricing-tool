#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <cmath>
#include "core_calc.h"
#include "Money.h"
  
int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid Number of arguments" << std::endl;
        return 1;
    }
    
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Cannot open file.\n";
        return 1;
    }

    std::vector<Bond> bonds(0);
    
    Bond b;
    int i = 0;
    while (file >> b) {
        bonds.push_back(b);
        i++;
    }

    for (Bond bond : bonds) {
        Money pval(bond.pval);
        Money cval(bond.cval);
        std::cout << "Present Value: " << pval << std::endl;
        std::cout << "Current Value: " << cval << std::endl;
        std::cout << bond << std::endl;

        Money money = pcp(&bond);
        money.show_units();
        std::cout << std::endl;
        std::cout << "Money: " << money << std::endl;

        double yield = ytm(&bond);
        std::cout << "Yield to maturity: " << yield << std::endl;

        double df = disc_fact(yield, bond.c_freq, bond.ttm);
        std::cout << "Discount Factor: " << df << std::endl;
    }

    
    file.close();
}
