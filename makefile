LIB=-lGLU -lGL -lglut
SRC=src/*.cpp src/animation/*.cpp


default:
	g++ $(SRC) -o main $(LIB) 

run: default
	./main

clean:
	rm *.o main
