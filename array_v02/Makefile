CXX=g++ -std=c++11
file_templates=my.vector.hpp my.range.allocator.hpp

my.vector.o: my.vector.h my.vector.cpp
	$(CXX) -c -o $@ my.vector.cpp

my.vector.exe: my.vector.o $(file_templates) my.vector.demo.h my.vector.main.cpp
	$(CXX) -o $@ my.vector.main.cpp my.vector.o

my.vector.test.exe: my.vector.o $(file_templates) my.vector.test.h my.vector.test.main.cpp
	$(CXX) -o $@ my.vector.test.main.cpp my.vector.o memory.map.o

my.vector.test.construct.exe: my.vector.o $(file_templates) my.vector.test.construct.h my.vector.test.construct.main.cpp
	$(CXX) -o $@ my.vector.test.construct.main.cpp my.vector.o

my.vector.test.ctor.exe: my.vector.o $(file_templates) my.vector.test.ctor.h my.vector.test.ctor.main.cpp
	$(CXX) -o $@ my.vector.test.ctor.main.cpp my.vector.o

my.vector.test.assign.exe: my.vector.o $(file_templates) my.vector.test.assign.h my.vector.test.assign.main.cpp
	$(CXX) -o $@ my.vector.test.assign.main.cpp my.vector.o

my.vector.test.range.assign.exe: my.vector.o $(file_templates) my.vector.test.range.assign.h my.vector.test.range.assign.main.cpp
	$(CXX) -o $@ my.vector.test.range.assign.main.cpp my.vector.o

clean:
	rm -f *.exe *.o
