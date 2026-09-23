# 3b9864 - hash_alt.sh
# contest root Makefile; each problem dir's Makefile is just `include ../Makefile`
# in a problem dir: `make x` builds ./x from x.cpp (make's built-in %: %.cpp rule)

ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CXX      = g++-13
CXXFLAGS = -std=c++20 -DLOCAL -Og -Wall -Wextra -D_GLIBCXX_DEBUG -fsanitize=address,undefined
CXXFLAGS += -I$(ROOT)headers
