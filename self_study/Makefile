CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -O2 -std=c++11 -Wall
CXXFLAGS = -O2 -std=c++11 -Wall

exe = name_of_exo

all: $(exe)

$(exe): name_of_exo.cpp

run: $(exe)
	./$< < input.txt

.PHONY: clean

clean:
	rm -rf $(exe)
