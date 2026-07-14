#include <iostream>
using namespace std;
int get_gcd(int a, int b) 
{
    while (b != 0) 
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
void solve() 
{
    int n, x, y;
    cin >> n >> x >> y;
    int g = get_gcd(x, y);
    bool possible = true;
    for (int i = 1; i <= n; ++i) 
    {
        int val;
        cin >> val;
        if (i % g != val % g) 
        {
            possible = false;
        }
    }
    if (possible) 
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
    cin >> t;
    while (t--) 
    {
        solve();
    }
    return 0;
}