#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace dbg {

template <class T>
concept iter = requires(T &x) { begin(x); } && !is_convertible_v<T, string_view>;

/* pair and tuple share the get<0> branch; string falls through to cerr << */
void pr(auto &&x) {
    [[maybe_unused]] int f = 0;
    if constexpr (iter<remove_cvref_t<decltype(x)>>) {
        if constexpr (iter<remove_cvref_t<decltype(*begin(x))>>) { /* iterable of iterables */
            cerr << "\n~~~~~\n";
            for (auto &&i : x) cerr << setw(3) << left << f++, pr(i), cerr << '\n';
            cerr << "~~~~~\n";
        } else {
            cerr << '{';
            for (auto &&i : x) cerr << (f++ ? "," : ""), pr(i);
            cerr << '}';
        }
    } else if constexpr (requires { x.pop(); }) { /* stack, queue, priority_queue */
        cerr << '{';
        for (auto t = x; !t.empty(); t.pop(), f++) {
            cerr << (f ? "," : "");
            if constexpr (requires { t.top(); }) pr(t.top());
            else pr(t.front());
        }
        cerr << '}';
    } else if constexpr (requires { get<0>(x); }) {
        cerr << '(';
        apply([&](auto &&...a) { ((cerr << (f++ ? "," : ""), pr(a)), ...); }, x);
        cerr << ')';
    } else
        cerr << x;
}

/* splits #__VA_ARGS__ on commas that aren't nested inside ( { [ */
void prn(const char *s, auto &&h, auto &&...t) {
    int i = 0, b = 0;
    for (; s[i] && (s[i] != ',' || b); i++) b += !!strchr("({[", s[i]) - !!strchr(")}]", s[i]);
    cerr.write(s, i) << " = ";
    pr(h);
    if constexpr (sizeof...(t)) cerr << " ||", prn(s + i + !!s[i], t...);
    else cerr << "]\n";
}

}  // namespace dbg

#define debug(...) cerr << __LINE__ << ": [", dbg::prn(#__VA_ARGS__, __VA_ARGS__)
