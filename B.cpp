#include <iostream>
#include <vector>
using namespace std;
void solve() 
{
    int n;
    cin >> n;
    if (n == 1) 
    {
        cout << 1 << "\n";
        return;
    }
    if (n == 2) 
    {
        cout << -1 << "\n"; 
        return;
    }
    vector<long long> a(n);
    a[0] = 1;
    a[1] = 2;
    long long p = 1;
    for (int i = 2; i < n; ++i) 
    {
        a[i] = 3 * p;
        p *= 2;
    }
    for (int i = n - 1; i >= 0; --i) 
    {
        cout << a[i] << " ";
    }
    cout << "\n";
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