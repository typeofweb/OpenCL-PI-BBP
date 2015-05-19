//
// Created by Michal Miszczyszyn on 19/05/15.
//

#ifndef PI2_PI2_HPP
#define PI2_PI2_HPP

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

    for (int k = n + 1; k < n + 100; ++k) {
        int partial = (8 * k + coef);
        sum += (std::pow(16.0f, n - k)) / partial;
        sum -= static_cast<int>(sum);
    }

    return sum;
}

float bbpAlgorithm(int n) {
    n -= 1;
    float sum = 4.0f * functionP(1, n) - 2.0f * functionP(4, n) - functionP(5, n) - functionP(6, n);
    return sum - static_cast<int>(sum) + 1.0f;
}

char hexFromFloat (float x) {
    int i;
    double y;
    char hx[] = "0123456789ABCDEF";

    y = std::abs(x);
    y = 16.0f * (y - std::floor(y));
    return hx[static_cast<int>(y)];
}

#endif //PI2_PI2_HPP
