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

    for (Bond elem : bonds) {
        std::cout << elem << std::endl;
    }
    file.close();
}
