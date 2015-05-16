CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -O2 -std=c++11 -Wall
CXXFLAGS = -O2 -std=c++11 -Wall

#SRCS = $(wildcard *.cpp)
#OBJS = (SRCS:.cpp=.o)
exe = proj_files_depends

all: $(exe)

$(exe): $(exe).cpp

run: $(exe)
	./$< < input.txt

.PHONY: clean

clean:
	rm -rf $(exe)
