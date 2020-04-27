#pragma once
#include "Figures.h"
#include <sstream>


class Aggregate: public Figure
{
private:
	std::vector<Figure*> figures;

	friend class AggregateMemento;

public:
	Aggregate();
	~Aggregate();

	bool addFigure(Figure* figure);

	Figure* getFigure(int index);

	std::vector<FigureProperties*> getFigures();

	int containsFigure(Figure* figure);
	int containsType(std::string type);

	FigureMemento* save();

	void restore(FigureMemento* memento);

	// Тип фигуры
	std::string getType();

	// Движение
	void move(float speed, int direction);
	void autoMove(float speed);

	// Смена цвета
	void changeColor();

	Figure* clone();
};


class AggregateMemento: private FigureMemento
{
private:
	std::string data;

	std::string serializeAggregate(Aggregate* _aggregate);
	Aggregate* deserializeAggregate(std::stringstream& stream);

public:
	AggregateMemento(std::string _data);
	AggregateMemento(Aggregate* _aggregate);

	Figure* getFigure();
	std::string getData();
};


class AggregateCaretaker
{
private:
	const std::string NAMES_FILE = "names.txt";

public:
	AggregateCaretaker();

	std::vector<Aggregate*> restoreState();
	void saveState(std::vector<Aggregate*> aggregates);
};