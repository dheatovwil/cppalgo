//
// Created by tgtay on 4/23/2019.
//

#include <iostream>
#include <cstring>

using namespace std;

// swap macro from https://stackoverflow.com/questions/3982348/implement-generic-swap-macro-in-c#3982430
#define swap(x,y) do { \
    unsigned char swap_tmp[sizeof(x) == sizeof(y) ?  (signed)sizeof(x) : -1]; \
    memcpy(swap_tmp, &y, sizeof(x)); \
    memcpy(&y, &x, sizeof(x)); \
    memcpy(&x, swap_tmp, sizeof(x)); \
    } while(0)

#define max(x,y) x>y?x:y
#define hLeft(i) i<<1
#define hRight(i) (hLeft(i)) + 1


void hMaxHeapify(int* A, int *data[3], unsigned i) {
    int l = hLeft(i);
    int r = hRight(i);
    int largest = i;
    if (l <= A[0] && data[l][2] > data[i][2])
        largest = l;
    if (r <= A[0] && data[r][2] > data[largest][2])
        largest = r;
    if (largest != i) {
        swap(A[i], A[largest]);
        hMaxHeapify(A, data, largest);
    }
}

void hMaxHeapSort(int *A, int **data) {
    // input A needed to be padded right
    for (unsigned int i = (A[0] >> 1); i >= 1; i--)
        hMaxHeapify(A, data, i);

    for (unsigned int i = A[0]; i >= 2; i--) {
        swap(A[1], A[i]);
        A[0]--;
        hMaxHeapify(A, data, 1);
    }
}

int main() {
    /*
     * input format:
     * {n}
     * {s_i, f_i, w_i}
     *  ...
     * {s_n, f_n, w_n}
     */

    int n;
    cin >> n;
    int *data[3];
    for (int i = 0; i < n; i++) {
        // 0- s_i, 1- f_i, 2- w_i
        int *tmp = new int[3];
        cin >> tmp[0] >> tmp[1] >> tmp[2];
        data[i] = tmp;
    }

    // solve, using dp approach from https://farazdagi.com/2013/weighted-interval-scheduling/

    // step 1 : sort
    // right pad by 1, store heap size at 0
    int sdi[n+1];
    for (int i = 0; i < n; i++)
        sdi[i+1] = i;
    sdi[0] = n;
    hMaxHeapSort(sdi, data);

    // step 2 : find p(i) -: rightmost compatible to the left of i, using bin-search
    int p[n];
    p[0] = 0;
    for (int i = 1; i <= n; i++) {
        unsigned lo = 0;
        unsigned hi = i;
        while (lo < hi) {
            int mid = lo + (hi >> 1);
            if (data[sdi[mid + 1]][1] > data[sdi[i + 1]][0]) // if f_mid > s_i
                hi = mid - 1;
            else // if f_mid <= s_i
                lo = mid;
        }
        p[i] = lo;
    }

    // step 3 : dp
    int OPT[n];
    for (int i = 0; i < n; i++)
        OPT[i] = max(data[sdi[i+1]][2] + OPT[p[sdi[i]]], OPT[i-1]);

    // step 4: backtrack
    int ans[n+1];
    ans[0] = 1;
    int i = n;
    while (i >= 0) {
        if (data[sdi[i+1]][2] + OPT[p[sdi[i+1]]] > OPT[i-1]) {
            ans[ans[0]] = sdi[i+1];
            ans[0]++;
            i = p[sdi[i+1]]; // jump
        }
        i--;
    }

}

