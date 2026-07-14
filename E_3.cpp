#include <iostream>
#include <vector>
#include <string>
using namespace std;
void solve() 
{
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<int> pref(n + 1, 0);
    for (int i = 1; i < n; i++) 
    {
        pref[i + 1] = pref[i];
        if (s[i] == s[i - 1]) 
        {
            pref[i + 1]++;
        }
    }
    while (q--) 
    {
        int l, r, k;
        cin >> l >> r >> k;
        int C = pref[r] - pref[l];
        int min_operations = (C + 1) / 2;
        if (min_operations <= k) 
        {
            cout << "YES\n";
        }
        else 
        {
            cout << "NO\n";
        }
    }
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