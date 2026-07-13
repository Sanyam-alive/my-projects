#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void solve() 
{
    long long a, b, x;
    cin >> a >> b >> x;
    vector<long long> A;
    long long current_a = a;
    A.push_back(current_a);
    while (current_a > 0) 
    {
        current_a /= x;
        A.push_back(current_a);
    }
    vector<long long> B;
    long long current_b = b;
    B.push_back(current_b);
    while (current_b > 0) 
    {
        current_b /= x;
        B.push_back(current_b);
    }
    long long min_ops = 2000000000; 
    for (int i = 0; i < A.size(); i++) 
    {
        for (int j = 0; j < B.size(); j++) 
        {
            long long a_prime = A[i];
            long long b_prime = B[j];
            long long additions = (a_prime > b_prime) ? (a_prime - b_prime) : (b_prime - a_prime);
            long long total_ops = i + j + additions;       
            if (total_ops < min_ops) 
            {
                min_ops = total_ops;
            }
        }
    }
    cout << min_ops << "\n";
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