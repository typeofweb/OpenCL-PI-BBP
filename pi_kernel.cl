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
        sum += (float)(modularPow(16, n - k, partial)) / partial;
        sum -= (int)(sum);
    }

    for (int k = n + 1; k < n + 100; ++k) {
        int partial = (8 * k + coef);
        sum += (pown(16.0f, n - k)) / partial;
        sum -= (int)(sum);
    }

    return sum;
}

__kernel void pi(const int decimalPlaces, __global float* piDigits, __local float* partialSums) {
    const int SUMS_PER_DECIMAl = 4;

    const int local_id = get_local_id(0) + get_group_id(0) * get_local_size(0);
    const int local_size = get_local_size(0);

    piDigits[local_id / SUMS_PER_DECIMAl] = 10.0f;



    for (int i = local_id; i < decimalPlaces * SUMS_PER_DECIMAl; i += local_size) {
        const int whichSum = i % SUMS_PER_DECIMAl;
        const int iteration = i / SUMS_PER_DECIMAl;
        float sum;

        if (whichSum == 0) {
            sum = 4.0f * functionP(1, iteration - 1);
        } else if (whichSum == 1) {
            sum = -2.0f * functionP(4, iteration - 1);
        } else if (whichSum == 2) {
            sum = - functionP(5, iteration - 1);
        } else {
            sum = - functionP(6, iteration - 1);
        }

        partialSums[i] = sum;
    }

    if (local_id % SUMS_PER_DECIMAl == 0) {
        for (int i = local_id; i < decimalPlaces * SUMS_PER_DECIMAl; i += local_size) {
            float s = partialSums[i] + partialSums[i + 1] + partialSums[i + 2] + partialSums[i + 3];
            piDigits[i / SUMS_PER_DECIMAl] = (s - (int)(s) + 1.0f);
        }
    }
}
