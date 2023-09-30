CCFLAGS=--std=c++11 -pedantic -Wall -Werror -ggdb3
efficient_frontier:main.o Assets.o
	g++ -o efficient_frontier $(CCFLAGS) main.o Assets.o

%.o: %.cpp Assets.hpp 
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ efficient_frontier
