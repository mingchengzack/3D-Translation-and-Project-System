project2: main.o object.o line.o point.o utility.o
	g++ -g -std=c++11 -Wall -o project2 main.o line.o point.o utility.o object.o -lglut -lGL

main.o: main.cpp utility.hpp object.hpp
	g++ -g -std=c++11 -Wall -c -o main.o main.cpp -lglut -lGL

object.o: object.cpp object.hpp utility.hpp line.hpp point.hpp
	g++ -g -std=c++11 -Wall -c -o object.o object.cpp -lglut -lGL

line.o: line.cpp line.hpp point.hpp utility.hpp
	g++ -g -std=c++11 -Wall -c -o line.o line.cpp -lglut -lglut -lGL

point.o: point.cpp point.hpp utility.hpp 
	g++ -g -std=c++11 -Wall -c -o point.o point.cpp -lglut -lGL

utility.o: utility.cpp utility.hpp
	g++ -g -std=c++11 -Wall -c -o utility.o utility.cpp -lglut -lGL

clean:
	rm -f *.o project2
