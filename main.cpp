#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <cmath>
#include "core_calc.h"
#include "Money.h"
  
int main(int argc, char *argv[]) {
    /*if (argc != 2) {
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
    }*/
    
    int num_rates = 5;
    double *rates = new double[]{
        0.0, 
        1.0,
        2.0,
        3.0,
        4.0, 
        5.0,
    };

    int freq = 3;
    int n = num_rates * freq;
    const double *int_rates = interpolate_rates(rates, num_rates, n, freq);
    for (int i = 0; i < n; i++) {
        std::cout << int_rates[i] << ": " << int_rates[i] << std::endl;
    }

    /*output_table(out, bonds);
    double mac_dur = macaulay_duration(bonds.at(0));
    convexity(bonds.at(0), mac_dur);
    in.close();
    out.close();*/

    //std::cout << "Output to: out.txt" << std::endl; 
}
