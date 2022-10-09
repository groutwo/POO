#Makefile p1
CXX = g++ 
CXXFLAGS = -std=${STD} -g -pedantic -Wall -o
VPATH = ../Tests-auto:.
CPPFLAGS = -I../Tests-auto -I. -DP1

STD = c++11
EXES = test-P1-auto test-P1-consola  
OBJS = test-caso0-cadena-auto.o test-caso0-fecha-auto.o test-P1-auto.o test-auto.o\
		 test-P1-consola.o fecha.o cadena.o fecha_check.o cadena_check.o 

all: $(EXES)

check: check_Fecha check_Cadena

cadena_check: 
	${MAKE} -f Make_check.mk $@

check_Cadena: 
	${MAKE} -f Make_check.mk $@

fecha_check: 
	${MAKE} -f Make_check.mk $@

check_Fecha: 
	${MAKE} -f Make_check.mk $@

fecha.o: fecha.hpp

cadena.o: cadena.hpp

test-auto.o: test-auto.hpp

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o cadena.o fecha.o 
	$(CXX) $(LDFLAGS) $^ -o $@ 

test-P1-consola: test-P1-consola.o cadena.o fecha.o
	$(CXX) $(LDFLAGS) $^ -o $@

test-P1-consola.o: fecha.hpp cadena.hpp

test-caso0-fecha_auto.o test-caso0-cadena-auto.o: test-auto.hpp

clean:
	$(RM) $(OBJS) $(EXES) 