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
    
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Cannot open file.\n";
        return 1;
    }

    std::ofstream out("out.txt");
    if (!out) {
        std::cerr << "Cannot open output file.\n";
        return 1;
    }

    std::vector<Bond> bonds(0);
    
    Bond b;
    int i = 0;
    while (in >> b) {
        bonds.push_back(b);
        i++;
    }
    
    
    output_table(out, bonds);
    double mac_dur = macaulay_duration(bonds.at(0));
    convexity(bonds.at(0), mac_dur);
    in.close();
    out.close();

    std::cout << "Output to: out.txt" << std::endl; 
}
