//
// Created by Michal Miszczyszyn on 19/05/15.
//

#ifndef PI2_PI2_HPP
#define PI2_PI2_HPP

#include <cmath>

unsigned int modularPow(int base, int exponent, int modulus) {
    unsigned int c = 1;
    for (unsigned int e = 0; e < exponent; ++e) {
        c = (c * base) % modulus;
    }
    return c;
}

float functionP(const int coef, const int n) {
    float sum = 0.0f;

    for (int k = 0; k <= n; ++k) {
        int partial = (8 * k + coef);
        sum += static_cast<float>(modularPow(16, n - k, partial)) / partial;
        sum -= static_cast<int>(sum);
    }

    /*for (int k = n + 1; k < n + 100; ++k) {
        int partial = (8 * k + coef);
        sum += (std::pow(16.0f, n - k)) / partial;
        sum -= static_cast<int>(sum);
    }*/

    return sum;
}

float bbpAlgorithm(int n) {
    n -= 1;
    float s1, s2, s3, s4;
    s1 = functionP(1, n);
    s2 = functionP(4, n);
    s3 = functionP(5, n);
    s4 = functionP(6, n);
    float sum = 4.0f * s1 - 2.0f * s2 - s3 - s4;
    return sum - static_cast<int>(sum) + 1.0f;
}

unsigned decIntFromHexFloat(float x) {
    float y;
    y = std::abs(x);
    y = 16.0f * (y - std::floor(y));
    return static_cast<unsigned>(y);
}

char hexFromFloat (float x) {
    char hx[] = "0123456789ABCDEF";
    return hx[decIntFromHexFloat(x)];
}

#endif //PI2_PI2_HPP
