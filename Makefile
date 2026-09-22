# e36766 - hash_alt.sh
# contest root Makefile; each problem dir's Makefile is just `include ../Makefile`
# in a problem dir: `make x` builds ./x from x.cpp
# at contest start run `make` here once to build the precompiled header

ROOT := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

CXX      = g++-13
CXXFLAGS = -std=c++20 -DLOCAL -Og -Wall -Wextra -pedantic -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize=undefined
CXXFLAGS += -I$(ROOT)pch -I$(ROOT)headers -I$(ROOT) -Winvalid-pch

# gcc uses pch/bits/stdc++.h.gch in place of <bits/stdc++.h> if it was built
# with identical flags (-Winvalid-pch warns otherwise); the copied header must
# sit next to it since a second #include <bits/stdc++.h> reopens it there
HDR := $(ROOT)pch/bits/stdc++.h
PCH := $(HDR).gch

# pb_ds isn't in the stock bits/stdc++.h, so append it to the copy; .cpp files
# still include it explicitly for the judge, which the guards make free here
PBDS := assoc_container.hpp priority_queue.hpp tree_policy.hpp trie_policy.hpp

NAMES := $(basename $(wildcard *.cpp))

.PHONY: all clean
all: $(PCH)

$(HDR): $(ROOT)Makefile
	@mkdir -p $(@D)
	cp "$$(echo '#include <bits/stdc++.h>' | $(CXX) -x c++ -E -H -o /dev/null - 2>&1 | awk '/stdc\+\+\.h/{print $$2; exit}')" $@
	@for h in $(PBDS); do echo "#include <ext/pb_ds/$$h>" >> $@; done

$(PCH): $(HDR)
	$(CXX) $(CXXFLAGS) -x c++-header $< -o $@

$(NAMES): %: %.cpp $(PCH)
	$(CXX) $(CXXFLAGS) $< -o $@

# every problem's binary, plus the shared pch
clean:
	rm -f $(basename $(wildcard $(ROOT)*.cpp $(ROOT)*/*.cpp))
	rm -rf $(ROOT)pch
