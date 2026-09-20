#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;

void solve() {
    int a, b; cin >> a >> b;
    cout << a << '\n';
    cout << b << '\n';
    cout << a + b << '\n';
    cout << a * b << '\n';
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}
