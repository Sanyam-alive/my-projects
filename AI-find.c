#include <stdio.h>
long long power(long long base, long long exp) 
{
    long long res = 1;
    base %= 998244353;
    while (exp > 0) 
    {
        if (exp % 2 == 1) 
        {
            res = (res * base) % 998244353;
        }
        base = (base * base) % 998244353;
        exp /= 2;
    }
    return res;
}
int main()
{
    long long t, y;
    if (scanf("%lld", &t) != 1) return 0;
    for (y = 0; y < t; y++)
    {
        long long n, m, r, c;
        if (scanf("%lld %lld %lld %lld", &n, &m, &r, &c) != 4) break;
        long long dim = (n * (c - 1)) + (m * (r - 1)) - ((r - 1) * (c - 1));
        long long ans = power(2, dim);
        printf("%lld\n", ans);
    }
    return 0;
}