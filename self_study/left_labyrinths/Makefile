CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -O2 -std=c++11 -Wall -Wextra -pedantic -g
CXXFLAGS = -O2 -std=c++11 -Wall -Wextra -pedantic -g

#SRCS = $(wildcard *.cpp)
#OBJS = (SRCS:.cpp=.o)
exe = left_labyrinths

all: $(exe)

$(exe): $(exe).cpp

run: $(exe)
	./$< < input

out: $(exe)
	./$< < input > output
.PHONY: clean

clean:
	rm -rf $(exe) output
