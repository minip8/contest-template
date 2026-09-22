#include <bits/stdc++.h>
#include<cassert>
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define fi first
#define se second
// #define printArr(x) for (int i = 0; i < sz(x); i++) cout << x[i] << " \n"[i==sz(x)-1]
#define printArr(x) 888
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi = vector<int>;
using vll = vector<ll>;


void solve() {
    int N,M; cin >> N >> M;
    vector<vector<int>> key_to_chests(N); // what the key can contribute to opening a chest
    vector<int> chest_key(M); // what the chest contains
    vector<vector<int>> chest_prereqs(M); // keeys needed
    set<int> start_keys; for (int i = 0; i < N; i++) start_keys.insert(i);
    for (int i = 0; i < M; i++) {
        int c; cin >> c; c--;
        chest_key[i] = c; start_keys.erase(c);
        int u; cin >> u;
        for (int j = 0; j < u; j++) {
            int k; cin >> k;
            k--;
            chest_prereqs[i].push_back(k);
            key_to_chests[k].push_back(i);
        }
    }
    vector<set<int>> chest_preqreqs_set(M);
    for (int i = 0; i < M; i++) {
        chest_preqreqs_set[i] = set<int>(all(chest_prereqs[i]));
    }
    vector<int> vis_keys_forward(N), vis_chests_forward(M);
    auto dfs_forward = [&] (auto&& dfs, int cur, bool at_key) -> void {
        // cout << cur << " " << at_key << '\n';
        if (at_key) {
            if (cur == N - 1) return;
            for (int chest : key_to_chests[cur]) {
                if (chest_preqreqs_set[chest].find(chest_key[chest]) != chest_preqreqs_set[chest].end()) continue;
                if (chest_preqreqs_set[chest].find(cur) == chest_preqreqs_set[chest].end()) {
                    continue;
                }
                if (vis_chests_forward[chest]) continue;
                chest_preqreqs_set[chest].erase(cur);
                if (chest_preqreqs_set[chest].empty()) {
                    vis_chests_forward[chest] = 1;
                    dfs(dfs, chest, false);
                }
            }
        }
        else {
            int key = chest_key[cur];
            vis_keys_forward[key] = 1;
            dfs(dfs, key, true);
        }
    };

    for (int start_key : start_keys) {
        if (vis_keys_forward[start_key]) continue;
        vis_keys_forward[start_key] = 1;
        dfs_forward(dfs_forward, start_key, 1);
    }
    printArr(vis_keys_forward);
    printArr(vis_chests_forward);
    // for (int i = 0; i < M; i++) {
    //     vector<int> rem_prereq = vector<int>(all(chest_preqreqs_set[i]));
    //     printArr(rem_prereq);
    // }
    if (vis_keys_forward.back() == 0) {
        cout << -1 << "\n"; return;
    }
    vector<vector<int>> chests_containing_key(N);
    for (int i = 0; i < M; i++) {
        chests_containing_key[chest_key[i]].push_back(i);
    }
    vector<int> path;
    vector<int> vis_keys_backward(N), vis_chests_backward(M);
    auto dfs_backward = [&] (auto&& dfs, int cur, bool at_key) -> void {
        // cout << (at_key ? "at key: " : "at chest: ");
        // cout << cur + 1 << '\n';
        if (at_key) {
            for (int chest : chests_containing_key[cur]) {
                if (vis_chests_forward[chest] && !vis_chests_backward[chest]) {
                    vis_chests_backward[chest] = true;
                    dfs(dfs, chest, false);
                    path.push_back(chest);
                    return;
                }
            }
        }
        else {
            for (int key : chest_prereqs[cur]) {
                assert(vis_keys_forward[key]);
                if (vis_keys_backward[key]) continue;
                vis_keys_backward[key] = true;
                dfs(dfs, key, true);
            }
        }
    };
    vis_keys_backward[N - 1] = true;
    dfs_backward(dfs_backward, N - 1, true);
    // reverse(all(path));
    printArr(vis_keys_backward);
    printArr(vis_chests_backward);
    // vector<int> have_key(N); for (int key : start_keys) have_key[key] = 1;
    // for (int chest : path) {
    //     for (int prereq : chest_prereqs[chest]) {
    //         assert(have_key[prereq]);
    //     }
    //     have_key[chest_key[chest]] = 1;
    // }
    cout << sz(path) << '\n';
    for (int i = 0; i < sz(path); i++) {
        cout << path[i] + 1 << " \n"[i==sz(path)-1];
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