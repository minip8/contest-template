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
using dd = double;


void solve() {
    int N; cin >> N;
    vector<ll> S(N); for (auto& s : S) cin >> s;
    vector<dd> C(N); for (auto& c : C) cin >> c;
    vector<int> M(N); for (auto& m : M) cin >> m;
    vector<dd> dp(N);
    for (int i = N - 1; i >= 0; i--) {
        int r = i + M[i] + 1;
        dd right_best = r >= N ? 0.0 : dp[r];
        
        // take
        dd cand1 = C[i] * S[i] + (1 - C[i]) * right_best;

        // not take
        dd cand2 = i + 1 < N ? dp[i + 1] : 0.0;

        dp[i] = max(cand1, cand2);
    }
    cout << fixed << setprecision(9) << dp[0] << '\n';
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