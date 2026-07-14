#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct FenwickTree 
{
    int size;
    vector<long long> tree;
    FenwickTree(int n) 
    {
        size = n;
        tree.assign(n + 1, 0);
    }
    void update(int i, long long val) 
    {
        for (; i <= size; i += i & -i) 
        {
            tree[i] = max(tree[i], val);
        }
    }
    long long query(int i) 
    {
        long long res = 0;
        if (i > size) i = size;
        for (; i > 0; i -= i & -i) 
        {
            res = max(res, tree[i]);
        }
        return res;
    }
};
void solve() 
{
    int n;
    cin >> n;    
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) 
    {
        cin >> a[i];
    }
    vector<vector<int>> active_at(n + 2);
    vector<long long> dp(n + 1, 0);
    FenwickTree bit(n);
    long long max_total_weight = 0;
    for (int i = 1; i <= n; i++) 
    {
        for (int j : active_at[i]) 
        {
            bit.update(j, dp[j]);
        }
        long long limit = i - a[i] - 1;
        long long max_prev = 0;
        if (limit >= 1) 
        {
            max_prev = bit.query(limit);
        }
        dp[i] = a[i] + max_prev;
        max_total_weight = max(max_total_weight, dp[i]);
        long long activation_time = i + a[i] + 1;
        if (activation_time <= n) 
        {
            active_at[activation_time].push_back(i);
        }
    }
    cout << max_total_weight << "\n";
}
int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) 
    {
        solve();
    }
    return 0;
}