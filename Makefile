
CXX=g++
CXXFLAGS=-std=c++2a -O1 -I.

SRCS=$(wildcard test/*.cpp)
BINS=$(SRCS:.cpp=)

.PHONY: tests clean
tests: $(BINS)
clean:
	rm -f $(BINS)

test/%: test/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
	$@
