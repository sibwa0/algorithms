.PHONY: all build rebuild clean run go run_linters

all: clean build rebuild run go run_linters

clean:
	rm -rf build

build:
	./build.sh

rebuild: clean build

run:
	./build/graph_impl

go: clean build run

# need fix
# run_linters:
	# ./run_linters.sh
