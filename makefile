game_of_life: main.o game_of_life.o
	g++ main.o game_of_life.o -o game_of_life -lsfml-graphics -lsfml-window -lsfml-system
	
game_of_life.o: game_of_life_def.cpp game_of_life.h
	g++ -c game_of_life_def.cpp -o game_of_life.o
	
main.o: main.cpp
	g++ -c main.cpp
