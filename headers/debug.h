#pragma once
#include <bits/stdc++.h>
using namespace std;

namespace dbg {

template <class T>
concept iter = requires(T &x) { begin(x); } && !is_convertible_v<T, string_view>;

void pr(auto &&x) {
    using T = remove_cvref_t<decltype(x)>;
    if constexpr (is_convertible_v<T, string_view>)
        cerr << '"' << x << '"';
    else if constexpr (is_same_v<T, char>)
        cerr << '\'' << x << '\'';
    else if constexpr (is_same_v<T, bool>)
        cerr << (x ? 'T' : 'F');
    else if constexpr (iter<T>) {
        int f = 0;
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
        auto t = x;
        int f = 0;
        cerr << '{';
        for (; !t.empty(); t.pop()) {
            cerr << (f++ ? "," : "");
            if constexpr (requires { t.top(); }) pr(t.top());
            else pr(t.front());
        }
        cerr << '}';
    } else if constexpr (requires { x.first; })
        cerr << '(', pr(x.first), cerr << ',', pr(x.second), cerr << ')';
    else if constexpr (requires { get<0>(x); }) {
        int f = 0;
        cerr << '(';
        apply([&](auto &&...a) { ((cerr << (f++ ? "," : ""), pr(a)), ...); }, x);
        cerr << ')';
    } else
        cerr << x;
}

/* splits #__VA_ARGS__ on commas that aren't nested inside ( { < */
void prn(const char *s, auto &&h, auto &&...t) {
    int i = 0, b = 0;
    for (; s[i] && (s[i] != ',' || b); i++)
        b += (s[i] == '(' || s[i] == '{' || s[i] == '<') - (s[i] == ')' || s[i] == '}' || s[i] == '>');
    cerr.write(s, i) << " = ";
    pr(h);
    if constexpr (sizeof...(t)) cerr << " ||", prn(s + i + 1, t...);
    else cerr << "]\n";
}

}  // namespace dbg

#define debug(...) cerr << __LINE__ << ": [", dbg::prn(#__VA_ARGS__, __VA_ARGS__)
