typedef unsigned long long ULL;
typedef pair<ULL,ULL> UINT128;
// __int128_t mul(ULL a, ULL b) { return a * __int128_t(b); }
UINT128 mul(ULL a, ULL b) {
  ULL M = (1ULL<<32);
  ULL a1 = a>>32, a0 = a%M, b1 = b>>32, b0 = b%M;
  ULL hi = a1 * b1, lo = a0 * b0;
  a0 *= b1, b0 *= a1;
  hi += (a0>>32) + (b0>>32);
  a0<<=32, b0 <<= 32;
  if (a0 + lo < lo) ++hi; lo += a0;
  if (b0 + lo < lo) ++hi; lo += b0;
  return UINT128(hi, lo);
}
