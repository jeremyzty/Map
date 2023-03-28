build:
	rm -f ./a.out
	g++ -std=c++17 -g -Wall main.cpp buildings.cpp building.cpp footway.cpp footways.cpp   node.cpp nodes.cpp osm.cpp tinyxml2.cpp -Wno-unused-variable -Wno-unused-function

run:
	./a.out

valgrind:
	valgrind --tool=memcheck --leak-check=full ./a.out

clean:
	rm -f ./a.out

submit:
	/home/cs211/w2023/tools/project06 submit *.cpp *.h
