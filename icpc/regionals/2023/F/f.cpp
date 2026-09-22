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


template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); }
    P perp() const { return P(-y, x); }
    P normal() const { return perp().unit(); }
    P rotate(double a) const {
        return P(x*cos(a) - y*sin(a), x*sin(a)+y*cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

vi dst;
vector<vector<int>> g;

void dfs(int curr) {
    // cout << curr << endl;
    for (auto nei:g[curr]) {
        if (dst[nei] <= -1) dfs(nei);
        dst[curr] = max(dst[curr], dst[nei] + 1);
    }
}



void solve() {
    int n;cin >> n;
    vector<Point<ll>> pts(n);
    for (int i=0; i<n; i++) cin >> pts[i].x >> pts[i].y;
    Point<ll> tar = pts.back();
    g.resize(n);
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i == j) continue;
            Point<ll> a = pts[j] - pts[i];
            Point<ll> b = tar - pts[i];
            // cout << '\n';
            if (a.dot(b) >= a.dist2()) {
                // cout << "GOOD\n";
                // cout << i << ' ' << j << endl;
                // cout << pts[i] << pts[j];
                // cout << a << b << a.dot(b) << ' ' << a.dist2() << endl;
                g[i].push_back(j);
            }
        }
    }
    dst = vi(n, -1);
    dst[n-1] = 0;
    dfs(0);
    cout << dst[0] -1 << '\n';
    // for (auto x:dst) cout << x << ' ';
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