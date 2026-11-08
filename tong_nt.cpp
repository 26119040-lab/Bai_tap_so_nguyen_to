#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

int main() {
    const long long N = 1000000000LL;
    const int SEG = 1000000;
    int r = (int)sqrt((double)N) + 1;

    // Buoc 1: sang cac so nguyen to nho den can N
    vector<char> small(r + 1, 0);          // 0 = nguyen to, 1 = hop so
    vector<int> primes;
    for (long long i = 2; i <= r; i++) {
        if (!small[i]) {
            primes.push_back((int)i);
            for (long long j = i * i; j <= r; j += i) small[j] = 1;
        }
    }

    // Buoc 2: sang tung doan
    vector<char> seg(SEG);
    unsigned long long total = 0;
    for (long long low = 0; low < N; low += SEG) {
        long long high = (low + SEG > N) ? N : low + SEG;
        memset(seg.data(), 0, SEG);
        if (low == 0) { seg[0] = 1; seg[1] = 1; }
        for (size_t k = 0; k < primes.size(); k++) {
            long long p = primes[k];
            if (p * p >= high) break;
            long long start = ((low + p - 1) / p) * p;
            if (start < p * p) start = p * p;
            for (long long j = start; j < high; j += p) seg[j - low] = 1;
        }
        for (long long i = low; i < high; i++)
            if (!seg[i - low]) total += i;
    }
    cout << total << endl;
    return 0;
}