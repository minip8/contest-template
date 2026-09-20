# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A per-contest ICPC scratch repo, not a library. One directory per problem (`A/`, `B/`, ...), each holding `<letter>.cpp`, sample tests as `<n>.in` / `<n>.out`, and a one-line `Makefile` that is just `include ../Makefile`. `template.cpp` is the starting point to copy into a new problem dir; `pbds.cpp` is a paste-in snippet for the pb_ds includes.

## Commands

Run once at contest start, from the repo root — it builds the shared precompiled header:

```sh
make
```

Then work inside a problem dir. `make <name>` builds `<name>.cpp` into `./<name>`:

```sh
cd A && make a          # build A/a.cpp -> A/a
./a < 1.in              # run one sample
./a < 1.in | diff - 1.out
```

`make clean` (from anywhere) deletes every problem binary and the PCH. There is no test-runner script and no lint step; samples are checked by hand with `diff`.

`.zshrc` sets `ASAN_OPTIONS`/`UBSAN_OPTIONS` so sanitizer aborts print a stack trace — source it if crashes are silent.

## Build setup

`g++-13`, `-std=c++20`, with `-DLOCAL`, heavy warnings, `_GLIBCXX_DEBUG`, and ASan+UBSan. Local builds are intentionally slow and loud; judge submissions are the plain `.cpp` text.

The root `Makefile` copies the real `bits/stdc++.h` to `pch/bits/stdc++.h`, appends the four pb_ds headers to the copy, and precompiles it. Two consequences:

- The PCH is only used if a translation unit compiles with **identical** flags — `-Winvalid-pch` warns when it silently falls back. Changing `CXXFLAGS` means the PCH rebuilds; don't add per-problem flags.
- pb_ds is already in the PCH, so `#include <ext/pb_ds/...>` in a source file costs nothing locally, but must still be written out explicitly because the judge has no PCH.

`compile_flags.txt` mirrors these flags for clangd, but `.vscode/settings.json` disables clangd in favour of Microsoft IntelliSense (cpptools), which does **not** read `compile_flags.txt` — its copy of the flags lives in the `C_Cpp.default.*` keys of that settings file, so a change to `CXXFLAGS` that affects parsing (the standard, `-DLOCAL`, the `-I` paths) has to be mirrored there by hand.

## Source conventions

Anything in a submitted `.cpp` must compile standalone on a judge that has neither `headers/` nor `-DLOCAL`. Hence the guard every solution file opens with:

```cpp
#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) ((void)0)
#endif
```

`headers/debug.h` provides `debug(a, b, ...)`, which prints `LINE: [a = ... || b = ...]` to stderr. It handles containers, nested containers (as a numbered table), pairs, tuples, and stack/queue/priority_queue, and splits the argument names itself by scanning `#__VA_ARGS__` for top-level commas — so an unparenthesized comma inside a template argument list (e.g. `map<int,int>{}` as a literal argument) is the one thing that confuses it.

Keep the template's short aliases (`all`, `sz`, `pb`, `fi`, `se`, `ll`, `pii`, `vi`, ...) rather than inventing new ones, and keep solutions in `solve()` with the multi-test loop in `main` — uncomment `cin >> t` when the problem needs it.

There is no `.gitignore`, so `pch/` and the compiled binaries show up as untracked — leave them out of commits, or run `make clean` first.
