CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -O2 -std=c++11 -Wall
CXXFLAGS = -O2 -std=c++11 -Wall

#SRCS = $(wildcard *.cpp)
#OBJS = (SRCS:.cpp=.o)
exe = solitaire

all: $(exe)

$(exe): $(exe).cpp

run: $(exe)
	./$< < input.txt

run2: $(exe)
	./$< < input2.txt

.PHONY: clean

clean:
	rm -rf $(exe)
