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
        int n, f; cin >> n >> f;
        vector<pii> edge(f);
        for (int i = 0; i < f; i++) {
            int a, b; cin >> a >> b;
            edge.pb({ a-1, b-1 });
        }

        int res = 0;
        for (int s = 0; s < (1 << 16); s++) {
            int cur = 0;
            for (auto [a, b] : edge) {
                cur += ((s >> a) & 1) ^ ((s >> b) & 1);
            }
            res = max(res, cur);
        }
        cout << res << endl;
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