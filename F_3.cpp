#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 1e9;
int n;
vector<vector<int>> adj;
vector<int> a;
vector<int> min_val, max_val, leaf_count;
vector<bool> is_valid;
void dfs(int u) 
{
    if (adj[u].empty()) 
    {
        min_val[u] = a[u];
        max_val[u] = a[u];
        leaf_count[u] = 1;
        is_valid[u] = true;
        return;
    }
    int current_min = INF;
    int current_max = -INF;
    int current_count = 0;
    bool children_valid = true;
    for (int v : adj[u]) 
    {
        dfs(v);
        if (!is_valid[v]) 
        {
            children_valid = false;
        }
        current_min = min(current_min, min_val[v]);
        current_max = max(current_max, max_val[v]);
        current_count += leaf_count[v];
    }
    if (!children_valid) 
    {
        is_valid[u] = false;
        return;
    }
    if (current_max - current_min + 1 != current_count) 
    {
        is_valid[u] = false;
        return;
    }
    int m = adj[u].size();
    int pos = 0;
    int smallest_min = INF;
    for (int i = 0; i < m; ++i) 
    {
        int v = adj[u][i];
        if (min_val[v] < smallest_min) 
        {
            smallest_min = min_val[v];
            pos = i;
        }
    }
    bool cyclically_sorted = true;
    for (int k = 1; k < m; ++k) 
    {
        int prev_v = adj[u][(pos + k - 1) % m];
        int curr_v = adj[u][(pos + k) % m];
        if (max_val[prev_v] + 1 != min_val[curr_v]) 
        {
            cyclically_sorted = false;
            break;
        }
    }
    if (cyclically_sorted) 
    {
        min_val[u] = current_min;
        max_val[u] = current_max;
        leaf_count[u] = current_count;
        is_valid[u] = true;
    } 
    else 
    {
        is_valid[u] = false;
    }
}
void solve() 
{
    cin >> n;
    adj.assign(n + 1, vector<int>());
    for (int i = 2; i <= n; ++i) 
    {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }
    a.resize(n + 1);
    for (int i = 1; i <= n; ++i) 
    {
        cin >> a[i];
    }
    min_val.assign(n + 1, INF);
    max_val.assign(n + 1, -INF);
    leaf_count.assign(n + 1, 0);
    is_valid.assign(n + 1, false);
    dfs(1);
    if (is_valid[1]) 
    {
        cout << "YES\n";
    } 
    else 
    {
        cout << "NO\n";
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