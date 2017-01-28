CXX=g++ -std=c++11

my.array.o: my.array.h my.array.cpp
	$(CXX) -c -o $@ my.array.cpp

my.array.exe: my.array.o my.array.hpp my.array.demo.h my.array.main.cpp
	$(CXX) -o $@ my.array.main.cpp my.array.o

my.array.test.exe: my.array.o my.array.hpp my.array.test.h my.array.test.main.cpp
	$(CXX) -o $@ my.array.test.main.cpp my.array.o memory.map.o

my.array.test.construct.exe: my.array.o my.array.hpp my.array.test.construct.h my.array.test.construct.main.cpp
	$(CXX) -o $@ my.array.test.construct.main.cpp my.array.o

my.array.test.ctor.exe: my.array.o my.array.hpp my.array.test.ctor.h my.array.test.ctor.main.cpp
	$(CXX) -o $@ my.array.test.ctor.main.cpp my.array.o

my.array.test.assign.exe: my.array.o my.array.hpp my.array.test.assign.h my.array.test.assign.main.cpp
	$(CXX) -o $@ my.array.test.assign.main.cpp my.array.o

my.array.test.range.assign.exe: my.array.o my.array.hpp my.array.test.range.assign.h my.array.test.range.assign.main.cpp
	$(CXX) -o $@ my.array.test.range.assign.main.cpp my.array.o

clean:
	rm -f *.exe *.o
