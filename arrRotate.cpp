#include <bits/stdc++.h>
#include <cstring>

/*
 * Array rotation question from HackerRank: https://www.hackerrank.com/challenges/ctci-array-left-rotation/problem
 */

using namespace std;

void rotLeft(int *a, int d, unsigned int n, int *result) {
    int bigArr[n << 1];
    int size = n*sizeof(int);
    memcpy(bigArr, a, size);
    memcpy(&bigArr[n], a, size);
    memcpy(result,&bigArr[d%n],size);
}

int main()
{
    ofstream f_out(getenv("OUTPUT_PATH"));

    unsigned int n, d;
    cin >> n >> d;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int b[n];
    rotLeft(a,d,n,b);

    for (int i = 0; i <n; i++) {
        f_out << b[i];

        if (i != n - 1) {
            f_out << " ";
        }
    }

    f_out << "\n";

    f_out.close();

    return 0;
}
