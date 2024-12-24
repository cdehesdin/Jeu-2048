CXX = g++ # compilateur C++ utilisé
FILES_INTERFACE = 2048_interface.cpp variante.cpp interface.cpp modele.cpp
INTERFACE = `pkg-config --cflags --libs gtk+-3.0`

clean:
	rm 2048 2048_variante 2048_interface test 2048_bots 2048_IA 

all:
	$(CXX) 2048.cpp modele.cpp affichage.cpp -o 2048 -lncurses -ltinfo -std=c++17
	$(CXX) 2048_variante.cpp modele.cpp variante.cpp -o 2048_variante -lncurses -ltinfo -std=c++17
	$(CXX) 2048_IA.cpp modele.cpp -o 2048_IA -std=c++17
	$(CXX) 2048_bots.cpp modele.cpp -o 2048_bots -std=c++17
	$(CXX) test.cpp modele.cpp variante.cpp -o test -lncurses -ltinfo -std=c++17 
	$(CXX) $(FILES_INTERFACE) -o 2048_interface $(INTERFACE) -std=c++17

run_test:
	./test

run_2048:
	./2048

run_interface:
	./2048_interface

run_IA:
	./2048_IA

2048_IA:
	$(CXX) 2048_IA.cpp IA.cpp -o 2048_IA -std=c++17

run_bot:
	./2048_bots