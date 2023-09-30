CCFLAGS=--std=c++11 -pedantic -Wall -Werror -ggdb3
CorrMatrix:main.o Asset.o Portfolio.o
	g++ -o correl_matrix $(CCFLAGS) main.o Asset.o Portfolio.o

%.o: %.cpp Assets.hpp 
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ correl_matrix
