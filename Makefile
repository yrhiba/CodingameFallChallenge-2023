build:
	g++ -std=c++17 build.cpp -o run && rm -rf ./prod/code.cpp && ./run && rm -rf run

clean:
	rm -rf ./prod/*
	rm -rf ./prod/.*
	rm -rf ./src/.*
	rm -rf ./src/includes/.*
	rm -rf ./src/classes/.*
	rm -rf ./src/solutions/.*