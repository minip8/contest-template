# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A per-contest ICPC scratch repo, not a library. One directory per problem (`A/`, `B/`, ...), each holding `<letter>.cpp`, sample tests as `<n>.in` / `<n>.out`, and a one-line `Makefile` that is just `include ../Makefile`. `template.cpp` is the starting point to copy into a new problem dir; `pbds.cpp` is a paste-in snippet for the pb_ds includes.

## Commands

Work inside a problem dir. `make <name>` builds `<name>.cpp` into `./<name>` via make's built-in `%: %.cpp` rule:

```sh
cd A && make a          # build A/a.cpp -> A/a
./a < 1.in              # run one sample
./a < 1.in | diff - 1.out
```

There is no test-runner script and no lint step; samples are checked by hand with `diff`.

`.zshrc` sets `ASAN_OPTIONS`/`UBSAN_OPTIONS` so sanitizer aborts print a stack trace — source it if crashes are silent.

## Build setup

`g++-13`, `-std=c++20`, with `-DLOCAL`, `-Og`, `-Wall -Wextra`, `_GLIBCXX_DEBUG`, and ASan+UBSan. Local builds are intentionally slow and loud; judge submissions are the plain `.cpp` text.

There is no precompiled header, so every build recompiles `<bits/stdc++.h>` from scratch. The first line of `template/Makefile` is its `hash_alt.sh` checksum (for checking a hand-typed copy) — recompute it after any edit to the Makefile.

`compile_flags.txt` mirrors these flags for clangd, but `.vscode/settings.json` disables clangd in favour of Microsoft IntelliSense (cpptools), which does **not** read `compile_flags.txt` — its copy of the flags lives in the `C_Cpp.default.*` keys of that settings file, so a change to `CXXFLAGS` that affects parsing (the standard, `-DLOCAL`, the `-I` paths) has to be mirrored there by hand.

pb_ds isn't in `<bits/stdc++.h>`, so solutions that use it paste the includes from `pbds.cpp`.

## Source conventions

Anything in a submitted `.cpp` must compile standalone on a judge that has neither `headers/` nor `-DLOCAL`. Hence the guard every solution file opens with:

```cpp
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) ((void)0)
#endif
```

`headers/debug.h` provides `debug(a, b, ...)`, which prints `LINE: [a = ... || b = ...]` to stderr. It handles containers, nested containers (as a numbered table), pairs, tuples, and stack/queue/priority_queue, and splits the argument names itself by scanning `#__VA_ARGS__` for commas that aren't nested inside `(`, `{` or `[`. Angle brackets are deliberately **not** counted, so shifts and comparisons (`debug(1 << k, x)`, `debug(a < b, x)`) split correctly. The cost is that a literal template type containing a comma (`debug(map<int,int>{{1,2}})`) splits mid-type and mangles the displayed *name*; the values stay correct. Name the variable first if you hit it. Values print unquoted: strings and chars are bare, bools are `1`/`0`.

Keep the template's short aliases (`all`, `sz`, `pb`, `fi`, `se`, `ll`, `pii`, `vi`, ...) rather than inventing new ones, and keep solutions in `solve()` with the multi-test loop in `main` — uncomment `cin >> t` when the problem needs it.

There is no `.gitignore`, so compiled binaries show up as untracked — leave them out of commits.
