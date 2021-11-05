src = $(wildcard ./src/*.cpp)
obj = $(src:.cpp=.o)

calcpp: $(obj)
	    g++ -o $@ $^ -lncurses

clean:
	    rm -f $(obj) calcpp
