//
// Created by tgtay on 4/23/2019.
//


#include <iostream>
#include <cstring>

#define ull uint32_t

using namespace std;

void matrix_multi(const ull *m, const ull *n, ull *out) {
    out[0] = m[0]*n[0] + m[1]*n[2];
    out[1] = m[0]*n[1] + m[1]*n[3];
    out[2] = m[2]*n[0] + m[3]*n[2];
    out[3] = m[2]*n[1] + m[3]*n[3];
}

void m_copy(ull *destination, const ull *src) {
    destination[0] = src[0];
    destination[1] = src[1];
    destination[2] = src[2];
    destination[3] = src[3];
}

int main() {


    uint32_t n;  // n-th fib to be calculated
    cin >> n;

    n--;
    // observation: cygwin64 clz only works on uint32_t
    unsigned hi = 32 - __builtin_clz(n) - 1; // find the pos of first significant bit
    unsigned lo = __builtin_ctz(n); // find the pos of last significant bit

    ull base[4] = { 1, 1, 1, 0 }; // Donald E.Knuth's identity matrix

    ull memo[hi][4];
    // memo[0] always hold the first power of matrix, manual assignment for optimization

    m_copy(memo[0], base);
    // compute up to 2^hi using memoization
    for (unsigned i=1; i <= hi; ++i)
        matrix_multi(memo[i-1],memo[i-1],memo[i]);

    ull matrix[4];
    m_copy(matrix, memo[lo]);
    for (unsigned i=lo+1u; i<= hi;i++)
        // multiply with if bit is 1
        if ((n >> i) & 1u) {
            ull temp[4];
            matrix_multi(matrix, memo[i], temp);
            m_copy(matrix, temp);
        }

    cout << matrix[0] << endl;
}