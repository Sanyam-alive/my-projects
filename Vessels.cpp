#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void solve() 
{
    int n;
    if (!(cin >> n)) return;
    vector<long long> h(n);
    vector<long long> h_double(2 * n);
    for (int i = 0; i < n; i++) 
    {
        cin >> h[i];
        h_double[i] = h[i];
        h_double[i + n] = h[i];
    }
    vector<long long> left_max(2 * n, 0);
    vector<long long> right_max(2 * n, 0);
    vector<long long> ans(n, 0);
    for (int l = 0; l < n; l++) 
    {
        left_max[l + 1] = h_double[l];
        for (int k = l + 2; k < l + n; k++) 
        {
            left_max[k] = max(left_max[k - 1], h_double[k - 1]);
        }
        right_max[l + n - 1] = h_double[l + n - 1];
        for (int k = l + n - 2; k >= l + 1; k--) 
        {
            right_max[k] = max(right_max[k + 1], h_double[k]);
        }
        long long current_sum = 0;
        for (int k = l + 1; k < l + n; k++) 
        {
            current_sum += min(left_max[k], right_max[k]);
        }
        ans[l] = current_sum;
    }
    for (int i = 0; i < n; i++) 
    {
        cout << ans[i] << (i == n - 1 ? '\n' : ' ');
    }
}
int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) 
    {
        while (t--) 
        {
            solve();
        }
    }
    return 0;
}