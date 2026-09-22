#include <bits/stdc++.h>
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) ((void)0)
#endif

#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define fi first
#define se second

using namespace std;

using ll = long long;
using dd = double;
using ld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vll = vector<ll>;

void solve() {
    int N; cin >> N;
    vector<vector<int>> A(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            int x; cin >> x;
            A[i].push_back(j);
        }
    }
    debug(sz(A) + sz(A) * sz(A) + 67);
    cout << A[N][0] << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}