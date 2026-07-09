#include <stdio.h>
#include <stdlib.h>
#define MAXN 3005
long long max_ll(long long a, long long b) 
{
    return (a > b) ? a : b;
}
long long min_ll(long long a, long long b) 
{
    return (a < b) ? a : b;
}
void solve()
{
    int n;
    if (scanf("%d", &n) != 1) return;
    long long h[MAXN];
    long long h_double[2 * MAXN];
    for (int i = 0; i < n; i++) 
    {
        scanf("%lld", &h[i]);
        h_double[i] = h[i];
        h_double[i + n] = h[i];
    }
    long long left_max[2 * MAXN];
    long long right_max[2 * MAXN];
    long long ans[MAXN];
    for (int l = 0; l < n; l++) 
    {
        left_max[l + 1] = h_double[l];
        for (int k = l + 2; k < l + n; k++) 
        {
            left_max[k] = max_ll(left_max[k - 1], h_double[k - 1]);
        }
        right_max[l + n - 1] = h_double[l + n - 1];
        for (int k = l + n - 2; k >= l + 1; k--) 
        {
            right_max[k] = max_ll(right_max[k + 1], h_double[k]);
        }
        long long current_sum = 0;
        for (int k = l + 1; k < l + n; k++) 
        {
            current_sum += min_ll(left_max[k], right_max[k]);
        }
        ans[l] = current_sum;
    }
    for (int i = 0; i < n; i++) 
    {
        printf("%lld%c", ans[i], (i == n - 1) ? '\n' : ' ');
    }
}
int main() 
{
    int t;
    if (scanf("%d", &t) == 1) 
    {
        while (t--) 
        {
            solve();
        }
    }
    return 0;
}