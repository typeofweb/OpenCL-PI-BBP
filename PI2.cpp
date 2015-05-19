#include <iostream>
#include <cmath>
#include "PI2.hpp"

int main () {
    const int LENGTH = 100;

    char pi[LENGTH];
    for (int i = 1; i < LENGTH + 1; ++i) {
       pi[i-1] =  hexFromFloat(bbpAlgorithm(i));
    }

    std::cout << "3.";
    for (auto &&i : pi) {
        std::cout << i;
    }
    std::cout << std::endl;


    float pi_dec = 3.0f;
    for (int i = LENGTH - 1; i >= 0; --i) {
        char h = pi[i];
        int v;
        if (h >= '0' && h <= '9') {
            v = h - '0';
        } else if (h >= 'A' && h <= 'F') {
            v = h - 'A' + 10;
        } else {
            continue;
        }

        pi_dec += std::pow(16.0f, -(i + 1)) * static_cast<float>(v);
    }
    std::cout.precision(LENGTH);
    std::cout << pi_dec << std::endl;
    return 0;
}
