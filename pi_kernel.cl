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

__kernel void pi(const int from, const int decimalPlaces, __global float* piDigits) {
    const int local_id = get_local_id(0) + get_group_id(0) * get_local_size(0);
    const int local_size = get_local_size(0);

    for (int i = local_id; i < decimalPlaces; i += local_size) {
        const int decimalPlace = from + i - 1;
        float sum = 4.0f * functionP(1, decimalPlace) - 2.0f * functionP(4, decimalPlace) - functionP(5, decimalPlace) - functionP(6, decimalPlace);

        piDigits[i] = sum - (int)sum + 1.0f;
    }
    //barrier(CLK_GLOBAL_MEM_FENCE);
}
