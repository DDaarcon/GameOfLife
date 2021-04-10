#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
// game_of_life.h

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


class Cell {
	
public:
	enum States {Alive, Dead};	// cell states
		
private:
	sf::RectangleShape rectangle;	// object visible on screen
	States state;
	short aliveNeighbours = 0;
	
	bool setAlive();
	bool setDead();
protected:

public:
	Cell(States state_ = Dead);
	Cell(const sf::Vector2f size_, States state_ = Dead);
	
	void setState(States);
	States getState() const;

	void increaseAliveNeighbors(int amount = 1) {aliveNeighbours += amount;}
	void resetAliveNeighbours(int value = 0) {aliveNeighbours = value;}
	void resolveStateByRules();
	
	void setAbsolutePosition(const sf::Vector2f&);
	void draw(sf::RenderWindow& w) const;
};

class Stage {
	
private:
	Cell ** cells;
	const int sideOfCell = 3;
	const sf::Vector2i sizeOfStage;
		
	void setTableDimensions();

	Cell* getCellAt(const sf::Vector2i) const;
protected:
	
public:
	Stage(sf::Vector2i = sf::Vector2i(100, 100));	// initialize Stage with all Cells dead
	Stage(Cell::States, sf::Vector2i = sf::Vector2i(100, 100)); // initialize Stage with all Cells at given state
	~Stage();
	
	bool setCellState(const sf::Vector2i, Cell::States);
	bool makeAlive(int x, int y);
	bool makeDead(int x, int y);
	
	Cell::States getCellState(const sf::Vector2i) const;
	
	void createRandomLife(int);	// fills Stage with alive Cells randomly - higher parameter, fewer alive cells
	
	bool checkIfYInside(const int) const;
	bool checkIfXInside(const int) const;	// checks if x/y coordinate is within stage
	int getSizeX() const;
	int getSizeY() const;	// returns size

	void calculateStage(); // count alive neighbours of every cell
	void applyCalculationsAndDraw(sf::RenderWindow&);	// set state of every cell depending on number of alive neighbours
	
	void draw(sf::RenderWindow&) const;
};

#endif
