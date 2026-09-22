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

ll k, c;
string f, m, l;
ll fs;

ll sizef(ll M) {
    if (M == 0) return 0;
    // how many regions after ur thing? ig treat the new k as k - M
    ll x = k - M;
    ll y = (x + 1) * sz(f) + 3 * x * (x + 1) / 2;
    return fs - y;
}

void solvef() {
    ll L = 0, R = k;
    ll res = 0;
    while (L <= R) {
        ll M = L + (R - L) / 2;
        if (sizef(M) <= c) {
            res = M;
            L = M + 1;
        }
        else {
            R = M - 1;
        }
    }

    c -= sizef(res);

    if (c < sz(f)) {
        cout << f[c] << endl;
        return;
    }
    c -= sz(f);
    cout << "SON"[c % 3] << endl;
}

void solve() {
    cin >> k >> c;
    cin >> f >> m >> l;
    
    fs = (k + 1) * sz(f) + 3 * k * (k + 1) / 2;
    if (c < fs) {
        solvef();
        return;
    }
    c -= fs;

    if (c < sz(m)) {
        cout << m[c] << endl;
        return;
    }
    c -= sz(m);

    cout << l[c % sz(l)] << endl;
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