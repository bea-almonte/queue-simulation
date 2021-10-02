CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Werror=return-type  -Werror=uninitialized # --coverage
# Do not allow compiling if a non-void function is missing a return statement
# Do not allow compiling if a variable is used without being initialized

OBJECTS = customer.o queue.o heap.o

final-simulation: final-simulation.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

memory: 
	valgrind ./final-simulation

clean:
	rm -rf *.dSYM
	$(RM) *.o *.gc* final-simulation
