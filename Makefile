CC = c++
CXXFLAGS = -g -std=c++11 -pthread

PROGRAMS = santa

all: $(PROGRAMS)

clean: 
	rm -f *.o *~ $(PROGRAMS)
