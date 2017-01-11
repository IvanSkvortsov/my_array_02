CXX=g++ -std=c++11

my.array.o: my.array.h my.array.cpp
	$(CXX) -c -o $@ my.array.cpp

my.array.exe: my.array.o my.array.hpp my.array.demo.h my.array.main.cpp
	$(CXX) -o $@ my.array.main.cpp my.array.o

clean:
	rm -f *.exe *.o
