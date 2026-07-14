#include <iostream>
using namespace std;
void solve() 
{
    int n;
    cin >> n;
    long long excess = 0;
    bool possible = true;
    for (int i = 1; i <= n; i++) 
    {
        long long a;
        cin >> a;
        long long current_books = a + excess;
        if (current_books < i) 
        {
            possible = false;
        } 
        else 
        {
            excess = current_books - i;
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