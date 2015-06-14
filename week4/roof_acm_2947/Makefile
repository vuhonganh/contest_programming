CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -lm -lcrypt -O2 -pipe -DONLINE_JUDGE
CXXFLAGS = -Wall -lm -lcrypt -O2 -pipe -DONLINE_JUDGE

#SRCS = $(wildcard *.cpp)
#OBJS = (SRCS:.cpp=.o)
exe = roof

all: $(exe)

$(exe): $(exe).cpp

run: $(exe)
	./$< < input

out: $(exe)
	./$< < input > output
.PHONY: clean

clean:
	rm -rf $(exe) output
