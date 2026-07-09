#include <stdio.h>
long long a[200005];
int main() 
{
    long long t, y;
    if (scanf("%lld", &t) != 1) return 0;
    for (y = 0; y < t; y++) 
    {
        long long n;
        scanf("%lld", &n);
        long long x;
        for (x = 0; x < n; x++) 
        {
            scanf("%lld", &a[x]);
        }
        long long max_val = a[0];
        for (long long i = 1; i < n; i++) 
        {
            if (a[i] >= max_val) 
            {
                max_val = a[i];
            }
            else
            {
                max_val += a[i];
            }
        }
        printf("%lld\n", max_val);
    }
    return 0;
}