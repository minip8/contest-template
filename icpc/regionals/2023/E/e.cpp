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
    ll n, s, h; cin >> n >> s >> h;
    vll p(n); for (int i = 0; i < n; i++) cin >> p[i];
    multiset<ll> ms(all(p));
    for (int i = 0; i < h; i++) {
        auto it = ms.lower_bound(s);
        if (it == ms.begin()) {
            break;
        }
        it = prev(it);
        s += (ll)ceil(sqrt(*it));
        ms.erase(it);
    }
    cout << s << endl;
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