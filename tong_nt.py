import math
from itertools import compress

N = 1_000_000_000      # tính tổng các số nguyên tố < N
SEG = 1_000_000        # kích thước mỗi đoạn

# Bước 1: sàng các số nguyên tố nhỏ đến căn N
r = math.isqrt(N) + 1
small = bytearray([1]) * (r + 1)
small[0] = small[1] = 0
for i in range(2, math.isqrt(r) + 1):
    if small[i]:
        small[i*i::i] = bytearray(len(range(i*i, r + 1, i)))
primes = [i for i in range(2, r + 1) if small[i]]

# Bước 2: sàng từng đoạn
total = 0
for low in range(0, N, SEG):
    high = min(low + SEG, N)
    seg = bytearray([1]) * (high - low)
    if low == 0:
        seg[0] = 0
        seg[1] = 0
    for p in primes:
        if p * p >= high:
            break
        start = max(p * p, ((low + p - 1) // p) * p)
        seg[start - low::p] = bytearray(len(range(start - low, high - low, p)))
    total += sum(compress(range(low, high), seg))

print(total)