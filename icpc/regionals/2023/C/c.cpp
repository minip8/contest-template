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

template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b),
        oc = a.cross(b, c), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) 
        return {(a * ob - b * oa) / (ob - oa)};
    set<P> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return {all(s)};
}

void solve() {
    cout << setprecision(20);
    int n;cin >> n;
    vector<Point<ll>> pts(n);
    for (int i=0; i<n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }
    // vector<vector<pair<int,ll>>> g(n);
    vector<vector<double>> dst(n, vector<double> (n, DBL_MAX));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i == j) continue;
            bool ok = 1;
            for (int k=0; k<n; k++) {
                if (k == j || (k+1) % n == j) continue;
                if (k == i) {
                    auto prev = pts[(n + k - 1) % n];
                    auto v1 = prev - pts[i];
                    auto v2 = pts[j] - pts[i];
                    ok = v1.cross(v2) <= 0;
                    // if (!(v1.cross(v2) <= 0)) cout << pts[i] << ' ' << pts[j] << ' ' << pts[k] << '\n';
                    continue;
                } else if ((k + 1) % n == i) {
                    auto nxt = pts[(n + k + 2) % n];
                    auto v1 = nxt - pts[i];
                    auto v2 = pts[j] - pts[i];
                    ok = v1.cross(v2) >= 0;
                    // if (!(v1.cross(v2) >= 0)) cout << v1.cross(v2) << ' ' << v1 << ' ' << v2 << ' ' << pts[i] << ' ' << pts[j] << ' ' << pts[k] << '\n';
                    continue;
                }
                if (sz(segInter(pts[i], pts[j], pts[k], pts[(k+1) % n])) == 1) {
                    // cout << pts[i] << 'A' << pts[j] << ' ' << pts[k] << ' ' << pts[(k+1)%n] << '\n';
                    ok = 0;
                }
            }
            if (ok) {
                // cout << i << " " << j << '\n';
                dst[i][j] = min(dst[i][j], (pts[i] - pts[j]).dist());
                dst[j][i] = min(dst[j][i], (pts[i] - pts[j]).dist());
            }
        }
    }
    // cout << dst[0][2] << '\n';
    for (int i=0; i<n; i++) {
        dst[i][i] = 0;
    }
    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                dst[i][j] = min(dst[i][j], dst[i][k] + dst[k][j]);
            }
        }
    }
    for (auto x:dst) {
        for (auto y:x) cout << y << ' ';
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