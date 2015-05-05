CC  = gcc
CXX = g++
LDLIBS = -lm
CFLAGS = -O2 -std=c++11
CXXFLAGS = -O2 -std=c++11

exe1 = LawnMower
exe2 = Goldbach
exe3 = NoChange

$(exe1): LawnMower.cpp

$(exe2): Goldbach.cpp

$(exe3): NoChange.cpp

runLawnMower: $(exe1)
	./$< < input_$(exe1).txt

runGoldbach: $(exe2)
	./$< < input_$(exe2).txt

runNoChange: $(exe3)
	./$< < input_$(exe3).txt

.PHONY: clean

clean:
	rm -rf $(exe1) $(exe2) $(exe3)
