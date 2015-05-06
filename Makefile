CXX = g++
CXXFLAGS = -std=c++11 -g

dp: main.o TransducerBuffer.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main.o: TransducerBuffer.h
TransducerBuffer.o: TransducerBuffer.h

.PHONY: clean
clean:
	rm -f *.o dp
