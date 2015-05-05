CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -O2 -std=c++11
CXXFLAGS = -O2 -std=c++11

exe1 = LawnMower
exe2 = Goldbach

$(exe1): LawnMower.cpp

$(exe2): Goldbach.cpp

runLawnMower: $(exe1)
	./$< < input_$(exe1).txt

runGoldbach: $(exe2)
	./$< < input_$(exe2).txt

.PHONY: clean

clean:
	rm -rf $(exe1) $(exe2)
