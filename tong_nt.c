#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {
    long long N = 1000000000LL;
    int SEG = 1000000;
    int r = (int)sqrt((double)N) + 1;

    /* Bước 1: sàng các số nguyên tố nhỏ đến căn N */
    char *small = calloc(r + 1, 1);          /* 0 = nguyên tố, 1 = hợp số */
    int *primes = malloc((r + 1) * sizeof(int));
    int np = 0;
    for (long long i = 2; i <= r; i++) {
        if (!small[i]) {
            primes[np++] = (int)i;
            for (long long j = i * i; j <= r; j += i) small[j] = 1;
        }
    }

    /* Bước 2: sàng từng đoạn */
    char *seg = malloc(SEG);
    unsigned long long total = 0;
    for (long long low = 0; low < N; low += SEG) {
        long long high = low + SEG;
        if (high > N) high = N;
        memset(seg, 0, SEG);
        if (low == 0) { seg[0] = 1; seg[1] = 1; }
        for (int k = 0; k < np; k++) {
            long long p = primes[k];
            if (p * p >= high) break;
            long long start = ((low + p - 1) / p) * p;
            if (start < p * p) start = p * p;
            for (long long j = start; j < high; j += p) seg[j - low] = 1;
        }
        for (long long i = low; i < high; i++)
            if (!seg[i - low]) total += i;
    }
    printf("%llu\n", total);
    return 0;
}