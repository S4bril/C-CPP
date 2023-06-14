#include "Game.h"
//Init
void Game::initVariables()
{
	this->window = nullptr;
	this->howMany = 80;
	this->i = 0;
	this->j = 0;
	this->timer = 0;
	this->timerMax = 1;
	stop = false;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1600, 800), "Sorting algorithms", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
}

void Game::initRectangles()
{
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(1);

	//first rectangle
	this->rectangleSize.x = static_cast<float>(this->window->getSize().x / this->howMany - 1);
	this->rectangleSize.y = static_cast<float>(rand() % this->window->getSize().y);
	this->rectangle.setSize(this->rectangleSize);
	this->rectangle.setPosition(1.f, this->window->getSize().y - this->rectangle.getSize().y);
	this->rectangles.push_back(this->rectangle);

	for (int i = 1; i < howMany; i++)
	{
		this->rectangleSize.y = static_cast<float>(rand() % this->window->getSize().y);

		this->rectangle.setSize(this->rectangleSize);
		this->rectangle.setPosition(this->rectangles[i - 1].getPosition().x + rectangle.getSize().x + 1
			, this->window->getSize().y - this->rectangle.getSize().y
		);

		this->rectangles.push_back(this->rectangle);
	}
}

//Functions
void Game::update()
{
	this->pollevents();
	this->updateRectangles();
}

void Game::render()
{
	this->window->clear(sf::Color::Black);

	//drawing stuff
	this->renderRectangles();

	this->window->display();
}

void Game::pollevents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			this->window->close();
		}break;

		default:
			break;
		}

	}
}

void Game::renderRectangles()
{
	for (auto rec: rectangles)
	{
		this->window->draw(rec);
	}
}

void Game::updateRectangles()
{
	if (this->i < this->rectangles.size())
	{
		if (this->j < rectangles.size() - 1 - i)
		{
			this->rectangles[j + 1].setFillColor(sf::Color::Red);
			this->rectangles[j].setFillColor(sf::Color::Red);
			stop = true;

			if (timer >= timerMax)
			{
				if (this->rectangles[j].getSize().y > this->rectangles[j + 1].getSize().y)
				{
					this->tempX = this->rectangles[j + 1].getPosition().x;
					this->rectangles[j + 1].setPosition(this->rectangles[j].getPosition().x, this->rectangles[j + 1].getPosition().y);
					this->rectangles[j].setPosition(this->tempX, this->rectangles[j].getPosition().y);

					std::iter_swap(this->rectangles.begin() + j, this->rectangles.begin() + j + 1);
				}
				//Time and color restart
				this->rectangles[j + 1].setFillColor(sf::Color::White);
				this->rectangles[j].setFillColor(sf::Color::White);
				timer = 0;
				stop = false;
			}
			else
			{
				timer++;
			}
		}
		if (stop == false)
		{
			j++;
		}
	}
	if (j == rectangles.size())
	{
		j = 0;
		this->rectangles[rectangles.size() - 1 - i].setFillColor(sf::Color::Green);
		i++;
	}
}

//constractors & desctructors
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initRectangles();
}
Game::~Game()
{
	delete window;
}

//accessors
const bool Game::isRunning()const
{
	return this->window->isOpen();
}