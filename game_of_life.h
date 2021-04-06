#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H
// game_of_life.h

// #include <cstdlib>
// #include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

	/* Info & Errors:
	 * Rozmiary komórek i całej planszy przechowywane są w obiekcie planszy
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 * 
	 */

class Cell {
	
public:
	enum States {Alive, Dead};	// stany komórki
		
private:
	sf::RectangleShape rectangle;	// rysowany obiekt
	States state;	// decyzja o tym, czy komórka jest żywa czy martwa
	short aliveNeighbours = 0;
	
	bool setAlive();
	bool setDead();
protected:

public:
	Cell(States state_ = Dead);
	Cell(const sf::Vector2f size_, States state_ = Dead);
	
	void setState(States);
	States checkState() const;	// status życia komórki

	void increaseAliveNeighbors(int amount = 1) {aliveNeighbours += amount;}
	void resetAliveNeighbours(int value = 0) {aliveNeighbours = value;} 
	
	void setAbsolutePosition(const sf::Vector2f&);
	void draw(sf::RenderWindow& w) const;
};

class Stage {
	
private:
	Cell ** cells;
	const int sideOfCell = 3;	// wymagane do wyliczania wymiarów planszy i umiejscowiania komórek, niestety zastosowane rozwiązanie pozwala jedynie na edytowanie wielkości komórek w kodzie klasy Stage :(
	const sf::Vector2i sizeOfStage;	// podawane podczas tworzenia obiektu, wymagane przechowywanie tej zmiennej do dalszych operacji (rozmieszczania komórek)
		
	void setTableDimensions();

	Cell* getCellAt(const sf::Vector2i) const;
protected:
	
public:
	Stage(sf::Vector2i = sf::Vector2i(100, 100));	// wszystkie martwe
	Stage(Cell::States, sf::Vector2i = sf::Vector2i(100, 100)); // wszystkie zgodnie z decyzją
	~Stage();
	
	bool setCellState(const sf::Vector2i, Cell::States);
	bool makeLive(int x, int y);
	bool makeDead(int x, int y);	// zmiana statusu życia poszczególnych komórek (2 wersy w górę)
	
	Cell::States getCellState(const sf::Vector2i) const;
	
	void createRandomLife(int);	// losowo tworzone życie na planszy
	
	bool checkIfYInside(const int) const;
	bool checkIfXInside(const int) const;
	int getSizeX() const;
	int getSizeY() const;

	void calculateStage(); // count alive neighbours of every cell
	void applyCalculationsAndDraw();	// set state of every cell depending on number of alive neighbours
	
	void draw(sf::RenderWindow&) const;
};

#endif
