#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void solve() 
{
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) 
    {
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; i++) 
    {
        cin >> b[i];
    }
    sort(b.begin(), b.end());
    long long total_productivity = 0;
    int current_index = 0;
    for (int j = 0; j < m; j++) 
    {
        int block_end = b[j];
        
        long long sum_normal = 0;
        while (current_index < block_end) 
        {
            sum_normal += a[current_index];
            current_index++;
        }
        long long sum_flipped = -sum_normal;
        total_productivity += max(sum_normal, sum_flipped);
    }
    while (current_index < n) 
    {
        total_productivity += a[current_index];
        current_index++;
    }
    cout << total_productivity << "\n";
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