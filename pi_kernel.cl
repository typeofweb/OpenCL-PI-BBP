void reduce(
     __local double* local_sums,
     __global double* partial_sums
) {
     int local_size = get_local_size(0);
     int local_id = get_local_id(0);
     int group_id = get_group_id(0);

     double sum;
     int i;

     if (local_id == 0) {
          sum = 0.0f;

          for (i = 0; i < local_size; ++i) {
                sum += local_sums[i];
          }

          partial_sums[group_id] = sum;
     }
}

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

__kernel void pi(const int whichDigit, __global double* piDigits) {
    int whichSum = get_local_id(0);

    float sum;

    if (whichSum == 0) {
        sum = 4.0f * functionP(1, whichDigit - 1);
    } else if (whichSum == 1) {
        sum = -2.0f * functionP(4, whichDigit - 1);
    } else if (whichSum == 2) {
        sum = - functionP(5, whichDigit - 1);
    } else {
        sum = - functionP(6, whichDigit - 1);
    }

    piDigits[whichSum] = (sum - (int)(sum) + 1.0f);
    barrier(CLK_LOCAL_MEM_FENCE);
}
