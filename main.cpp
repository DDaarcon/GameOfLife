#include <iostream>
#include <ctime>
#include "game_of_life.h"

const int SCREEN_HEIGHT = 650;
const int SCREEN_WIDTH = 800;
const sf::String WINDOW_NAME = "Game of Life";

struct CellNeighbours{
	Cell::States selfState;
	int alive = 0;
	int dead = 0;
};

CellNeighbours checkNeighbours(const Stage&, const sf::Vector2i&);

// funkcja zmienia planszę, jeśli zmiana ma byc wprowadzona w następnej klatce, zastosować po window.display (lub przed jeśli w tej samej klatce)
void updateStageCells(Stage&);

int main(){
	sf::View mainView(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_NAME);
	window.setView(mainView);
	
	Stage testStage(Cell::States::Dead, sf::Vector2i(100, 100));
	// testStage.makeLive(50, 50);
	// testStage.makeLive(50, 51);
	// testStage.makeLive(50, 52);
	// testStage.makeLive(51, 51);
	// testStage.makeLive(52, 51);
	testStage.createRandomLife(50);
	
	while(window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
		}//closing event
		
		
		window.clear(sf::Color(255, 255, 255, 255));
		testStage.draw(window);
		window.display();
		updateStageCells(testStage);
	}
	
	return 0;
}

CellNeighbours checkNeighbours(const Stage& stage_, const sf::Vector2i& coord_) {
	CellNeighbours cellNeighbours;
	if (stage_.checkIfXInside(coord_.x) &&
		stage_.checkIfYInside(coord_.y)){
		cellNeighbours.selfState = stage_.getCellState(coord_);
		
		// x . .
		// x . .
		// x . .
		if (coord_.x > 1){
			// x . .
			// . . .
			// . . .
			if (coord_.y > 1){
				if (stage_.getCellState(sf::Vector2i(coord_.x - 1, coord_.y - 1)) == Cell::States::Alive){
					cellNeighbours.alive++;
				} else {
					cellNeighbours.dead++;
				}
			}
			
			// . . .
			// x . .
			// . . .
			if (stage_.getCellState(sf::Vector2i(coord_.x - 1, coord_.y)) == Cell::States::Alive){
				cellNeighbours.alive++;
			} else {
				cellNeighbours.dead++;
			}
			
			// . . .
			// . . .
			// x . .
			if (stage_.checkIfYInside(coord_.y + 1)){
				if (stage_.getCellState(sf::Vector2i(coord_.x - 1, coord_.y + 1)) == Cell::States::Alive){
					cellNeighbours.alive++;
				} else {
					cellNeighbours.dead++;
				}
			}
		}
		
		// . . x
		// . . x
		// . . x
		if (stage_.checkIfYInside(coord_.x + 1)){
			// . . x
			// . . .
			// . . .
			if (coord_.y > 1){
				if (stage_.getCellState(sf::Vector2i(coord_.x + 1, coord_.y - 1)) == Cell::States::Alive){
					cellNeighbours.alive++;
				} else {
					cellNeighbours.dead++;
				}
			}
			
			// . . .
			// . . x
			// . . .
			if (stage_.getCellState(sf::Vector2i(coord_.x + 1, coord_.y)) == Cell::States::Alive){
				cellNeighbours.alive++;
			} else {
				cellNeighbours.dead++;
			}
			
			// . . .
			// . . .
			// . . x
			if (stage_.checkIfYInside(coord_.y + 1)){
				if (stage_.getCellState(sf::Vector2i(coord_.x + 1, coord_.y + 1)) == Cell::States::Alive){
					cellNeighbours.alive++;
				} else {
					cellNeighbours.dead++;
				}
			}
		}
		
		// . x .
		// . . .
		// . . .
		if (coord_.y > 1){
			if (stage_.getCellState(sf::Vector2i(coord_.x, coord_.y - 1)) == Cell::States::Alive){
				cellNeighbours.alive++;
			} else {
				cellNeighbours.dead++;
			}
		}
		
		// . . .
		// . . .
		// . x .
		if (stage_.checkIfYInside(coord_.y + 1)){
			if (stage_.getCellState(sf::Vector2i(coord_.x, coord_.y + 1)) == Cell::States::Alive){
				cellNeighbours.alive++;
			} else {
				cellNeighbours.dead++;
			}
		}
	}
	
	return cellNeighbours;
}


void updateStageCells(Stage& stage_) {
	CellNeighbours tempCellNeighbours;
	Stage tempStage(Cell::States::Dead, sf::Vector2i(stage_.getSizeX(), stage_.getSizeY()));
	
	for (int x = 1; stage_.checkIfXInside(x); x++)
		for (int y = 1; stage_.checkIfYInside(y); y++){
			tempCellNeighbours = checkNeighbours(stage_, sf::Vector2i(x, y));
			
			if (tempCellNeighbours.selfState == Cell::States::Alive){
				if (tempCellNeighbours.alive < 2 || tempCellNeighbours.alive > 3)
					tempStage.makeDead(x, y);
				else
					tempStage.makeLive(x, y);
				//std::cout << "a: " << tempCellNeighbours.alive << std::endl;
			}
			
			if (tempCellNeighbours.selfState == Cell::States::Dead){
				if (tempCellNeighbours.alive == 3)
					tempStage.makeLive(x, y);
				else
					tempStage.makeDead(x, y);
			}
			
		}
		
	for (int x = 1; stage_.checkIfXInside(x); x++)
		for (int y = 1; stage_.checkIfYInside(y); y++){
			if (stage_.getCellState(sf::Vector2i(x, y)) != tempStage.getCellState(sf::Vector2i(x, y)))
				stage_.setCellState(sf::Vector2i(x, y), tempStage.getCellState(sf::Vector2i(x, y)));
		}
		
}
