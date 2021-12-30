all:
	clang++ -std=c++17 LFUCache.cc test.cc -lgtest -o test

clean:
	rm -rf test