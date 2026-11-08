program TongSoNguyenTo;
const
  N   = 1000000000;
  SEG = 1000000;
  R   = 31700;
var
  small : array[0..R] of boolean;
  sieve : array[0..SEG-1] of boolean;
  primes: array[1..4000] of longint;
  np, i : longint;
  p, low, high, start, k, total : int64;
begin
  { Buoc 1: sang cac so nguyen to nho den can N }
  fillchar(small, sizeof(small), false);
  np := 0;
  for i := 2 to R do
    if not small[i] then begin
      inc(np);
      primes[np] := i;
      k := i; k := k * i;
      while k <= R do begin
        small[k] := true;
        k := k + i;
      end;
    end;

  { Buoc 2: sang tung doan }
  total := 0;
  low := 0;
  while low < N do begin
    high := low + SEG;
    if high > N then high := N;
    fillchar(sieve, sizeof(sieve), false);   { false = nguyen to }
    if low = 0 then begin sieve[0] := true; sieve[1] := true; end;
    for i := 1 to np do begin
      p := primes[i];
      if p * p >= high then break;
      start := ((low + p - 1) div p) * p;
      if start < p * p then start := p * p;
      k := start;
      while k < high do begin
        sieve[k - low] := true;
        k := k + p;
      end;
    end;
    for i := 0 to high - low - 1 do
      if not sieve[i] then total := total + low + i;
    low := low + SEG;
  end;
  writeln(total);
end.