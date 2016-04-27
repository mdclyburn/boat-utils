CXX = g++
CXXFLAGS = -std=c++11 -O2 -g

all: agg

agg: main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: main.cpp

.PHONY: clean

clean:
	$(RM) agg *.o
