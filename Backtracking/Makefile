CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

OBJ = MainBT.o AlgoritmoBT.o ControladorBT.o

a.out: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o a.out

MainBT.o: main.cpp AlgoritmoBT.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o MainBT.o

AlgoritmoBT.o: AlgoritmoBT.cpp AlgoritmoBT.h ControladorBT.h
	$(CXX) $(CXXFLAGS) -c AlgoritmoBT.cpp -o AlgoritmoBT.o

ControladorBT.o: ControladorBT.cpp ControladorBT.h
	$(CXX) $(CXXFLAGS) -c ControladorBT.cpp -o ControladorBT.o

clean:
	rm -f *.o a.out