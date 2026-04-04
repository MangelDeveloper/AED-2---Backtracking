CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

OBJ = MainBT.o AlgoritmoBT.o ControladorBT.o

a.out: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o a.out

MainBT.o: main.cpp Algoritmos/Backtracking.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o MainBT.o

AlgoritmoBT.o: Algoritmos/Backtracking.cpp Algoritmos/Backtracking.h Controlador/Controlador.h
	$(CXX) $(CXXFLAGS) -c AlgoritmoBT.cpp -o AlgoritmoBT.o

ControladorBT.o: Controlador/Controlador.cpp Controlador/Controlador.h
	$(CXX) $(CXXFLAGS) -c ControladorBT.cpp -o ControladorBT.o

clean:
	rm -f *.o a.out