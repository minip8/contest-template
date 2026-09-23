# 2cb2af - hash_alt.sh
# contest root Makefile; each problem dir's Makefile is just `include ../Makefile`
# in a problem dir: `make x` builds ./x from x.cpp (make's built-in %: %.cpp rule)

ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CXX      = g++-13
CXXFLAGS = -std=c++20 -DLOCAL -Og -Wall -Wextra -pedantic -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined
CXXFLAGS += -I$(ROOT)headers
