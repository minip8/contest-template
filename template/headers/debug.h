/* 635cef - kactl hash.sh */
/* 01f7ad - claude hash_alt.sh */
#pragma once
#include <bits/stdc++.h>
using namespace std;

void pr(auto &&x) {
    int f = 0;
    if constexpr (ranges::range<decltype(x)> && !is_convertible_v<decltype(x), string_view>) {
        cerr << '{';
        for (auto &&i : x) cerr << (f++ ? "," : ""), pr(i);
        cerr << '}';
    } else if constexpr (requires { get<0>(x); }) {
        cerr << '(';
        apply([&](auto &&...a) { ((cerr << (f++ ? "," : ""), pr(a)), ...); }, x);
        cerr << ')';
    } else cerr << x;
}

#define debug(...) cerr << __LINE__ << ": [" << #__VA_ARGS__ << "] =", [](auto &&...a) { ((cerr << ' ', pr(a)), ...); cerr << '\n'; }(__VA_ARGS__)
