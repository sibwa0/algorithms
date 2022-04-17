TARGET = ./task.out
SRC = ./4_1.cpp

.PHONY: all check build rebuild run clean full

all: check build run

check:
	./run_linters.sh $(SRC)

build:
	$(CXX) -g -fdiagnostics-color -Wall -Wextra -Werror -o $(TARGET) $(SRC)

rebuild: clean build

run:
	$(TARGET)

clean:
	rm *.out

full: build run clean

memtest: build
	valgrind $(TARGET)
	rm *.out
