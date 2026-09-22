#include <bits/stdc++.h>

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define fi first
#define se second

using namespace std;

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vll = vector<ll>;


void solve() {
    int n;cin >> n;
    int k;cin >> k;
    vector<vector<bool>> grid(n, vector<bool> (n));
    k = n * n - k;
    if (n == 1) {
        if (k == 0) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        cout << "POSSIBLE\n";
        cout << (k ? "." : "#");
        return;
    }
    if (k < n || k >= 2 * n - 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    grid[0][0] = 1;
    grid[n-1][n-1] = 1;
    k -= 2;
    for (int i=1; i<n-1; i++) {
        grid[n-1-i][n-1-i] = 1;
        k--;
    }
    // cout << k << '\n';
    for (int i=1; i<n-1; i++) {
        if (k-- > 0) {
            grid[i][n-1] = 1;
            grid[i][i] = 0;
            grid[0][i] = 1;
        }
    }
    cout << "POSSIBLE\n";
    for (auto row:grid) {
        for (auto x:row) cout << (x ? '.' : '#');
        cout << '\n';
    }
}

signed main() {
    cin.tie(0)->sync_with_stdio(false);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}