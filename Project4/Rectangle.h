#pragma once
#include <SFML/Graphics.hpp>


class Rectangle : public sf::Shape
{
public:
	Rectangle()
	{
		setToDefault();
		update();
	}

	Rectangle(const sf::Vector2f& sz)
	{
		setSize(sz);
		update();
	}

	void setToDefault()
	{
		setSize(sf::Vector2f(150, 150));
		setFillColor(sf::Color::Green);
		setPosition(400, 400);
		setOrigin(250 / 2, 250 / 2);

		update();
	}
	void setSize(const sf::Vector2f& sz)
	{
		size = sz;
		update();
	}

	const sf::Vector2f& getSize() const
	{
		return size;
	}

	virtual std::size_t getPointCount() const
	{
		return 4;
	}

	virtual sf::Vector2f getPoint(std::size_t index) const
	{
		switch (index)
		{
		default:
		case 0: return sf::Vector2f(0, 0);
		case 1: return sf::Vector2f(size.x, 0);
		case 2: return sf::Vector2f(size.x, size.y);
		case 3: return sf::Vector2f(0, size.y);
		}
	}

private:
	sf::Vector2f size;
};