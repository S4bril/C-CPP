#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <windows.h>
#include <algorithm>

class Game
{
private:
	//Init
	void initVariables();
	void initWindow();
	void initRectangles();

public:
	//Variables
	sf::RenderWindow* window;
	sf::Event event;
	int howMany; //how many rectangles
	int i;
	int j;
	int timer;
	int timerMax;
	bool stop;

	//Rectangles
	sf::RectangleShape rectangle;
	float tempX;
	std::vector <sf::RectangleShape> rectangles;
	sf::Vector2f rectangleSize;

	//functions
	void update();
	void render();
	void pollevents();

	void updateRectangles();
	void renderRectangles();

	//constractors & desctructors
	Game();
	virtual ~Game();

	//accessors
	const bool isRunning()const; 
};

