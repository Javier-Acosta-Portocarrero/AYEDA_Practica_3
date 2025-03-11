CXX = g++
CXXFLAGS =  -std=c++23 -Wall 
TARGET = practica1_ayed

SOURCES = funciones.cc main.cc big_unsigned.cc big_integer.cc big_rational.cc big_number.cc

OBJECTS = $(SOURCES:.cc=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

cleano:
	rm -f $(OBJECTS)

.PHONY: all clean cleano