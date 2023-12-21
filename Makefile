build:
	g++ -std=c++17 build.cpp -o run && rm -rf ./prod/code.cpp && ./run && rm -rf run
