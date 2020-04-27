#include "SFMLWorker.h"
#include "SFMLShape.h"

SFMLWorker::SFMLWorker()
{
	sf::ContextSettings settings;

	settings.antialiasingLevel = 10;
	window = new sf::RenderWindow(sf::VideoMode(800, 800), "LAB_3", sf::Style::Default, settings);
}

void SFMLWorker::work()
{
	window->clear(sf::Color::Black);

	while (window->isOpen())
	{

		sf::Event event;
		while (window->pollEvent(event))
		{
			// Close program
			if (event.type == sf::Event::Closed)
			{
				window->close();

				return;
			}

			manageEvent(event);
		}

		window->clear(sf::Color::Black);

		std::vector<FigureProperties*> figures = Controller::getInstance().getFigures();

		std::vector<sf::Shape*> shapes;

		for (auto& figure : figures)
		{
			sf::Shape* shape = (sf::Shape*)(new SFMLShape(figure));
			shapes.push_back(shape);
		}

		for (auto& shape : shapes)
		{
			window->draw(*shape);
		}

		window->display();

		for (auto& shape : shapes)
		{
			delete shape;
		}
	}
}

void SFMLWorker::manageEvent(sf::Event event)
{
	// Generate Circle - 1
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
	{
		Controller::getInstance().generateCircle();
	}
	// Generate Rectangle - 2
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
	{
		Controller::getInstance().generateRectangle();
	}
	// Change color - Q
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
	{
		Controller::getInstance().changeColor();
	}
	// Select figure - Left Click
	else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2f mouse_position;
		mouse_position.x = sf::Mouse::getPosition(*window).x;
		mouse_position.y = sf::Mouse::getPosition(*window).y;

		Controller::getInstance().selectFigure(mouse_position.x, mouse_position.y);
	}
	// Aggregate / Deaggregate all figures - W
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
	{
		Controller::getInstance().setAggregation(!Controller::getInstance().isAggregated());
	}
	// Auto move - E
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)
	{
		Controller::getInstance().moveAuto();
	}
	// Move
	else if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Up ||
		event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Left ||
		event.key.code == sf::Keyboard::Right))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Controller::getInstance().move(LEFT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Controller::getInstance().move(RIGHT);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Controller::getInstance().move(UP);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Controller::getInstance().move(DOWN);
		}
	}
	// Save figures to file "figures.txt" - S
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
	{
		Controller::getInstance().saveProgress();
	}
	// Load figures from file "figures.txt" - D
	else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
	{
		Controller::getInstance().loadProgress();
	}
}
