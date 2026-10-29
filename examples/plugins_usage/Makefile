all:
	@echo '[Building plugin]'
	clang++ -shared -fpic -I. -o plugin.so plugin.cpp
	@echo '[Building main]'
	clang++ -I. -ldl -o main main.cpp

.PHONY: all

clean:
	rm -rf plugin.so main

