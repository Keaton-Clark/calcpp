calcpp: window.o main.o config.h calc.o
	g++ main.o window.o calc.o -o calcpp -lncurses && rm *.o && ./calcpp

main.o: main.cpp
	g++ -c main.cpp

window.o: window.cpp window.h
	g++ -c window.cpp -lncurses

calc.o: calc.cpp calc.h
	g++ -c calc.cpp

clean:
	rm *.o

run: calcpp
	./calcpp
