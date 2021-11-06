src = $(wildcard ./src/*.cpp)
obj = $(src:.cpp=.o)

calcpp: $(obj)
	    g++ -o $@ $^ -lncurses && rm -f $(obj)
