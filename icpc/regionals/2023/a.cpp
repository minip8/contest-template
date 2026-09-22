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
    ll n, k;cin >> n >> k;
    vector<ll> a(n);
    for (int i=0; i<n; i++) {
        cin >> a[i];
    }
    ll sum = 0;
    for (int i=0; i<n; i++) {
        sum += (a[n-1-i] % (k+1) != 0) * (i + 1);
    }
    cout << (sum % 2 ? "Aaron" : "Bertha");
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