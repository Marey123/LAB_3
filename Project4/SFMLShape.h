#pragma once
#include "SFML/Graphics.hpp"
#include "Figure.h"

class SFMLShape: sf::Shape
{
public:
	SFMLShape(FigureProperties* figure);


	void setConfigs(FigureProperties* figure);

	virtual std::size_t getPointCount() const;
	
	virtual sf::Vector2f getPoint(std::size_t index) const;

private:
	float radius;
	std::size_t points;
};

