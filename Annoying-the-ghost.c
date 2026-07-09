#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void solve() 
{
    int n;
    if (scanf("%d", &n) != 1) return;
    long long *a = (long long *)malloc(n * sizeof(long long));
    long long *b = (long long *)malloc(n * sizeof(long long));
    int *p = (int *)malloc(n * sizeof(int));
    int *used = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) 
    {
        scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n; i++) 
    {
        scanf("%lld", &b[i]);
    }
    int possible = 1;
    for (int j = 0; j < n; j++) 
    {
        int matched_idx = -1;
        for (int i = 0; i < n; i++) 
        {
            if (!used[i] && a[i] <= b[j]) 
            {
                matched_idx = i;
                break;
            }
        }
        if (matched_idx == -1) 
        {
            possible = 0;
            break;
        }
        used[matched_idx] = 1;
        p[matched_idx] = j;
    }
    if (!possible) 
    {
        printf("-1\n");
    } 
    else 
    {
        long long inversions = 0;
        for (int i = 0; i < n; i++) 
        {
            for (int k = i + 1; k < n; k++) 
            {
                if (p[i] > p[k]) 
                {
                    inversions++;
                }
            }
        }
        printf("%lld\n", inversions);
    }
    free(a);
    free(b);
    free(p);
    free(used);
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