#include <iostream>
#include <cassert>
#include <vector>
#include "core_calc.h"
#include "Money.h"
  
int main(int argc, char *argv[]) {
    if (argc != 6) {
        std::cerr << "Invalid Number of arguments" << std::endl;
        return 1;
    }
    
    std::vector<std::string> args(argv, argv+argc);
    Bond bond;
    try {
        bond.pval = std::stod(args.at(1));
        bond.c_rate = std::stod(args.at(2)) / 100.0; 
        bond.c_freq = std::stoi(args.at(3));
        bond.ttm = std::stoi(args.at(4));
        bond.ytm = std::stod(args.at(5)) / 100.0;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid Number in arguments" << std::endl;
    }
    
    Money money = pcp(&bond);
    double dr = flat_curve_dr(&bond);
    std::cout << money << ", " << dr << std::endl;
}
