#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
void solve() 
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ml = 0;
    int cl = 0;
    for (int i = 0; i < n; i++) 
    {
        if (s[i] == '#') 
        {
            cl++;
        } 
        else 
        {
            if (cl > ml) 
            {
                ml = cl;
            }
            cl = 0;
        }
    }
    if (cl > ml) 
    {
        ml = cl;
    }
    int max_time = (ml + 1) / 2;   
    cout << max_time << "\n";
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